#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include <string>
#include "../../../strategy/abstract/IShapeStrategy.h"
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
            auto it = std::find(m_observers.begin(), m_observers.end(), observer);
            if (it == m_observers.end()) {
                m_observers.emplace_back(observer);
            }
        }

        void Unsubscribe(IShapeObserver* observer)
        {
            std::erase(m_observers, observer);
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
        std::vector<IShapeObserver*> m_observers;

        void Notify(const ShapeEventType& eventType) {
            for (auto& observer : m_observers) {
                if (observer != nullptr) {
                    observer->OnShapeChange(ConstructEvent(eventType));
                }
            }
        }

        virtual ShapeEvent ConstructEvent(const ShapeEventType& event) = 0;

        virtual void SetColorImpl(const std::string& color) = 0;
        virtual void SetStrategyImpl(std::unique_ptr<strategy::IShapeStrategy> strategy) = 0;
        virtual void MoveImpl(double dx, double dy) = 0;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H