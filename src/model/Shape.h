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
        }

        std::string GetId();

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
    private:
        const std::string m_shapeId;
        std::string m_color;
        std::unique_ptr<strategy::IShapeStrategy> m_strategy;
    };
}

#endif //OOD_L1_SHAPES_SHAPE_H
