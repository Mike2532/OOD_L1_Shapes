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
        auto firstCoord = vertices[0].GetCoords();
        auto secondCoord = vertices[1].GetCoords();
        auto thirdCoord = vertices[2].GetCoords();
        if (firstCoord == secondCoord || secondCoord == thirdCoord || firstCoord == thirdCoord) {
            throw std::invalid_argument("can not construct triangle from same points");
        }
    }

    void Triangle::Move(double dx, double dy) {
        for (auto& verticle : vertices)
        {
            verticle.Move(dx, dy);
        }
    }

    void Triangle::Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color)
    {
        auto startCoords = vertices[0].GetCoords();
        canvas->MoveTo(startCoords.first, startCoords.second);
        canvas->LineTo(vertices[1].GetCoords().first, vertices[1].GetCoords().second);
        canvas->LineTo(vertices[2].GetCoords().first, vertices[2].GetCoords().second);
        canvas->LineTo(vertices[0].GetCoords().first, vertices[0].GetCoords().second);
    }

    std::string Triangle::GetArgsAsString() {
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

    std::string Triangle::GetStrategyName() {
        return TriangleStrategyName::GetStrategyName();
    }

    template class StrategyRegister<Triangle, TriangleStrategyName>;
}
