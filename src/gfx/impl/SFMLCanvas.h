#ifndef OOD_L1_SHAPES_SFMLCANVAS_H
#define OOD_L1_SHAPES_SFMLCANVAS_H

#include <SFML/Graphics.hpp>

#include "../abstract/ICanvas.h"

namespace gfx {
    class SFMLCanvas : public ICanvas
    {
    public:
        SFMLCanvas(sf::RenderWindow& window, sf::Font& font);

        void SetColor(const std::string& color) override;
        void MoveTo(double x, double y) override;
        void LineTo(double x, double y) override;
        void DrawEllipse(double cx, double cy, float rx, double ry) override;
        void DrawText(double left, double top, double fontSize, const std::string &text) override;
        void Clear() override;
        void Display() override;
        void Close() override;
        bool IsActive() override;
        bool NeedToClose() override;
    private:
        static constexpr int ELLIPSE_POINT_COUNT = 100;
        static constexpr float BASE_RADIUS = 1.f;
        static constexpr float LINE_THICKNESS = 7.f;

        sf::Vector2f m_drawPoint;
        sf::Color m_color;
        sf::RenderWindow& m_window;
        sf::Font& m_font;

        sf::Color ConvertColorToSFMLColor(const std::string& color);
        int ConvertHexStringToDecemicalNumber(const std::string& hexString);
    };
}

#endif //OOD_L1_SHAPES_SFMLCANVAS_H