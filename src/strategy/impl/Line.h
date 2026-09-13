#ifndef OOD_L1_SHAPES_LINE_H
#define OOD_L1_SHAPES_LINE_H

#include <string>

#include "../abstract/AutoRegisterStrategy.h"

namespace strategy {
    struct LineStrategyName {
        static std::string GetStrategyName()
        {
            return "line";
        }
    };

    class Line : AutoRegisterStrategy<Line, LineStrategyName>
    {
    public:
        void Move(double dx, double dy) override;
        void Draw() override;
    };
};

#endif //OOD_L1_SHAPES_LINE_H
