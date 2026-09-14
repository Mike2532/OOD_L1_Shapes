#ifndef OOD_L1_SHAPES_PICTURE_H
#define OOD_L1_SHAPES_PICTURE_H

#include <iostream>
#include <string>
#include <vector>
#include "../Shape.h"
#include "../../strategy/abstract/IStrategyStorage.h"
#include "../shapeStorage/IShapeStorage.h"

namespace model {
    class Picture
    {
    public:
        Picture(
            std::unique_ptr<IShapeStorage> shapeStorage,
            std::unique_ptr<strategy::IStrategyStorage> strategyStorage
        ) : m_shapeStorage(std::move(shapeStorage)), m_strategyStorage(std::move(strategyStorage))
        {
        }

        void AddShape(const std::string& id, std::string color, const std::string& shapeType, const std::vector<std::string>& args);
        void MoveShape(const std::string& id, double dx, double dy);
        void DeleteShape(const std::string& id);
        void ChangeColor(const std::string& id, const std::string& color);
        void ChangeShape(const std::string& id, const std::string& shapeType, const std::vector<std::string>& args);
        void DrawShape(const std::string& id);
        void List(std::ostream& output = std::cout);
        void MovePicture(double dx, double dy);
        void DrawPicture();
    private:
        std::unique_ptr<IShapeStorage> m_shapeStorage;
        std::unique_ptr<strategy::IStrategyStorage> m_strategyStorage;

        std::shared_ptr<Shape> GetExistingShape(const std::string &id);
        std::unique_ptr<strategy::IShapeStrategy> GetExistingStrategy(const std::string& shapeType, const std::vector<std::string>& args);
        void RequireShapeDoesNotExist(const std::string& id);
    };
}


#endif //OOD_L1_SHAPES_PICTURE_H
