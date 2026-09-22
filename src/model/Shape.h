#ifndef OOD_L1_SHAPES_SHAPE_H
#define OOD_L1_SHAPES_SHAPE_H
#include <memory>
#include <utility>

#include "../gfx/abstract/ICanvas.h"
#include "../strategy/abstract/IShapeStrategy.h"
#include "observe/shape/INotificationShape.h"
#include "observe/shape/IShapeObserver.h"

namespace model {
    class Shape : public INotificationShape
    {
    public:
        Shape(
            std::string id,
            std::string color,
            std::unique_ptr<strategy::IShapeStrategy> strategy
        )
            : m_shapeId(std::move(id)),
            m_color(std::move(color)),
            m_strategy(std::move(strategy))
        {
            RequireColorIsValid(m_color);
        }

        std::string GetId() override
        {
            return m_shapeId;
        }

        std::string GetColor() override
        {
            return m_color;
        }

        void Draw(std::unique_ptr<gfx::ICanvas>& canvas) override
        {
            m_strategy->Draw(canvas, m_color);
        }

        std::string GetArgsAsString() override
        {
            return m_strategy->GetArgsAsString();
        }

        std::string GetStrategyName() override
        {
            return m_strategy->GetStrategyName();
        }
    private:
        const std::string m_shapeId;
        std::string m_color;
        std::unique_ptr<strategy::IShapeStrategy> m_strategy;

        static void RequireColorIsValid(const std::string& color) {
            std::regex pattern("^#[0-9a-f]{6}$");
            if (!std::regex_match(color, pattern)) {
                throw std::invalid_argument("invalid color. Color must be format #rrggbb");
            }
        }

        void SetColorImpl(const std::string& color) override
        {
            RequireColorIsValid(color);
            m_color = color;
        }

        void SetStrategyImpl(std::unique_ptr<strategy::IShapeStrategy> strategy) override
        {
            m_strategy = std::move(strategy);
        }

        void MoveImpl(double dx, double dy) override
        {
            m_strategy->Move(dx, dy);
        }

        ShapeEvent ConstructEvent(const ShapeEventType& event) override
        {
            return ShapeEvent {
                m_shapeId,
                GetEventMsg(event)
            };
        }

        std::string GetEventMsg(const ShapeEventType& event) const {
            switch (event) {
                case ShapeEventType::ColorChanged:
                    return "shape " + m_shapeId + " change color. New color: " + m_color;
                case ShapeEventType::StrategyChanged:
                    return "shape " + m_shapeId + " change stategy. New strategy: " + m_strategy->GetStrategyName();
                case ShapeEventType::ShapeMoved:
                    return "shape " + m_shapeId + " change coords. New coords: " + m_strategy->GetCoords();
            }
            throw std::invalid_argument("unknown event type");
        }
    };
}

#endif //OOD_L1_SHAPES_SHAPE_H
