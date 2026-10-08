#include <iostream>
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

void MoveJustInitedTestShape(model::Shape* testShape, const std::shared_ptr<TestShapeObserver>& shapeObserver)
{
    testShape->Move(5, 6);
    REQUIRE(shapeObserver->GetLastShapeId() == "testId");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "shape testId change coords. New coords: 6.00 8.00");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 1);
}

void ChangeTestShapeColorAfterMoving(model::Shape* testShape, const std::shared_ptr<TestShapeObserver>& shapeObserver)
{
    testShape->SetColor("#000000");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "shape testId change color. New color: #000000");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 2);
}

void RequireEmptyObserver(const std::shared_ptr<TestShapeObserver>& shapeObserver)
{
    REQUIRE(shapeObserver->GetLastShapeId() == "");
    REQUIRE(shapeObserver->GetLastShapeMsg() == "");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 0);
}

TEST_CASE("observer empty init")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();

    auto subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());

    RequireEmptyObserver(shapeObserver);
}

TEST_CASE("base notifications scenario")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();

    auto subMove = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());
    auto subColor = testShape.SubscribeToChangedColor(shapeObserver->GetColorHandler());
    auto subStrategy = testShape.SubscribeToChangedStrategy(shapeObserver->GetStrategyHandler());

    MoveJustInitedTestShape(&testShape, shapeObserver);
    ChangeTestShapeColorAfterMoving(&testShape, shapeObserver);

    std::vector<std::string> triangleArgs = {"1", "2", "3", "4", "5", "6"};
    testShape.SetStrategy(std::make_unique<strategy::Triangle>(triangleArgs));

    REQUIRE(shapeObserver->GetLastShapeMsg() == "shape testId change stategy. New strategy: triangle");
    REQUIRE(shapeObserver->GetNotificationsCounter() == 3);
}

TEST_CASE("double subscribe will produce two notifications")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();

    auto subscription1 = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());
    auto subscription2 = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());

    testShape.Move(5, 6);

    REQUIRE(shapeObserver->GetNotificationsCounter() == 2);
}

TEST_CASE("observer unsubscribe and will not get notifications")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();
    auto subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());

    MoveJustInitedTestShape(&testShape, shapeObserver);

    subscription.Unsubscribe();

    int counterBefore = shapeObserver->GetNotificationsCounter();
    testShape.Move(5, 6);
    REQUIRE(shapeObserver->GetNotificationsCounter() == counterBefore);
}

TEST_CASE("two observers get notifications")
{
    auto testShape = GetTestShape();
    auto shapeObserver1 = std::make_shared<TestShapeObserver>();
    auto shapeObserver2 = std::make_shared<TestShapeObserver>();

    auto subscription1 = testShape.SubscribeToMove(shapeObserver1->GetMoveHandler());
    auto subscription2 = testShape.SubscribeToMove(shapeObserver2->GetMoveHandler());

    testShape.Move(5, 6);

    REQUIRE(shapeObserver1->GetNotificationsCounter() == 1);
    REQUIRE(shapeObserver2->GetNotificationsCounter() == 1);
}

TEST_CASE("exception")
{
    auto testShape = GetTestShape();
    auto shapeObserver1 = std::make_shared<TestShapeObserver>();
    auto shapeObserver2 = std::make_shared<TestShapeObserver>();

    auto subscription1 = testShape.SubscribeToMove([](const model::ShapeMovedEvent& event) {
        throw std::runtime_error("runtime_error");
    });
    auto subscription2 = testShape.SubscribeToMove(shapeObserver2->GetMoveHandler());

    REQUIRE_THROWS_AS(
        testShape.Move(5, 6),
        std::runtime_error
    );

    REQUIRE(shapeObserver1->GetNotificationsCounter() == 0);
    REQUIRE(shapeObserver2->GetNotificationsCounter() == 0);
}

TEST_CASE("An unsuccessful operation that does not change the state of the object does not result in a notification")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();
    auto subscription = testShape.SubscribeToChangedColor(shapeObserver->GetColorHandler());

    REQUIRE_THROWS_MATCHES(
        testShape.SetColor("invalid color"),
        std::invalid_argument,
        Catch::Matchers::Message("invalid color. Color must be format #rrggbb")
    );

    RequireEmptyObserver(shapeObserver);
}

