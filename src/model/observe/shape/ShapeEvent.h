#ifndef OOD_L1_SHAPES_EVENT_H
#define OOD_L1_SHAPES_EVENT_H
#include <string>

namespace model {
    struct ShapeMovedEvent
    {
        const std::string shapeId;
        const std::string newCoords;
        double dx;
        double dy;
    };

    struct ShapeChangedStrategyEvent
    {
        const std::string shapeId;
        const std::string oldStrategyName;
        const std::string newStrategyName;
    };

    struct ShapeChangedColorEvent
    {
        const std::string shapeId;
        const std::string oldColor;
        const std::string newColor;
    };
}

#endif //OOD_L1_SHAPES_EVENT_H