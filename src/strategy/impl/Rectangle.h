#ifndef OOD_L1_SHAPES_RECTANGLE_H
#define OOD_L1_SHAPES_RECTANGLE_H

#include <string>

#include "../abstract/StrategyRegister.h"
#include "../point/Point.h"

namespace strategy {
    struct RectangleStrategyName {
        static std::string GetStrategyName() {
            return "rectangle";
        }
    };

    class Rectangle : public StrategyRegister<Rectangle, RectangleStrategyName>
    {
    public:
        Rectangle(const std::vector<std::string>& args);

        void Move(double dx, double dy) override;

        void Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color) override;

        std::string GetArgsAsString() override;

        std::string GetStrategyName() override;

        std::string GetCoords() override;
    private:
        static constexpr int TARGET_ARGUMENTS_SIZE = 4;
        Point pivotPoint;
        double m_width = 0;
        double m_height = 0;
    };
}

#endif //OOD_L1_SHAPES_RECTANGLE_H
