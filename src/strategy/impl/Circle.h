#ifndef OOD_L1_SHAPES_CIRCLE_H
#define OOD_L1_SHAPES_CIRCLE_H

#include "../abstract/AutoRegisterStrategy.h"
#include "../point/Point.h"

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
        explicit Circle(const std::vector<std::string>& args);

        void Move(double dx, double dy) override;

        void Draw() override;

        std::string GetArgsAsString() override;

        std::string GetStrategyName() override;

    private:
        static constexpr int TARGET_ARGUMENTS_SIZE = 3;
        Point pivotPoint;
        double m_radius = 0;
    };
}


#endif //OOD_L1_SHAPES_CIRCLE_H
