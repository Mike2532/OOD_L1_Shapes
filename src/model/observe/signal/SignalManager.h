#ifndef OOD_L1_SHAPES_SIGNALMANAGER_H
#define OOD_L1_SHAPES_SIGNALMANAGER_H
#include <functional>
#include <list>

namespace model {
    template<typename T>
    struct StoredSignal
    {
        int subscriptionId;
        std::function<void(T)> observer;
        bool isDeleted = false;
    };

    template<typename T>
    class SignalManager
    {
    public:
        void AddObserver(const std::function<void(T)>& observer, int subscriptionId)
        {
            if (!observer) {
                return;
            }

            for (const auto& existingSignal : m_signals) {
                if (subscriptionId == existingSignal.subscriptionId) {
                    return;
                }
            }
            m_signals.emplace_back(StoredSignal<T>(subscriptionId, observer));
        }

        void RemoveObserver(int subscriptionId) {
            for (auto& existingSignal : m_signals) {
                if (subscriptionId == existingSignal.subscriptionId) {
                    existingSignal.isDeleted = true;
                    return;
                }
            }
        }

        void NotifyAll(const T& value)
        {
            if (m_signals.empty()) {
                return;
            }
            auto lastElem = std::prev(m_signals.end());
            for (auto it = m_signals.begin(); ; ++it) {
                if (!it->isDeleted) {
                    if (auto observer = it->observer) {
                        observer(value);
                    } else {
                        it->isDeleted = true;
                    }
                }
                if (it == lastElem) {
                    break;
                }
            }
            m_signals.remove_if([](const StoredSignal<T>& signal) {
                return signal.isDeleted;
            });
        }
    private:
        std::list<StoredSignal<T>> m_signals;
    };
}

#endif //OOD_L1_SHAPES_SIGNALMANAGER_H