#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/gfx/impl/SFMLCanvas.h"
#include "src/model/observe/picture/PictureObserver.h"
#include "src/model/picture/Picture.h"
#include "src/model/shapeStorage/ShapeStorage.h"
#include "src/parser/Parser.h"
#include "src/strategy/abstract/StrategyStorage.h"

const unsigned W = 800;
const unsigned H = 600;
std::string fontPath = "/System/Library/Fonts/Helvetica.ttc";

std::unique_ptr<model::Picture> GetPictureWithCanvas(sf::RenderWindow& window, sf::Font font)
{
    auto canvas = std::make_unique<gfx::SFMLCanvas>(window, font);

    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();
    return std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        std::move(canvas)
    );
}

//todo у домика почему то земля и небо некорректно рисуется
int main() {
    sf::RenderWindow window(sf::VideoMode({W, H}), "Shapes");

    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font file: " + fontPath);
    }

    auto picture = GetPictureWithCanvas(window, font);


    auto pictureObserver = std::make_shared<model::PictureObserver>();
    picture->SubscribePictureObserver(pictureObserver);

    auto parser = parser::Parser(std::move(picture));
    parser.ListenAndServe();
}
