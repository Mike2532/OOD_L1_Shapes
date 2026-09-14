#include "./Line.h"

namespace strategy {
    Line::Line(const std::vector<std::string> &args) {
        RequireArgumentsSize(TARGET_ARGUMENTS_SIZE, args);
        for (const auto& i : targetIndexes)
        {
            vertices.emplace_back(
                std::stod(args[i]),
                std::stod(args[i+1])
            );
        }
    }

    void Line::Move(double dx, double dy) {
        for (auto& verticle : vertices)
        {
            verticle.Move(dx, dy);
        }
    }

    void Line::Draw()
    {
    }

    std::string Line::GetArgsAsString() {
        std::string result;
        auto vecticleSize = vertices.size();
        for (auto i = 0; i < vecticleSize; i++) {
            auto vecticle = vertices[i];
            auto coords = vecticle.GetCoords();
            result += ConvertNumberToString(coords.first) + ' ' + ConvertNumberToString(coords.second);
            if (i != vecticleSize - 1) {
                result += ' ';
            }
        }
        return result;
    }

    std::string Line::GetStrategyName() {
        return LineStrategyName::GetStrategyName();
    }

    template class AutoRegisterStrategy<Line, LineStrategyName>;
}
