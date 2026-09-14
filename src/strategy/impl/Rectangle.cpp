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

    void Rectangle::Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color)
    {
        canvas->SetColor(color);

        auto coords = pivotPoint.GetCoords();
        auto xPos = coords.first;
        auto yPos = coords.second;

        canvas->MoveTo(xPos, yPos);

        canvas->LineTo(xPos + m_width, yPos);
        canvas->LineTo(xPos + m_width, yPos + m_height);
        canvas->LineTo(xPos, yPos + m_height);
        canvas->LineTo(xPos, yPos);
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

    template class StrategyRegister<Rectangle, RectangleStrategyName>;
}
