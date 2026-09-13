#ifndef OOD_L1_SHAPES_TEXT_H
#define OOD_L1_SHAPES_TEXT_H

#include <string>
#include "../abstract/AutoRegisterStrategy.h"

namespace strategy {
    struct TextStrategyName {
        static std::string GetStrategyName()
        {
            return "circle";
        }
    };

    class Text : AutoRegisterStrategy<Text, TextStrategyName>
    {
    public:
        void Move(double dx, double dy) override;
        void Draw() override;
    };
}

#endif //OOD_L1_SHAPES_TEXT_H
