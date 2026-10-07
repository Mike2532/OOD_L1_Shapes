#ifndef OOD_L1_SHAPES_TESTSHAPEOBSERVER_H
#define OOD_L1_SHAPES_TESTSHAPEOBSERVER_H

#include <string>
#include "../../../observe/shape/ShapeEvent.h"

class TestShapeObserver
{
public:
    void OnMove(const model::ShapeMovedEvent& event)
    {
        m_lastShapeId = event.shapeId;
        m_lastShapeMsg = "shape " + event.shapeId + " change coords. New coords: " + event.newCoords;
        m_notificationsCounter++;
    }

    void OnColorChanged(const model::ShapeChangedColorEvent& event)
    {
        m_lastShapeId = event.shapeId;
        m_lastShapeMsg = "shape " + event.shapeId + " change color. New color: " + event.newColor;
        m_notificationsCounter++;
    }

    void OnStrategyChanged(const model::ShapeChangedStrategyEvent& event)
    {
        m_lastShapeId = event.shapeId;
        m_lastShapeMsg = "shape " + event.shapeId + " change stategy. New strategy: " + event.newStrategyName;
        m_notificationsCounter++;
    }

    auto GetMoveHandler() {
        return [this](const model::ShapeMovedEvent& e) {
            OnMove(e);
        };
    }
    auto GetColorHandler() {
        return [this](const model::ShapeChangedColorEvent& e) {
            OnColorChanged(e);
        };
    }
    auto GetStrategyHandler() {
        return [this](const model::ShapeChangedStrategyEvent& e) {
            OnStrategyChanged(e);
        };
    }

    std::string GetLastShapeId() const {
        return m_lastShapeId;
    }
    std::string GetLastShapeMsg() const {
        return m_lastShapeMsg;
    }
    int GetNotificationsCounter() const {
        return m_notificationsCounter;
    }

private:
    std::string m_lastShapeId;
    std::string m_lastShapeMsg;
    int m_notificationsCounter = 0;
};

#endif // OOD_L1_SHAPES_TESTSHAPEOBSERVER_H