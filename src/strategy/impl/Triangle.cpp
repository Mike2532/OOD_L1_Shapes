#include "Triangle.h"

namespace strategy {
    Triangle::Triangle(const std::vector<std::string> &args) {
        RequireArgumentsSize(TARGET_ARGUMENTS_SIZE, args);
        for (const auto& i : targetIndexes)
        {
            vertices.emplace_back(
                std::stod(args[i]),
                std::stod(args[i+1])
            );
        }
    }

    void Triangle::Move(double dx, double dy) {
        for (auto& verticle : vertices)
        {
            verticle.Move(dx, dy);
        }
    }

    void Triangle::Draw()
    {
    }

    std::string Triangle::GetArgsAsString() {
        std::string result;
        for (const auto& vecticle : vertices) {
            auto coords = vecticle.GetCoords();
            result += ConvertNumberToString(coords.first) + ' ' + ConvertNumberToString(coords.second);
        }
        return result;
    }

    std::string Triangle::GetStrategyName() {
        return TriangleStrategyName::GetStrategyName();
    }

    template class AutoRegisterStrategy<Triangle, TriangleStrategyName>;
}
