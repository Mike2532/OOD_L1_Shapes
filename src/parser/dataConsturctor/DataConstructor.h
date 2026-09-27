#ifndef OOD_L1_SHAPES_DATACONSTRUCTOR_H
#define OOD_L1_SHAPES_DATACONSTRUCTOR_H

#include <sstream>
#include "../../model/picture/commandData/AddShapeData.h"
#include "../../model/picture/commandData/ChangeColorData.h"
#include "../../model/picture/commandData/ChangeShapeData.h"
#include "../../model/picture/commandData/DeleteShapeData.h"
#include "../../model/picture/commandData/DrawShapeData.h"
#include "../../model/picture/commandData/MovePictureData.h"
#include "../../model/picture/commandData/MoveShapeData.h"
#include "../exception/DataConstructException.h"

namespace parser {
    class DataConstructor
    {
    public:
        AddShapeData ConstructAddShapeData(std::stringstream& input)
        {
            std::string id;
            std::string color;
            std::string shapeType;
            if (!(input >> id >> color >> shapeType)) {
                throw DataConstructException("can not construct AddShapeData");
            }

            std::vector<std::string> args;
            std::string arg;
            while (input >> arg) {
                args.push_back(arg);
            }

            return AddShapeData(id, color, shapeType, args);
        }

        MoveShapeData ConstructMoveShapeData(std::stringstream& input)
        {
            std::string id;
            double dx;
            double dy;
            if (!(input >> id >> dx >> dy)) {
                throw DataConstructException("can not construct MoveShapeData");
            }
            return MoveShapeData(id, dx, dy);
        }

        DeleteShapeData ConstructDeleteShapeData(std::stringstream& input)
        {
            std::string id;
            if (!(input >> id)) {
                throw DataConstructException("can not construct DeleteShapeData");
            }
            return DeleteShapeData(id);
        }

        ChangeColorData ConstructChangeColorData(std::stringstream& input)
        {
            std::string id;
            std::string color;
            if (!(input >> id >> color)) {
                throw DataConstructException("can not construct ChangeColorData");
            }
            return ChangeColorData(id, color);
        }

        ChangeShapeData ConstructChangeShapeData(std::stringstream& input)
        {
            std::string id;
            std::string shapeType;
            if (!(input >> id >> shapeType)) {
                throw DataConstructException("can not construct ChangeShapeData");
            }
            std::vector<std::string> args;
            std::string arg;
            while (input >> arg) {
                args.push_back(arg);
            }
            return ChangeShapeData(id, shapeType);
        }

        DrawShapeData ConstructDrawShapeData(std::stringstream& input)
        {
            std::string id;
            if (!(input >> id)) {
                throw DataConstructException("can not construct DrawShapeData");
            }
            return DrawShapeData(id);
        }

        MovePictureData ConstructMovePictureData(std::stringstream& input)
        {
            double dx;
            double dy;
            if (!(input >> dx >> dy)) {
                throw DataConstructException("can not construct MovePictureData");
            }
            return MovePictureData(dx, dy);
        }
    };
}

#endif //OOD_L1_SHAPES_DATACONSTRUCTOR_H