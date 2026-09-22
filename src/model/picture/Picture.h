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

        void AddShape(const std::string& id, std::string color, const std::string& shapeType, const std::vector<std::string>& args);
        void MoveShape(const std::string& id, double dx, double dy);
        void DeleteShape(const std::string& id);
        void ChangeColor(const std::string& id, const std::string& color);
        void ChangeShape(const std::string& id, const std::string& shapeType, const std::vector<std::string>& args);
        void DrawShape(const std::string& id);
        void List(std::ostream& output = std::cout);
        void MovePicture(double dx, double dy);
        void DrawPicture();
        void OnShapeChange(const ShapeEvent &shapeEvent) override;
        void SubscribePictureObserver(IPictureObserver* pictureObserver);
        void UnsubscribePictureObserver(IPictureObserver* pictureObserver);
    private:
        std::unique_ptr<IShapeStorage> m_shapeStorage;
        std::unique_ptr<strategy::IStrategyStorage> m_strategyStorage;
        std::unique_ptr<gfx::ICanvas> m_canvas;

        std::vector<IPictureObserver*> m_pictureObservers;


        std::shared_ptr<Shape> GetExistingShape(const std::string &id);
        std::unique_ptr<strategy::IShapeStrategy> GetExistingStrategy(const std::string& shapeType, const std::vector<std::string>& args);
        void RequireShapeDoesNotExist(const std::string& id);
        void ShowShapes(const std::vector<std::shared_ptr<Shape>>& shapes);
    };
}


#endif //OOD_L1_SHAPES_PICTURE_H
