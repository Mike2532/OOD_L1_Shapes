#ifndef OOD_L1_SHAPES_SHAPE_H
#define OOD_L1_SHAPES_SHAPE_H
#include <memory>
#include <utility>

#include "../strategy/abstract/IShapeStrategy.h"

namespace model {
    class Shape
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
            std::regex pattern("^#[0-9a-f]{6}$");
            if (!std::regex_match(m_color, pattern)) {
                throw std::invalid_argument("invalid color. Color must be format #rrggbb");
            }
        }

        std::string GetId() {
            return m_shapeId;
        }

        std::string GetColor() {
            return m_color;
        }

        void SetColor(const std::string& color)
        {
            m_color = color;
        }

        void SetStrategy(std::unique_ptr<strategy::IShapeStrategy> strategy)
        {
            m_strategy = std::move(strategy);
        }

        virtual void Move(double dx, double dy)
        {
            m_strategy->Move(dx, dy);
        }

        //todo add params)
        virtual void Draw()
        {
            m_strategy->Draw();
        }

        std::string GetArgsAsString()
        {
            return m_strategy->GetArgsAsString();
        }

        std::string GetStrategyName()
        {
            return m_strategy->GetStrategyName();
        }
    private:
        const std::string m_shapeId;
        std::string m_color;
        std::unique_ptr<strategy::IShapeStrategy> m_strategy;
    };
}

#endif //OOD_L1_SHAPES_SHAPE_H
