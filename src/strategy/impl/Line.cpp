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
        if (vertices[0].GetCoords() == vertices[1].GetCoords()) {
            throw std::invalid_argument("cannot construct line from same points");
        }
    }

    void Line::Move(double dx, double dy) {
        for (auto& verticle : vertices)
        {
            verticle.Move(dx, dy);
        }
    }

    void Line::Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color)
    {
        canvas->SetColor(color);

        auto startCoords = vertices[0].GetCoords();
        auto endCoords = vertices[1].GetCoords();

        canvas->MoveTo(startCoords.first, startCoords.second);
        canvas->LineTo(endCoords.first, endCoords.second);
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

    template class StrategyRegister<Line, LineStrategyName>;
}
