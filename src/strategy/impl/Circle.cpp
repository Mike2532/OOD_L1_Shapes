#include "./Circle.h"

namespace strategy {
    Circle::Circle(const std::vector<std::string> &args) {
        RequireArgumentsSize(TARGET_ARGUMENTS_SIZE, args);

        pivotPoint = Point(
            std::stod(args[0]),
            std::stod(args[1])
        );

        m_radius = std::stod(args[2]);

        RequireNumberIsNonNegative("raduis", m_radius);
    }

    void Circle::Move(double dx, double dy) {
        pivotPoint.Move(dx, dy);
    }

    void Circle::Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color)
    {
        canvas->SetColor(color);
        auto coords = pivotPoint.GetCoords();
        canvas->DrawEllipse(coords.first, coords.second, m_radius, m_radius);
    }

    std::string Circle::GetArgsAsString() {
        auto coords = GetCoords();
        return coords + ' ' + ConvertNumberToString(m_radius);
    }

    std::string Circle::GetStrategyName() {
        return CircleStrategyName::GetStrategyName();
    }

    std::string Circle::GetCoords() {
        auto coords = pivotPoint.GetCoords();
        return ConvertNumberToString(coords.first) + ' ' + ConvertNumberToString(coords.second);
    }

    template class StrategyRegister<Circle, CircleStrategyName>;
}
