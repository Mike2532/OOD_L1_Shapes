#ifndef OOD_L1_SHAPES_RECTANGLE_H
#define OOD_L1_SHAPES_RECTANGLE_H

#include <string>

#include "../abstract/AutoRegisterStrategy.h"

namespace strategy {
    struct RectangleStrategyName {
        static std::string GetStrategyName() {
            return "rectangle";
        }
    };

    class Rectangle : public AutoRegisterStrategy<Rectangle, RectangleStrategyName>
    {
    public:
        void Move(double dx, double dy) override;
        void Draw() override;
    };

}

#endif //OOD_L1_SHAPES_RECTANGLE_H
