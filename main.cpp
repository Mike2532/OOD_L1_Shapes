#include "src/model/picture/Picture.h"
#include "src/model/shapeStorage/ShapeStorage.h"
#include "src/strategy/abstract/StrategyStorage.h"

int main()
{
    auto shapeStorage = std::make_unique<model::ShapeStorage>();
    auto strategyStorage = std::make_unique<strategy::StrategyStorage>();

    auto picture = std::make_unique<model::Picture>(
        std::move(shapeStorage),
        std::move(strategyStorage)
    );

    picture->AddShape("rectangleOne", "#ffffff", "rectangle", std::vector<std::string>{"1", "2","3", "4"});
    picture->AddShape("circleOne", "#ffffff", "circle", std::vector<std::string>{"1", "2","3"});
    picture->AddShape("lineOne", "#ffffff", "line", std::vector<std::string>{"1", "2","3", "4"});
    picture->AddShape("triangleOne", "#ffffff", "triangle", std::vector<std::string>{"1", "2","3", "1", "2","3"});
    picture->AddShape("textOne", "#ffffff", "text", std::vector<std::string>{"1", "2","3", "hello world"});
    picture->List();
}
