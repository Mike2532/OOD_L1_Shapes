#ifndef OOD_L1_SHAPES_EVENT_H
#define OOD_L1_SHAPES_EVENT_H
#include <string>

enum class ShapeEventType {
    ColorChanged,
    StrategyChanged,
    ShapeMoved,
};

struct ShapeEvent
{
    const std::string shapeId;
    const std::string msg;
};

#endif //OOD_L1_SHAPES_EVENT_H