#ifndef OOD_L1_SHAPES_PICTUREEVENT_H
#define OOD_L1_SHAPES_PICTUREEVENT_H

#include <string>

namespace model {
    struct PictureEvent
    {
        const std::string msg;
    };

    struct ShapeAddedEvent
    {
        const std::string shapeId;
    };

    struct ShapeRemovedEvent
    {
        const std::string shapeId;
    };
}

#endif //OOD_L1_SHAPES_PICTUREEVENT_H