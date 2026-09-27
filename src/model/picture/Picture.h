#ifndef OOD_L1_SHAPES_PICTURE_H
#define OOD_L1_SHAPES_PICTURE_H

#include <iostream>
#include <string>
#include <vector>
#include "../Shape.h"
#include "../../gfx/abstract/ICanvas.h"
#include "../../strategy/abstract/IStrategyStorage.h"
#include "../shapeStorage/IShapeStorage.h"
#include "../observe/picture/IPictureObserver.h"
#include "commandData/AddShapeData.h"
#include "commandData/ChangeColorData.h"
#include "commandData/ChangeShapeData.h"
#include "commandData/DeleteShapeData.h"
#include "commandData/DrawShapeData.h"
#include "commandData/MovePictureData.h"
#include "commandData/MoveShapeData.h"

namespace model {
    class Picture : public IShapeObserver
    {
    public:
        Picture(
            std::unique_ptr<IShapeStorage> shapeStorage,
            std::unique_ptr<strategy::IStrategyStorage> strategyStorage,
            std::unique_ptr<gfx::ICanvas> canvas
        ) : m_shapeStorage(std::move(shapeStorage)),
            m_strategyStorage(std::move(strategyStorage)),
            m_canvas(std::move(canvas))
        {
        }

        void AddShape(const AddShapeData& data);
        void MoveShape(const MoveShapeData& data);
        void DeleteShape(const DeleteShapeData& data);
        void ChangeColor(const ChangeColorData& data);
        void ChangeShape(const ChangeShapeData& data);
        void DrawShape(const DrawShapeData& data);
        void List(std::ostream& output = std::cout);
        void MovePicture(const MovePictureData& data);
        void DrawPicture();
        void OnShapeChange(const ShapeEvent &shapeEvent) override;
        void SubscribePictureObserver(IPictureObserver* pictureObserver);
        void UnsubscribePictureObserver(IPictureObserver* pictureObserver);
    private:
        ObserverStorage<IPictureObserver> m_observerStorage;
        std::unique_ptr<IShapeStorage> m_shapeStorage;
        std::unique_ptr<strategy::IStrategyStorage> m_strategyStorage;
        std::unique_ptr<gfx::ICanvas> m_canvas;
        std::shared_ptr<Shape> GetExistingShape(const std::string &id);
        std::unique_ptr<strategy::IShapeStrategy> GetExistingStrategy(const std::string& shapeType, const std::vector<std::string>& args);

        void RequireShapeDoesNotExist(const std::string& id);
        void ShowShapes(const std::vector<std::shared_ptr<Shape>>& shapes);
        void NotifyPicturesObservers(const std::string& msg);
    };
}


#endif //OOD_L1_SHAPES_PICTURE_H
