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

    void Circle::Draw()
    {
    }

    std::string Circle::GetArgsAsString() {
        auto coords = pivotPoint.GetCoords();
        return ConvertNumberToString(coords.first) + ' ' + ConvertNumberToString(coords.second) + ' ' + ConvertNumberToString(m_radius);
    }

    std::string Circle::GetStrategyName() {
        return CircleStrategyName::GetStrategyName();
    }

    template class AutoRegisterStrategy<Circle, CircleStrategyName>;
}
