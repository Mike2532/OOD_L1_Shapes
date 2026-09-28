#include "Picture.h"

#include "../../strategy/abstract/StrategyStorage.h"
#include "../Shape.h"
#include "../observe/picture/PictureEvent.h"
#include "../shapeStorage/IShapeStorage.h"
#include "commandData/AddShapeData.h"
#include "commandData/MoveShapeData.h"

namespace model {
    void Picture::AddShape(const AddShapeData& data) {
        RequireShapeDoesNotExist(data.id);

        std::string color = data.color;
        std::transform(color.begin(), color.end(), color.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        auto strategy = GetExistingStrategy(data.shapeType, data.args);
        const auto shape = std::make_shared<Shape>(data.id, color, std::move(strategy));
        m_shapeStorage->Store(shape);

        auto subscription = shape->Subscribe(shared_from_this());
        m_subscriptions.push_back(std::move(subscription));

        const std::string shapeAddedNotification = "Added " + data.id + " to Picture";
        NotifyPicturesObservers(shapeAddedNotification);
    }

    void Picture::MoveShape(const MoveShapeData& data)
    {
        auto shape = GetExistingShape(data.id);
        shape->Move(data.dx, data.dy);
    }

    void Picture::DeleteShape(const DeleteShapeData& data)
    {
        const auto shape = GetExistingShape(data.id);
        auto subscriptionId = shape->GetSubscriptionId();

        const auto subscriptionIt = std::find_if(m_subscriptions.begin(), m_subscriptions.end(),
            [subscriptionId] (const Subscription& subscription) {
                return subscription.GetSubscriptionId() == subscriptionId;
        });
        if (subscriptionIt != m_subscriptions.end()) {
            subscriptionIt->Unsubscribe();
        }

        m_shapeStorage->DeleteById(data.id);

        std::string shapeRemovedNotification = "Removed " + data.id + " from Picture";
        NotifyPicturesObservers(shapeRemovedNotification);
    }

    void Picture::ChangeColor(const ChangeColorData& data)
    {
        auto shape = GetExistingShape(data.id);
        shape->SetColor(data.color);
    }

    void Picture::ChangeShape(const ChangeShapeData& data) {
        auto strategy = GetExistingStrategy(data.shapeType, data.args);
        const auto shape = GetExistingShape(data.id);
        shape->SetStrategy(std::move(strategy));
    }

    void Picture::DrawShape(const DrawShapeData& data)
    {
        auto shape = GetExistingShape(data.id);
        ShowShapes({shape});
    }

    void Picture::List(std::ostream& output)
    {
        auto shapes = m_shapeStorage->GetAll();
        const auto shapesSize = shapes.size();

        std::string result;
        for (auto shapeInd = 0; shapeInd < shapesSize; shapeInd++)
        {
            auto shape = shapes[shapeInd];
            result += std::to_string(shapeInd + 1) + ' ';
            result += shape->GetStrategyName() + ' ';
            result += shape->GetId() + ' ';
            result += shape->GetColor() + ' ';
            result += shape->GetArgsAsString();
            result += '\n';
        }
        output << result;
    }

    void Picture::MovePicture(const MovePictureData& data)
    {
        auto shapes = m_shapeStorage->GetAll();
        for (const auto& shape : shapes) {
            shape->Move(data.dx, data.dy);
        }
    }

    void Picture::DrawPicture()
    {
        auto shapes = m_shapeStorage->GetAll();
        ShowShapes(shapes);
    }

    void Picture::OnChange(const ShapeEvent &shapeEvent)
    {
        std::string notificationMsg = "Picture changed. " + shapeEvent.shapeId + ": " + shapeEvent.msg;
        NotifyPicturesObservers(notificationMsg);
    }

    Subscription Picture::SubscribePictureObserver(const std::weak_ptr<IObserverElem<PictureEvent>>& observer)
    {
        m_observerService.AddElement(observer);
        auto callback = [this, observer] () {
            m_observerService.RemoveElement(observer);
        };
        const auto subscriptionId = SubscribeIdProvider::GetNextSubscribeId();
        m_subscriptionId = subscriptionId;

        return Subscription(callback, subscriptionId);
    }

    std::shared_ptr<Shape> Picture::GetExistingShape(const std::string &id)
    {
        auto shape = m_shapeStorage->GetById(id);
        if (shape.has_value()) {
            return shape.value();
        }
        throw std::runtime_error("can not get shape with id " + id);
    }

    std::unique_ptr<strategy::IShapeStrategy> Picture::GetExistingStrategy(
        const std::string &shapeType,
        const std::vector<std::string> &args
    ) {
        auto strategy = m_strategyStorage->Construct(shapeType, args);
        if (strategy != nullptr) {
            return std::move(strategy);
        }
        throw std::runtime_error("unknown strategy");
    }

    void Picture::RequireShapeDoesNotExist(const std::string &id)
    {
        auto shape = m_shapeStorage->GetById(id);
        if (shape.has_value()) {
            throw std::runtime_error("shape with id " + id + " already exists");
        }
    }

    void Picture::ShowShapes(const std::vector<std::shared_ptr<Shape>> &shapes) {
        while (m_canvas->IsActive()) {
            if (m_canvas->NeedToClose()) {
                m_canvas->Close();
            }

            m_canvas->Clear();

            for (const auto& shape : shapes) {
                shape->Draw(m_canvas);
            }

            m_canvas->Display();
        }
    }

    void Picture::NotifyPicturesObservers(const std::string& msg) {
        const auto event = PictureEvent{msg};
        m_observerService.NotifyAll(event);
    }
}
