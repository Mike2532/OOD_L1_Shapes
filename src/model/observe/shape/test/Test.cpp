#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "CallbackTestObserver.h"
#include "TestShapeObserver.h"
#include "../../../Shape.h"
#include "../../../../strategy/impl/Rectangle.h"
#include "../../../../strategy/impl/Triangle.h"

model::Shape GetTestShape() {
    std::vector<std::string> rectangleArgs = {"1", "2", "3", "4"};
    return model::Shape{
        "testId",
        "#ffffff",
        std::make_unique<strategy::Rectangle>(rectangleArgs)
    };
}

void MoveJustInitedTestShape(model::Shape* testShape, TestShapeObserver* shapeObserver)
{
    testShape->Move(5, 6);
    REQUIRE(shapeObserver->GetLastShapeId() == "testId");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "shape testId change coords. New coords: 6.00 8.00");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 1);
}

void ChangeTestShapeColorAfterMoving(model::Shape* testShape, TestShapeObserver* shapeObserver)
{
    testShape->SetColor("#000000");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "shape testId change color. New color: #000000");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 2);
}

void RequireEmptyObserver(TestShapeObserver* shapeObserver)
{
    REQUIRE(shapeObserver->GetLastShapeId() == "");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 0);
}

TEST_CASE("observer empty init")
{
    auto testShape = GetTestShape();

    auto shapeObserver = TestShapeObserver();
    testShape.Subscribe(&shapeObserver);

    RequireEmptyObserver(&shapeObserver);
}

TEST_CASE("base notifications scenario")
{
    auto testShape = GetTestShape();

    auto shapeObserver = TestShapeObserver();
    testShape.Subscribe(&shapeObserver);

    MoveJustInitedTestShape(&testShape, &shapeObserver);

    ChangeTestShapeColorAfterMoving(&testShape, &shapeObserver);

    std::vector<std::string> triangleArgs = {"1", "2", "3", "4", "5", "6"};
    testShape.SetStrategy(std::make_unique<strategy::Triangle>(triangleArgs));
    REQUIRE(shapeObserver.GetLastShapeMsg() == "shape testId change stategy. New strategy: triangle");
    REQUIRE(shapeObserver.GetNotificationsCounter() == 3);
}

TEST_CASE("double subscribe will produce one notification")
{
    auto testShape = GetTestShape();
    auto shapeObserver = TestShapeObserver();
    testShape.Subscribe(&shapeObserver);
    testShape.Subscribe(&shapeObserver);

    MoveJustInitedTestShape(&testShape, &shapeObserver);
}

TEST_CASE("observer unsubsribe and will not get notifications")
{
    auto testShape = GetTestShape();
    auto shapeObserver = TestShapeObserver();
    testShape.Subscribe(&shapeObserver);

    MoveJustInitedTestShape(&testShape, &shapeObserver);

    testShape.Unsubscribe(&shapeObserver);

    MoveJustInitedTestShape(&testShape, &shapeObserver);
}

TEST_CASE("two observers get notifications")
{
    auto testShape = GetTestShape();
    auto shapeObserver = TestShapeObserver();
    auto secondObserver = TestShapeObserver();

    testShape.Subscribe(&shapeObserver);
    testShape.Subscribe(&secondObserver);

    MoveJustInitedTestShape(&testShape, &shapeObserver);
    ChangeTestShapeColorAfterMoving(&testShape, &secondObserver);
}

TEST_CASE("An unsuccessful operation that does not change the state of the object does not result in a notification")
{
    auto testShape = GetTestShape();
    auto shapeObserver = TestShapeObserver();
    testShape.Subscribe(&shapeObserver);

    REQUIRE_THROWS_MATCHES(
        testShape.SetColor("invalid color"),
        std::invalid_argument,
        Catch::Matchers::Message("invalid color. Color must be format #rrggbb")
    );

    RequireEmptyObserver(&shapeObserver);
}

TEST_CASE("unsubscribe one of observers during notifications")
{
    auto testShape = GetTestShape();

    auto callbackObserver = CallbackTestObserver();
    auto secondCallbackObserver = CallbackTestObserver();
    auto thirdCallbackObserver = CallbackTestObserver();

    testShape.Subscribe(&callbackObserver);
    testShape.Subscribe(&secondCallbackObserver);
    testShape.Subscribe(&thirdCallbackObserver);

    callbackObserver.SetExecutable([&testShape, &secondCallbackObserver] () {
        testShape.Unsubscribe(&secondCallbackObserver);
    });

    testShape.Move(3, 4);

    REQUIRE(callbackObserver.GetCallCount() == 1);
    REQUIRE(secondCallbackObserver.GetCallCount() == 0);
    REQUIRE(thirdCallbackObserver.GetCallCount() == 1);
}

TEST_CASE("add new observer during notifications")
{
    auto testShape = GetTestShape();

    auto callbackObserver = CallbackTestObserver();
    auto secondCallbackObserver = CallbackTestObserver();

    testShape.Subscribe(&callbackObserver);

    callbackObserver.SetExecutable([&testShape, &secondCallbackObserver] () {
        testShape.Subscribe(&secondCallbackObserver);
    });

    testShape.Move(3, 4);
    REQUIRE(callbackObserver.GetCallCount() == 1);
    REQUIRE(secondCallbackObserver.GetCallCount() == 0);

    testShape.Move(3, 4);
    REQUIRE(callbackObserver.GetCallCount() == 2);
    REQUIRE(secondCallbackObserver.GetCallCount() == 1);
}