TEST_CASE("unsubscribe one of observers during notifications")
{
    auto testShape = GetTestShape();

    auto callbackObserver1 = std::make_shared<CallbackTestObserver<model::ShapeMovedEvent>>();
    auto callbackObserver2 = std::make_shared<CallbackTestObserver<model::ShapeMovedEvent>>();
    auto callbackObserver3 = std::make_shared<CallbackTestObserver<model::ShapeMovedEvent>>();

    auto firstSubscription = testShape.SubscribeToMove([callbackObserver1](const auto& e){ callbackObserver1->OnEvent(e); });
    auto secondSubscription = testShape.SubscribeToMove([callbackObserver2](const auto& e){ callbackObserver2->OnEvent(e); });
    auto thirdSubscription = testShape.SubscribeToMove([callbackObserver3](const auto& e){ callbackObserver3->OnEvent(e); });

    callbackObserver1->SetExecutable([&secondSubscription]() {
        secondSubscription.Unsubscribe();
    });

    testShape.Move(3, 4);

    REQUIRE(callbackObserver1->GetCallCount() == 1);
    REQUIRE(callbackObserver2->GetCallCount() == 0);
    REQUIRE(callbackObserver3->GetCallCount() == 1);
}

TEST_CASE("add new observer during notifications")
{
    auto testShape = GetTestShape();

    auto callbackObserver1 = std::make_shared<CallbackTestObserver<model::ShapeMovedEvent>>();
    auto callbackObserver2 = std::make_shared<CallbackTestObserver<model::ShapeMovedEvent>>();

    auto subscription1 = testShape.SubscribeToMove([callbackObserver1](const auto& e){ callbackObserver1->OnEvent(e); });
    std::optional<model::Subscription> subscription2;

    callbackObserver1->SetExecutable([&testShape, callbackObserver2, &subscription2]() {
        if (subscription2.has_value()) {
            return;
        }
        subscription2 = testShape.SubscribeToMove([callbackObserver2](const auto& e){ callbackObserver2->OnEvent(e); });
    });

    testShape.Move(3, 4);
    REQUIRE(callbackObserver1->GetCallCount() == 1);
    REQUIRE(callbackObserver2->GetCallCount() == 0);

    testShape.Move(3, 4);
    REQUIRE(callbackObserver1->GetCallCount() == 2);
    REQUIRE(callbackObserver2->GetCallCount() == 1);
}

TEST_CASE("double unsubscribe is safe")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();
    auto subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());

    MoveJustInitedTestShape(&testShape, shapeObserver);

    subscription.Unsubscribe();
    subscription.Unsubscribe();

    int counterBefore = shapeObserver->GetNotificationsCounter();
    testShape.Move(5, 6);
    REQUIRE(shapeObserver->GetNotificationsCounter() == counterBefore);
}

TEST_CASE("dont get notifications after destroying subscription object")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();

    {
        auto subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());
        MoveJustInitedTestShape(&testShape, shapeObserver);
    }

    int counterBefore = shapeObserver->GetNotificationsCounter();
    testShape.Move(5, 6);
    REQUIRE(shapeObserver->GetNotificationsCounter() == counterBefore);
}

TEST_CASE("destroying shape before subscription unsubscribe")
{
    std::optional<model::Subscription> subscription;
    auto shapeObserver = std::make_shared<TestShapeObserver>();

    {
        auto testShape = GetTestShape();
        subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());
    }

    subscription->Unsubscribe();
}

TEST_CASE("move subscription with save connections")
{
    auto testShape = GetTestShape();
    auto shapeObserver = std::make_shared<TestShapeObserver>();
    auto subscription = testShape.SubscribeToMove(shapeObserver->GetMoveHandler());

    auto secondSubscription = std::move(subscription);

    MoveJustInitedTestShape(&testShape, shapeObserver);
    REQUIRE(shapeObserver->GetNotificationsCounter() == 1);
}