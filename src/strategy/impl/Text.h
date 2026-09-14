#ifndef OOD_L1_SHAPES_TEXT_H
#define OOD_L1_SHAPES_TEXT_H

#include <string>
#include "../abstract/AutoRegisterStrategy.h"
#include "../point/Point.h"

namespace strategy {
    struct TextStrategyName {
        static std::string GetStrategyName()
        {
            return "text";
        }
    };

    class Text : public AutoRegisterStrategy<Text, TextStrategyName>
    {
    public:
        Text(const std::vector<std::string>& args);

        void Move(double dx, double dy) override;

        void Draw() override;

        std::string GetArgsAsString() override;

        std::string GetStrategyName() override;
    private:
        Point pivotPoint;
        double m_textSize;
        std::string m_text;
    };
}

#endif //OOD_L1_SHAPES_TEXT_H
