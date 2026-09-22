#ifndef OOD_L1_SHAPES_LINE_H
#define OOD_L1_SHAPES_LINE_H

#include <string>

#include "../abstract/StrategyRegister.h"
#include "../point/Point.h"

namespace strategy {
    struct LineStrategyName {
        static std::string GetStrategyName()
        {
            return "line";
        }
    };

    class Line : public StrategyRegister<Line, LineStrategyName>
    {
    public:
        Line(const std::vector<std::string>& args);

        void Move(double dx, double dy) override;

        void Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color) override;

        std::string GetArgsAsString() override;

        std::string GetStrategyName() override;

        std::string GetCoords() override;
    private:
        static constexpr int TARGET_ARGUMENTS_SIZE = 4;
        std::vector<size_t> targetIndexes = {0, 2};
        std::vector<Point> vertices;
    };
};

#endif //OOD_L1_SHAPES_LINE_H
