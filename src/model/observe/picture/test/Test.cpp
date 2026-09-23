#include <catch2/catch_test_macros.hpp>

#include "../PictureObserver.h"
#include "../../../picture/Picture.h"
#include "../../../shapeStorage/ShapeStorage.h"
#include "../../../../strategy/abstract/StrategyStorage.h"

const std::string testPictureAddedMsg = "Added testId to Picture\n";
const std::string testPictureId = "testId";

std::shared_ptr<model::Picture> GetPicture()
{
    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();
    return std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        nullptr
    );
}

void AddRectangle(std::shared_ptr<model::Picture> picture)
{
    std::vector<std::string> rectangleArgs = {"1", "2", "3", "4"};
    picture->AddShape(
        testPictureId,
        "#ffffff",
        "rectangle",
        rectangleArgs
    );
}

TEST_CASE("default behavior")
{
    std::ostringstream output;
    auto pictureObserver = model::PictureObserver(output);

    auto picture = GetPicture();
    picture->SubscribePictureObserver(&pictureObserver);

    AddRectangle(picture);
    REQUIRE(output.str() == testPictureAddedMsg);
    output.str("");

    picture->MoveShape(testPictureId, 3, 4);

    std::string justCreatedTestShapeMovedMsg = "Picture changed. testId: shape testId change coords. New coords: 4.00 6.00\n";
    REQUIRE(output.str() == "Picture changed. testId: shape testId change coords. New coords: 4.00 6.00\n");
    output.str("");

    picture->DeleteShape(testPictureId);
    REQUIRE(output.str() == "Removed testId from Picture\n");
}

TEST_CASE("two subscribers")
{
    std::ostringstream output;
    auto pictureObserver = model::PictureObserver(output);

    std::ostringstream secondOutput;
    auto secondPictureObserver = model::PictureObserver(secondOutput);

    auto picture = GetPicture();
    picture->SubscribePictureObserver(&pictureObserver);
    picture->SubscribePictureObserver(&secondPictureObserver);

    AddRectangle(picture);

    REQUIRE(output.str() == testPictureAddedMsg);
    REQUIRE(secondOutput.str() == testPictureAddedMsg);
}

TEST_CASE("double subscribe, one notification")
{
    std::ostringstream output;
    auto pictureObserver = model::PictureObserver(output);

    auto picture = GetPicture();
    picture->SubscribePictureObserver(&pictureObserver);
    picture->SubscribePictureObserver(&pictureObserver);

    AddRectangle(picture);
    REQUIRE(output.str() == testPictureAddedMsg);
}

TEST_CASE("unsubscribe")
{
    std::ostringstream output;
    auto pictureObserver = model::PictureObserver(output);

    auto picture = GetPicture();
    picture->SubscribePictureObserver(&pictureObserver);

    AddRectangle(picture);
    REQUIRE(output.str() == testPictureAddedMsg);
    output.str("");

    picture->UnsubscribePictureObserver(&pictureObserver);

    picture->MoveShape(testPictureId, 3, 4);
    REQUIRE(output.str() == "");
}