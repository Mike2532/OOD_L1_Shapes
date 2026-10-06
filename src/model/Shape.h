#ifndef OOD_L1_SHAPES_SHAPE_H
#define OOD_L1_SHAPES_SHAPE_H
#include <memory>
#include <utility>

#include "../gfx/abstract/ICanvas.h"
#include "../strategy/abstract/IShapeStrategy.h"
#include "observe/shape/IObservableShape.h"
#include "observe/shape/ShapeEvent.h"

namespace model {
    class Shape : public IObservableShape
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

        std::string GetId()
        {
            return m_shapeId;
        }

        std::string GetColor()
        {
            return m_color;
        }

        void Draw(std::unique_ptr<gfx::ICanvas>& canvas)
        {
            m_strategy->Draw(canvas, m_color);
        }

        std::string GetArgsAsString()
        {
            return m_strategy->GetArgsAsString();
        }

        std::string GetStrategyName()
        {
            return m_strategy->GetStrategyName();
        }

        void SetColor(const std::string& color)
        {
            const auto oldColor = m_color;

            RequireColorIsValid(color);
            m_color = color;

            m_changedColorSignal(ShapeChangedColorEvent(
                m_shapeId,
                oldColor,
                m_color
            ));
        }

        void SetStrategy(std::unique_ptr<strategy::IShapeStrategy> strategy)
        {
            const auto oldName = m_strategy->GetStrategyName();

            m_strategy = std::move(strategy);

            m_changedStrategySignal(ShapeChangedStrategyEvent (
                m_shapeId,
                oldName,
                m_strategy->GetStrategyName()
            ));
        }

        void Move(double dx, double dy)
        {
            m_strategy->Move(dx, dy);

            m_movedSignal(ShapeMovedEvent(
               m_shapeId,
               m_strategy->GetCoords(),
               dx,
               dy
           ));
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
    };
}

#endif //OOD_L1_SHAPES_SHAPE_H
