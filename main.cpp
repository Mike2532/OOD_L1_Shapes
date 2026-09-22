#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/gfx/impl/SFMLCanvas.h"
#include "src/model/observe/picture/PictureObserver.h"
#include "src/model/picture/Picture.h"
#include "src/model/shapeStorage/ShapeStorage.h"
#include "src/strategy/abstract/StrategyStorage.h"

const unsigned W = 800;
const unsigned H = 600;
std::string fontPath = "/System/Library/Fonts/Helvetica.ttc";

std::unique_ptr<model::Picture> GetPicture()
{
    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();
    return std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage),
        nullptr
    );
}

int main() {
    auto pictureObserver = PictureObserver();

    auto picture = GetPicture();
    picture->SubscribePictureObserver(&pictureObserver);

    std::string defaultColor = "#ffffff";

    std::string fistShapeId = "fistShapeId";
    std::string firstShapeType = "circle";
    std::vector<std::string> firstShapeArgs{"1", "2","3"};

    picture->AddShape(fistShapeId, defaultColor, firstShapeType, firstShapeArgs);
    picture->MoveShape("fistShapeId", 3, 4);
    picture->ChangeColor("fistShapeId", "#000000");

    std::string secondShapeType = "line";
    std::vector<std::string> secondShapeArgs{"400", "400","600", "400"};
    picture->ChangeShape(fistShapeId, secondShapeType, secondShapeArgs);

    auto x = 0;
}

// int main()
// {
//     std::string userInput;
//     while (std::getline(std::cin, userInput)) {
//         if (userInput.empty()) {
//             continue;
//         }
//
//         std::stringstream stream(userInput);
//     }
//
//
//     //
//     const unsigned W = 800;
//     const unsigned H = 600;
//     sf::RenderWindow window(sf::VideoMode({W, H}), "Shapes");
//
//     sf::Font font;
//     std::string fontPath = "/System/Library/Fonts/Helvetica.ttc";
//     if (!font.openFromFile(fontPath)) {
//         throw std::runtime_error("Failed to load font file: " + fontPath);
//     }
//
//
//     auto canvas = std::make_unique<gfx::SFMLCanvas>(window, font);
//
//     while (canvas->IsActive()) {
//         while (const std::optional event = window.pollEvent()) {
//             if (event->is<sf::Event::Closed>()) {
//                 canvas->Close();
//             }
//         }
//         canvas->Clear();
//
//         canvas->SetColor("#ddee33");
//         canvas->LineTo(200, 300);
//         canvas->MoveTo(400, 200);
//         canvas->DrawEllipse(100, 50, 200, 200);
//         canvas->DrawText(250, 250, 25, "hello world");
//
//         canvas->Display();
//     }
// }
