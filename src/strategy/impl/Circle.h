#ifndef OOD_L1_SHAPES_CIRCLE_H
#define OOD_L1_SHAPES_CIRCLE_H

#include "../abstract/AutoRegisterStrategy.h"

namespace strategy {
    struct CircleStrategyName {
        static std::string GetStrategyName()
        {
            return "circle";
        }
    };

    class Circle : public AutoRegisterStrategy<Circle, CircleStrategyName>
    {
    public:
        void Move(double dx, double dy) override;
        void Draw() override;
    };

}

#endif //OOD_L1_SHAPES_CIRCLE_H
