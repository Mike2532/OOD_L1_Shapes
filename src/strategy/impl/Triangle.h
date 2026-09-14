#ifndef OOD_L1_SHAPES_TRIANGLE_H
#define OOD_L1_SHAPES_TRIANGLE_H
#include <string>

#include "../abstract/AutoRegisterStrategy.h"
#include "../Point/Point.h"

namespace strategy {
    struct TriangleStrategyName {
        static std::string GetStrategyName() {
            return "triangle";
        }
    };

    class Triangle : public AutoRegisterStrategy<Triangle, TriangleStrategyName> {
    public:
        Triangle(const std::vector<std::string>& args);

        void Move(double dx, double dy) override;

        void Draw() override;

        std::string GetArgsAsString() override;

        std::string GetStrategyName() override;
    private:
        static constexpr int TARGET_ARGUMENTS_SIZE = 6;
        std::vector<size_t> targetIndexes = {0, 2, 4};
        std::vector<Point> vertices;
    };
}


#endif //OOD_L1_SHAPES_TRIANGLE_H