#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "../Circle.h"
#include "../Line.h"
#include "../Rectangle.h"
#include "../Text.h"
#include "../Triangle.h"

TEST_CASE("standart circle") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::string radius = "3";
    std::vector args{xPos, yPos, radius};
    auto strategy = strategy::Circle(args);

    std::string targetStrategyName = "circle";
    REQUIRE(strategy.GetStrategyName() == targetStrategyName);

    std::string targetArgsAsString = "1.00 2.00 3.00";
    REQUIRE(strategy.GetArgsAsString() == targetArgsAsString);

    strategy.Move(3, 4);
    std::string targetMovedArgsAsString = "4.00 6.00 3.00";
    REQUIRE(strategy.GetArgsAsString() == targetMovedArgsAsString);
}

TEST_CASE("circle negative radius") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::string radius = "-3";
    std::vector args{xPos, yPos, radius};
    REQUIRE_THROWS_MATCHES(
        strategy::Circle(args),
        std::invalid_argument,
        Catch::Matchers::Message("raduis must be non negative")
    );
}

TEST_CASE("circle too few arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Circle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 2 Expected: 3")
    );
}

TEST_CASE("circle too much arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Circle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 4 Expected: 3")
    );
}

TEST_CASE("standart line")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string xPos2 = "3";
    std::string yPos2 = "4";
    std::vector args{xPos, yPos, xPos2, yPos2};
    auto strategy = strategy::Line(args);

    std::string targetStrategyName = "line";
    REQUIRE(strategy.GetStrategyName() == targetStrategyName);

    std::string targetArgsAsString = "1.00 2.00 3.00 4.00";
    REQUIRE(strategy.GetArgsAsString() == targetArgsAsString);

    strategy.Move(3, 4);
    std::string targetMovedArgsAsString = "4.00 6.00 6.00 8.00";
    REQUIRE(strategy.GetArgsAsString() == targetMovedArgsAsString);
}

TEST_CASE("line too few arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Line(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 2 Expected: 4")
    );
}

TEST_CASE("line too much arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos, xPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Line(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 5 Expected: 4")
    );
}

TEST_CASE("standart rectangle")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string width = "3";
    std::string height = "4";
    std::vector args{xPos, yPos, width, height};
    auto strategy = strategy::Rectangle(args);

    std::string targetStrategyName = "rectangle";
    REQUIRE(strategy.GetStrategyName() == targetStrategyName);

    std::string targetArgsAsString = "1.00 2.00 3.00 4.00";
    REQUIRE(strategy.GetArgsAsString() == targetArgsAsString);

    strategy.Move(3, 4);
    std::string targetMovedArgsAsString = "4.00 6.00 3.00 4.00";
    REQUIRE(strategy.GetArgsAsString() == targetMovedArgsAsString);
}

TEST_CASE("rectangle too few arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Rectangle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 2 Expected: 4")
    );
}

TEST_CASE("rectangle too much arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos, xPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Rectangle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 5 Expected: 4")
    );
}

TEST_CASE("rectangle negative width")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string width = "-3";
    std::string height = "4";
    std::vector args{xPos, yPos, width, height};
    REQUIRE_THROWS_MATCHES(
        strategy::Rectangle(args),
        std::invalid_argument,
        Catch::Matchers::Message("width must be non negative")
    );
}

TEST_CASE("rectangle negative height")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string width = "3";
    std::string height = "-4";
    std::vector args{xPos, yPos, width, height};
    REQUIRE_THROWS_MATCHES(
        strategy::Rectangle(args),
        std::invalid_argument,
        Catch::Matchers::Message("height must be non negative")
    );
}

TEST_CASE("standart text")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string textSize = "3";
    std::string text = "hello world";
    std::vector args{xPos, yPos, textSize, text};
    auto strategy = strategy::Text(args);

    std::string targetStrategyName = "text";
    REQUIRE(strategy.GetStrategyName() == targetStrategyName);

    std::string targetArgsAsString = "1.00 2.00 3.00 hello world";
    REQUIRE(strategy.GetArgsAsString() == targetArgsAsString);

    strategy.Move(3, 4);
    std::string targetMovedArgsAsString = "4.00 6.00 3.00 hello world";
    REQUIRE(strategy.GetArgsAsString() == targetMovedArgsAsString);
}

TEST_CASE("text too few arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Text(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 2 Expected: 4")
    );
}

TEST_CASE("text too much arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos, xPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Text(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 5 Expected: 4")
    );
}

TEST_CASE("text negative text size")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string textSize = "-3";
    std::string text = "hello world";
    std::vector args{xPos, yPos, textSize, text};
    REQUIRE_THROWS_MATCHES(
        strategy::Text(args),
        std::invalid_argument,
        Catch::Matchers::Message("text size must be non negative")
    );
}

TEST_CASE("standart triangle")
{
    std::string xPos = "1";
    std::string yPos = "2";
    std::string xPos2 = "3";
    std::string yPos2 = "4";
    std::string xPos3 = "5";
    std::string yPos3 = "6";
    std::vector args{xPos, yPos, xPos2, yPos2, xPos3, yPos3};
    auto strategy = strategy::Triangle(args);

    std::string targetStrategyName = "triangle";
    REQUIRE(strategy.GetStrategyName() == targetStrategyName);

    std::string targetArgsAsString = "1.00 2.00 3.00 4.00 5.00 6.00";
    REQUIRE(strategy.GetArgsAsString() == targetArgsAsString);

    strategy.Move(3, 4);
    std::string targetMovedArgsAsString = "4.00 6.00 6.00 8.00 8.00 10.00";
    REQUIRE(strategy.GetArgsAsString() == targetMovedArgsAsString);
}

TEST_CASE("triangle too few arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos, xPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Triangle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 5 Expected: 6")
    );
}

TEST_CASE("triangle too much arguments") {
    std::string xPos = "1";
    std::string yPos = "2";
    std::vector args{xPos, yPos, xPos, yPos, xPos, xPos, xPos};
    REQUIRE_THROWS_MATCHES(
        strategy::Triangle(args),
        std::runtime_error,
        Catch::Matchers::Message("wrong number of arguments. Found: 7 Expected: 6")
    );
}
