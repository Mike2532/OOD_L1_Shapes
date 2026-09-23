#ifndef OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H
#define OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H

#include <functional>
#include "../IShapeObserver.h"

class CallbackTestObserver : public model::IShapeObserver
{
public:
    void OnShapeChange(const model::ShapeEvent &shapeEvent) override {
        m_callCount++;
        if (m_executable != nullptr) {
            m_executable();
        }
    }

    void SetExecutable(const std::function<void()>& executable) {
        this->m_executable = executable;
    }

    int GetCallCount() {
        return m_callCount;
    }
private:
    std::function<void()> m_executable = nullptr;
    int m_callCount = 0;
};

#endif //OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H