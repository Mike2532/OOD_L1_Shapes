#include <catch2/catch_test_macros.hpp>
#include <SFML/Graphics.hpp>

#include "../SFMLCanvas.h"

TEST_CASE("canvas withs some shapes")
{
    const unsigned W = 800;
    const unsigned H = 600;
    sf::RenderWindow window(sf::VideoMode({W, H}), "Shapes");

    sf::Font font;
    std::string fontPath = "/System/Library/Fonts/Helvetica.ttc";
    if (!font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font file: " + fontPath);
    }

    auto canvas = std::make_unique<gfx::SFMLCanvas>(window, font);

    while (canvas->IsActive()) {
        if (canvas->NeedToClose()) {
            canvas->Close();
        }

        canvas->Clear();

        canvas->SetColor("#ff0303");
        canvas->LineTo(200, 300);

        canvas->SetColor("#139e48");
        canvas->MoveTo(400, 200);

        canvas->SetColor("#1f0ccc");
        canvas->DrawEllipse(100, 50, 200, 200);
        canvas->DrawText(250, 250, 25, "hello world");

        canvas->Display();
    }
}