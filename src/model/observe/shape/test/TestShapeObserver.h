#ifndef OOD_L1_SHAPES_TESTSHAPEOBSERVER_H
#define OOD_L1_SHAPES_TESTSHAPEOBSERVER_H
#include "../IShapeObserver.h"

class TestShapeObserver : public model::IShapeObserver
{
public:
    void OnShapeChange(const model::ShapeEvent &shapeEvent) override
    {
        m_lastShapeId = shapeEvent.shapeId;
        m_lastShapeMsg = shapeEvent.msg;
        notificationsCounter++;
    }

    std::string GetLastShapeId() {
        return m_lastShapeId;
    }

    std::string GetLastShapeMsg() {
        return m_lastShapeMsg;
    }

    int GetNotificationsCounter() {
        return notificationsCounter;
    }
private:
    std::string m_lastShapeId;
    std::string m_lastShapeMsg;
    int notificationsCounter = 0;
};

#endif //OOD_L1_SHAPES_TESTSHAPEOBSERVER_H