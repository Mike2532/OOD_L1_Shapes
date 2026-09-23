#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include <string>
#include "../../../strategy/abstract/IShapeStrategy.h"
#include "../../observe/storage/ObserverStorage.h"
#include "IShapeObserver.h"

namespace model {
    class INotificationShape
    {
    public:
        virtual ~INotificationShape() = default;

        virtual std::string GetId() = 0;

        virtual std::string GetColor() = 0;

        virtual void Draw(std::unique_ptr<gfx::ICanvas>& canvas) = 0;

        virtual std::string GetArgsAsString() = 0;

        virtual std::string GetStrategyName() = 0;

        void Subscribe(IShapeObserver* observer)
        {
            m_observerStorage.AddObserver(observer);
        }

        void Unsubscribe(IShapeObserver* observer)
        {
            m_observerStorage.RemoveObserver(observer);
        }

        void SetColor(const std::string& color) {
            SetColorImpl(color);
            Notify(ShapeEventType::ColorChanged);
        }

        void SetStrategy(std::unique_ptr<strategy::IShapeStrategy> strategy) {
            SetStrategyImpl(std::move(strategy));
            Notify(ShapeEventType::StrategyChanged);
        }

        void Move(const double dx, const double dy) {
            MoveImpl(dx, dy);
            Notify(ShapeEventType::ShapeMoved);
        }
    private:
        ObserverStorage<IShapeObserver> m_observerStorage;

        void Notify(const ShapeEventType& eventType) {
            const auto event = ConstructEvent(eventType);

            auto observers = m_observerStorage.GetObservers();
            for (const auto& observer : observers) {
                if (observer->isRemoved || observer->observer == nullptr) {
                    continue;
                }
                observer->observer->OnShapeChange(event);
            }

            m_observerStorage.Unlock();
        }

        virtual ShapeEvent ConstructEvent(const ShapeEventType& event) = 0;

        virtual void SetColorImpl(const std::string& color) = 0;
        virtual void SetStrategyImpl(std::unique_ptr<strategy::IShapeStrategy> strategy) = 0;
        virtual void MoveImpl(double dx, double dy) = 0;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H