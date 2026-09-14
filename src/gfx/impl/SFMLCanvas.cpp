#include "SFMLCanvas.h"

namespace gfx {
    SFMLCanvas::SFMLCanvas(sf::RenderWindow& window, sf::Font& font)
        : m_window(window), m_font(font)
    {
    }

    void SFMLCanvas::SetColor(const std::string& color)
    {
        m_color = ConvertColorToSFMLColor(color);
    }

    void SFMLCanvas::MoveTo(double x, double y)
    {
        m_drawPoint.x = x;
        m_drawPoint.y = y;
    }

    void SFMLCanvas::LineTo(double x, double y)
    {
        sf::Vector2f startPoint = m_drawPoint;
        sf::Vector2f endPoint(x, y);

        sf::Vector2f direction = endPoint - startPoint;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Angle angle = sf::radians(std::atan2(direction.y, direction.x));

        sf::RectangleShape line(sf::Vector2f(length, LINE_THICKNESS));
        line.setFillColor(m_color);

        line.setOrigin(sf::Vector2f(0.0f, LINE_THICKNESS / 2));
        line.setPosition(m_drawPoint);
        line.setRotation(angle);

        m_window.draw(line);

        MoveTo(x, y);
    }

    void SFMLCanvas::DrawEllipse(double cx, double cy, float rx, double ry)
    {
        sf::CircleShape ellipse(BASE_RADIUS);
        ellipse.setPointCount(ELLIPSE_POINT_COUNT);
        ellipse.setFillColor(m_color);
        ellipse.setOutlineColor(m_color);
        ellipse.setOrigin(sf::Vector2f{1.f, 1.f});
        ellipse.setScale(sf::Vector2f{static_cast<float>(rx), static_cast<float>(ry)});
        ellipse.setPosition(sf::Vector2f{static_cast<float>(cx), static_cast<float>(cy)});
        m_window.draw(ellipse);
    }

    void SFMLCanvas::DrawText(double left, double top, double fontSize, const std::string &text)
    {
        sf::Text textToDraw(m_font, text, static_cast<unsigned int>(fontSize));
        textToDraw.setFillColor(m_color);
        textToDraw.setPosition(sf::Vector2{static_cast<float>(left), static_cast<float>(top)});
        m_window.draw(textToDraw);
    }

    void SFMLCanvas::Clear()
    {
        m_window.clear(sf::Color::White);
    }

    void SFMLCanvas::Display()
    {
        m_window.display();
    }

    void SFMLCanvas::Close()
    {
        m_window.close();
    }

    bool SFMLCanvas::IsActive()
    {
        return m_window.isOpen();
    }

    bool SFMLCanvas::NeedToClose()
    {
        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                return true;
            }
        }
        return false;
    }

    sf::Color SFMLCanvas::ConvertColorToSFMLColor(const std::string &color)
    {
        if (color.size() != 7) {
            throw std::invalid_argument("Unexpected color size");
        }

        std::vector<int> colors;

        std::vector<size_t> partsIndexes{1, 3, 5};
        for (const size_t& i : partsIndexes) {
            const std::string hexStr = {color[i],  color[i + 1]};
            colors.push_back(ConvertHexStringToDecemicalNumber(hexStr));
        }
        return sf::Color(colors[0], colors[1], colors[2], 255);
    }

    int SFMLCanvas::ConvertHexStringToDecemicalNumber(const std::string &hexString)
    {
        return std::stoi(hexString, nullptr, 16);
    }
}
