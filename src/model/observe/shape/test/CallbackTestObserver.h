#ifndef OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H
#define OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H

#include <functional>

template <typename EventType>
class CallbackTestObserver
{
public:
    void OnEvent(const EventType&)
    {
        m_callCount++;
        if (m_executable) {
            m_executable();
        }
    }

    void SetExecutable(const std::function<void()>& executable) {
        this->m_executable = executable;
    }

    int GetCallCount() const {
        return m_callCount;
    }

private:
    std::function<void()> m_executable;
    int m_callCount = 0;
};

#endif // OOD_L1_SHAPES_CALLBACKTESTOBSERVER_H