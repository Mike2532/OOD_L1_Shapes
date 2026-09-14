#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <SFML/Graphics.hpp>

#include "../../shapeStorage/ShapeStorage.h"
#include "../../../strategy/abstract/StrategyStorage.h"
#include "../Picture.h"
#include "../../../gfx/impl/SFMLCanvas.h"

const unsigned W = 800;
const unsigned H = 600;
std::string fontPath = "/System/Library/Fonts/Helvetica.ttc";

std::unique_ptr<model::Picture> GetPicture()
{
    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();
    return std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        nullptr
    );
}

std::unique_ptr<model::Picture> GetPictureWithCanvas(sf::RenderWindow& window, sf::Font font)
{
    auto canvas = std::make_unique<gfx::SFMLCanvas>(window, font);

    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();
    return std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        std::move(canvas)
    );
}

TEST_CASE("init empty picture")
{
    auto picture = GetPicture();

    std::ostringstream output;
    picture->List(output);
    REQUIRE(output.str() == "");
}

TEST_CASE("wrong color format")
{
    auto picture = GetPicture();

    std::string wrongColor = "hello world!";

    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};

    REQUIRE_THROWS_MATCHES(
        picture->AddShape(fistShapeId, wrongColor, firstShapeType, firstShapeArgs),
        std::invalid_argument,
        Catch::Matchers::Message("invalid color. Color must be format #rrggbb")
    );
}

TEST_CASE("add shapes and list them, delete one and list again")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};
    picture->AddShape(fistShapeId, defaultColor, firstShapeType, firstShapeArgs);

    std::string secondShapeId = "secondShapeId";
    std::string secondShapeType = "rectangle";
    std::vector<std::string> secondShapeArgs{"1", "2","3", "4"};
    picture->AddShape(secondShapeId, defaultColor, secondShapeType, secondShapeArgs);

    std::ostringstream output;
    picture->List(output);
    std::string result = output.str();
    std::string targetOutput = "1 circle fistShapeId #ffffff 1.00 2.00 3.00\n2 rectangle secondShapeId #ffffff 1.00 2.00 3.00 4.00\n";
    REQUIRE(result == targetOutput);

    picture->DeleteShape(fistShapeId);

    std::ostringstream secondOutput;
    picture->List(secondOutput);
    std::string secondResult = secondOutput.str();
    std::string secondTargetOutput = "1 rectangle secondShapeId #ffffff 1.00 2.00 3.00 4.00\n";
    REQUIRE(secondResult == secondTargetOutput);
}

TEST_CASE("Two shapes with same id")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};
    picture->AddShape(fistShapeId, defaultColor, firstShapeType, firstShapeArgs);

    REQUIRE_THROWS_MATCHES(
        picture->AddShape(fistShapeId, defaultColor, firstShapeType, firstShapeArgs),
        std::runtime_error,
        Catch::Matchers::Message("shape with id fistShapeId already exists")
    );
}

TEST_CASE("move shape")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string secondShapeId = "secondShapeId";
    std::string secondShapeType = "rectangle";
    std::vector<std::string> secondShapeArgs{"1", "2","3", "4"};
    picture->AddShape(secondShapeId, defaultColor, secondShapeType, secondShapeArgs);

    picture->MoveShape(secondShapeId, 3, 4);

    std::ostringstream secondOutput;
    picture->List(secondOutput);
    std::string secondResult = secondOutput.str();
    std::string secondTargetOutput = "1 rectangle secondShapeId #ffffff 4.00 6.00 3.00 4.00\n";
    REQUIRE(secondResult == secondTargetOutput);
}

TEST_CASE("move picture")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};
    picture->AddShape(fistShapeId, defaultColor, firstShapeType, firstShapeArgs);

    std::string secondShapeId = "secondShapeId";
    std::string secondShapeType = "rectangle";
    std::vector<std::string> secondShapeArgs{"1", "2","3", "4"};
    picture->AddShape(secondShapeId, defaultColor, secondShapeType, secondShapeArgs);

    picture->MovePicture(3, 4);

    std::ostringstream secondOutput;
    picture->List(secondOutput);
    std::string secondResult = secondOutput.str();
    std::string secondTargetOutput = "1 circle fistShapeId #ffffff 4.00 6.00 3.00\n2 rectangle secondShapeId #ffffff 4.00 6.00 3.00 4.00\n";;
    REQUIRE(secondResult == secondTargetOutput);
}

TEST_CASE("change shape color")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string secondShapeId = "secondShapeId";
    std::string secondShapeType = "rectangle";
    std::vector<std::string> secondShapeArgs{"1", "2","3", "4"};
    picture->AddShape(secondShapeId, defaultColor, secondShapeType, secondShapeArgs);

    std::string newColor = "#dddddd";
    picture->ChangeColor(secondShapeId, newColor);

    std::ostringstream secondOutput;
    picture->List(secondOutput);
    std::string secondResult = secondOutput.str();
    std::string secondTargetOutput = "1 rectangle secondShapeId #dddddd 1.00 2.00 3.00 4.00\n";
    REQUIRE(secondResult == secondTargetOutput);
}

TEST_CASE("change shape")
{
    auto picture = GetPicture();

    std::string defaultColor = "#ffffff";

    std::string secondShapeId = "secondShapeId";
    std::string secondShapeType = "rectangle";
    std::vector<std::string> secondShapeArgs{"1", "2","3", "4"};
    picture->AddShape(secondShapeId, defaultColor, secondShapeType, secondShapeArgs);

    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};
    picture->ChangeShape(secondShapeId, firstShapeType, firstShapeArgs);

    std::ostringstream secondOutput;
    picture->List(secondOutput);
    std::string secondResult = secondOutput.str();
    std::string secondTargetOutput = "1 circle secondShapeId #ffffff 1.00 2.00 3.00\n";
    REQUIRE(secondResult == secondTargetOutput);
}

TEST_CASE("draw shape by id")
{
    sf::RenderWindow window(sf::VideoMode({W, H}), "Shapes");

    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font file: " + fontPath);
    }

    auto picture = GetPictureWithCanvas(window, font);

    std::string firstColor = "#1f0ccc";
    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"100", "200","100"};
    picture->AddShape(fistShapeId, firstColor, firstShapeType, firstShapeArgs);

    picture->DrawShape(fistShapeId);
}

TEST_CASE("draw all shape types")
{
    sf::RenderWindow window(sf::VideoMode({W, H}), "Shapes");

    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font file: " + fontPath);
    }

    auto picture = GetPictureWithCanvas(window, font);

     picture->AddShape(
         "shapeId",
         "#1f0ccc",
         "circle",
         {"100", "200","100"}
     );

    picture->AddShape(
        "lineId",
        "#000000",
        "line",
{"400", "400","600", "400"}
    );

    picture->AddShape(
        "rectangleId",
        "#ff4400",
        "rectangle",
{"300", "300","150", "220"}
    );

    picture->AddShape(
        "textId",
        "#c8ff00",
        "text",
{"0", "0","25", "hello world!"}
    );

    picture->AddShape(
        "triangleId",
        "#9900ff",
        "triangle",
{"10", "50","200", "30", "75", "75"}
    );

    picture->DrawPicture();
}