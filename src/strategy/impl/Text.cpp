#include "./Text.h"

namespace strategy {
    Text::Text(const std::vector<std::string> &args) {
        RequireMinimalArguments(4, args);

        pivotPoint = Point(
            std::stod(args[0]),
            std::stod(args[1])
        );

        m_textSize = std::stod(args[2]);
        RequireNumberIsNonNegative("text size", m_textSize);

        std::string text;
        auto argsSize = args.size();
        for (int i = 3; i < argsSize; i++) {
            text += args[i];
            if (i != argsSize - 1) {
                text += ' ';
            }
        }
        m_text = text;
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
        auto coords = GetCoords();
        return coords + ' ' + ConvertNumberToString(m_textSize) + ' ' + m_text;
    }

    std::string Text::GetStrategyName() {
        return TextStrategyName::GetStrategyName();
    }

    std::string Text::GetCoords()
    {
        auto coords = pivotPoint.GetCoords();
        return ConvertNumberToString(coords.first) + ' ' +
            ConvertNumberToString(coords.second);
    }

    template class StrategyRegister<Text, TextStrategyName>;
}
