#ifndef OOD_L1_SHAPES_ADDSHAPEDATA_H
#define OOD_L1_SHAPES_ADDSHAPEDATA_H

#include <string>
#include <vector>

struct AddShapeData
{
    const std::string id;
    const std::string color;
    const std::string shapeType;
    const std::vector<std::string> args;
};

#endif //OOD_L1_SHAPES_ADDSHAPEDATA_H