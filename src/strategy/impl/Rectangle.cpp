#include "./Rectangle.h"

namespace strategy {
    Rectangle::Rectangle(const std::vector<std::string> &args) {
        RequireArgumentsSize(TARGET_ARGUMENTS_SIZE, args);

        pivotPoint = Point(
            std::stod(args[0]),
            std::stod(args[1])
        );

        m_width = std::stod(args[2]);
        m_height = std::stod(args[3]);

        RequireNumberIsNonNegative("width", m_width);
        RequireNumberIsNonNegative("height", m_height);
    }

    void Rectangle::Move(double dx, double dy) {
        pivotPoint.Move(dx, dy);
    }

    void Rectangle::Draw()
    {
    }

    std::string Rectangle::GetArgsAsString() {
        auto coords = pivotPoint.GetCoords();
        return ConvertNumberToString(coords.first) + ' ' +
            ConvertNumberToString(coords.second) + ' ' +
            ConvertNumberToString(m_width) + ' ' + ConvertNumberToString(m_height);
    }

    std::string Rectangle::GetStrategyName() {
        return RectangleStrategyName::GetStrategyName();
    }

    template class AutoRegisterStrategy<Rectangle, RectangleStrategyName>;
}
