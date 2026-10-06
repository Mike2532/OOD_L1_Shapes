#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <memory>

#include "../PictureObserver.h"
#include "../../../picture/Picture.h"
#include "../../../shapeStorage/ShapeStorage.h"
#include "../../../../strategy/abstract/StrategyStorage.h"

const std::string TEST_PICTURE_ID = "testId";

std::shared_ptr<model::Picture> GetPicture()
{
    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();

    return std::make_shared<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        nullptr
    );
}

void AddRectangle(std::shared_ptr<model::Picture>& picture)
{
    std::vector<std::string> rectangleArgs = {"1", "2", "3", "4"};
    auto data = AddShapeData(
        TEST_PICTURE_ID,
        "#ffffff",
        "rectangle",
        rectangleArgs
    );
    picture->AddShape(data);
}

TEST_CASE("default behavior")
{
    std::ostringstream output;
    auto pictureObserver = std::make_shared<model::PictureObserver>(output);
    auto picture = GetPicture();

    auto removedSubscription = picture->SubscribeToShapeRemoved([&pictureObserver](const model::ShapeRemovedEvent& event) {
        pictureObserver->OnShapeRemoved(event);
    });
    auto addedSubscription = picture->SubscribeToShapeAdded([&pictureObserver](const model::ShapeAddedEvent& event) {
        pictureObserver->OnShapeAdded(event);
    });
    auto movedSubscription = picture->SubscribeToMove([&pictureObserver](const model::ShapeMovedEvent& event) {
        pictureObserver->OnShapeMoved(event);
    });

    AddRectangle(picture);
    REQUIRE(output.str() == "Added testId to Picture\n");
    output.str("");

    auto mData = MoveShapeData(TEST_PICTURE_ID, 3, 4);
    picture->MoveShape(mData);
    REQUIRE(output.str() == "Picture changed. testId: shape testId change coords. New coords: 4.00 6.00\n");
    output.str("");

    auto dData = DeleteShapeData(TEST_PICTURE_ID);
    picture->DeleteShape(dData);
    REQUIRE(output.str() == "Removed testId from Picture\n");
}

TEST_CASE("two subscribers")
{
    std::ostringstream output1;
    auto observer1 = std::make_shared<model::PictureObserver>(output1);

    std::ostringstream output2;
    auto observer2 = std::make_shared<model::PictureObserver>(output2);

    auto picture = GetPicture();

    auto addedSubscriptionOne = picture->SubscribeToShapeAdded([&observer1](const model::ShapeAddedEvent& event) {
        observer1->OnShapeAdded(event);
    });
    auto addedSubscriptionTwo = picture->SubscribeToShapeAdded([&observer2](const model::ShapeAddedEvent& event) {
        observer2->OnShapeAdded(event);
    });

    AddRectangle(picture);

    REQUIRE(output1.str() == "Added testId to Picture\n");
    REQUIRE(output2.str() == "Added testId to Picture\n");
}

TEST_CASE("double subscribe produces TWO notifications")
{
    std::ostringstream output;
    auto pictureObserver = std::make_shared<model::PictureObserver>(output);
    auto picture = GetPicture();

    auto addedSubscriptionOne = picture->SubscribeToShapeAdded([&pictureObserver](const model::ShapeAddedEvent& event) {
        pictureObserver->OnShapeAdded(event);
    });
    auto addedSubscriptionTwo = picture->SubscribeToShapeAdded([&pictureObserver](const model::ShapeAddedEvent& event) {
        pictureObserver->OnShapeAdded(event);
    });

    AddRectangle(picture);

    REQUIRE(output.str() == "Added testId to Picture\nAdded testId to Picture\n");
}

TEST_CASE("unsubscribe")
{
    std::ostringstream output;
    auto pictureObserver = std::make_shared<model::PictureObserver>(output);
    auto picture = GetPicture();

    auto subAdded = picture->SubscribeToShapeAdded([&pictureObserver](const model::ShapeAddedEvent& event) {
        pictureObserver->OnShapeAdded(event);
    });
    auto subMoved = picture->SubscribeToMove([&pictureObserver](const model::ShapeMovedEvent& event) {
        pictureObserver->OnShapeMoved(event);
    });

    AddRectangle(picture);
    REQUIRE(output.str() == "Added testId to Picture\n");
    output.str("");

    subAdded.disconnect();
    subMoved.disconnect();

    auto data = MoveShapeData(TEST_PICTURE_ID, 3, 4);
    picture->MoveShape(data);

    REQUIRE(output.str() == "");
}