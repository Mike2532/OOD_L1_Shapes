#include "./Text.h"

namespace strategy {
    Text::Text(const std::vector<std::string> &args) {
        RequireArgumentsSize(4, args);

        pivotPoint = Point(
            std::stod(args[0]),
            std::stod(args[1])
        );

        m_textSize = std::stod(args[2]);
        RequireNumberIsNonNegative("text size", m_textSize);

        m_text = args[3];
    }

    void Text::Move(double dx, double dy) {
        pivotPoint.Move(dx, dy);
    }

    void Text::Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color)
    {
        canvas->SetColor(color);
        canvas->DrawText(
            pivotPoint.GetCoords().first,
            pivotPoint.GetCoords().second,
            m_textSize,
            m_text
        );
    }

    std::string Text::GetArgsAsString() {
        auto coords = pivotPoint.GetCoords();
        return ConvertNumberToString(coords.first) + ' ' +
            ConvertNumberToString(coords.second) + ' ' +
            ConvertNumberToString(m_textSize) + ' ' + m_text;
    }

    std::string Text::GetStrategyName() {
        return TextStrategyName::GetStrategyName();
    }

    template class StrategyRegister<Text, TextStrategyName>;
}
