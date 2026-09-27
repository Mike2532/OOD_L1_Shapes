#ifndef OOD_L1_SHAPES_CHANGESHAPEDATA_H
#define OOD_L1_SHAPES_CHANGESHAPEDATA_H

#include <string>
#include <vector>

struct ChangeShapeData
{
    const std::string id;
    const std::string shapeType;
    const std::vector<std::string> args;
};

#endif //OOD_L1_SHAPES_CHANGESHAPEDATA_H