#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/gfx/impl/SFMLCanvas.h"

int main()
{
    std::string userInput;
    while (std::getline(std::cin, userInput)) {
        if (userInput.empty()) {
            continue;
        }

        std::stringstream stream(userInput);
    }


    //
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
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                canvas->Close();
            }
        }
        canvas->Clear();

        canvas->SetColor("#ddee33");
        canvas->LineTo(200, 300);
        canvas->MoveTo(400, 200);
        canvas->DrawEllipse(100, 50, 200, 200);
        canvas->DrawText(250, 250, 25, "hello world");

        canvas->Display();
    }
}
