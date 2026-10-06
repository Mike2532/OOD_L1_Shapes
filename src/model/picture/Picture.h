#ifndef OOD_L1_SHAPES_PICTURE_H
#define OOD_L1_SHAPES_PICTURE_H

#include <iostream>
#include <string>
#include <vector>
#include "../Shape.h"
#include "../../gfx/abstract/ICanvas.h"
#include "../../strategy/abstract/IStrategyStorage.h"
#include "../shapeStorage/IShapeStorage.h"
#include "commandData/AddShapeData.h"
#include "commandData/ChangeColorData.h"
#include "commandData/ChangeShapeData.h"
#include "commandData/DeleteShapeData.h"
#include "commandData/DrawShapeData.h"
#include "commandData/MovePictureData.h"
#include "commandData/MoveShapeData.h"
#include "../observe/picture/PictureEvent.h"

namespace model {
    class Picture
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

        Subscription SubscribeToShapeRemoved(const std::function<void(ShapeRemovedEvent)>& handler);
        Subscription SubscribeToShapeAdded(const std::function<void(ShapeAddedEvent)>& handler);
        Subscription SubscribeToMove(const std::function<void(ShapeMovedEvent)>& handler);
        Subscription SubscribeToChangedStrategy(const std::function<void(ShapeChangedStrategyEvent)> &handler);
        Subscription SubscribeToChangedColor(const std::function<void(ShapeChangedColorEvent)>& handler);

    private:
        std::unique_ptr<IShapeStorage> m_shapeStorage;
        std::unique_ptr<strategy::IStrategyStorage> m_strategyStorage;
        std::unique_ptr<gfx::ICanvas> m_canvas;
        std::vector<Subscription> m_subscriptions;
        std::shared_ptr<Shape> GetExistingShape(const std::string &id);
        std::unique_ptr<strategy::IShapeStrategy> GetExistingStrategy(const std::string& shapeType, const std::vector<std::string>& args);
        int m_subscriptionId;

        SignalManager<ShapeMovedEvent> m_movedSignal;
        SignalManager<ShapeChangedColorEvent> m_changedColorSignal;
        SignalManager<ShapeChangedStrategyEvent> m_changedStrategySignal;
        SignalManager<ShapeAddedEvent> m_shapeAddedSignal;
        SignalManager<ShapeRemovedEvent> m_shapeRemovedSignal;

        void RequireShapeDoesNotExist(const std::string& id);
        void ShowShapes(const std::vector<std::shared_ptr<Shape>>& shapes);
        void OnShapeMoved(const ShapeMovedEvent& event);
        void OnShapeChangedStrategy(const ShapeChangedStrategyEvent& event);
        void OnShapeChangedColor(const ShapeChangedColorEvent& event);

        template <typename T>
        Subscription SubscribeToSignal(const std::function<void(T)>& handler,SignalManager<T>& signalManager)
        {
            const auto subscriptionId = SubscribeIdProvider::GetNextSubscribeId();
            signalManager.AddObserver(handler, subscriptionId);
            auto callback = [subscriptionId, &signalManager] () {
                signalManager.RemoveObserver(subscriptionId);
            };
            m_subscriptionId = subscriptionId;
            return Subscription(callback, subscriptionId);
        }
    };
}


#endif //OOD_L1_SHAPES_PICTURE_H
