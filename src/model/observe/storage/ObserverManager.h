#ifndef OOD_L1_SHAPES_OBSERVERSTORAGETWO_H
#define OOD_L1_SHAPES_OBSERVERSTORAGETWO_H

#include <list>
#include "../IObserverElem.h"

namespace model {
    template <typename T>
    struct StoredObserver
    {
        std::weak_ptr<IObserverElem<T>> observer;
        bool isDeleted = false;
    };

    template <typename T>
    class ObserverManager
    {
    public:
        void AddElement(std::weak_ptr<IObserverElem<T>> elem)
        {
            auto newShared = elem.lock();
            if (!newShared) {
                return;
            }

            for (const auto& existingElem : m_elems) {
                auto existingShared = existingElem.observer.lock();
                if (existingShared && existingShared.get() == newShared.get()) {
                    return;
                }
            }

            m_elems.push_back({elem, false});
        }

        void RemoveElement(std::weak_ptr<IObserverElem<T>> elem)
        {
            auto targetShared = elem.lock();
            if (!targetShared) {
                return;
            }

            for (auto& existingElem : m_elems) {
                auto existingShared = existingElem.observer.lock();
                if (existingShared && existingShared.get() == targetShared.get()) {
                    existingElem.isDeleted = true;
                    return;
                }
            }
        }

        void NotifyAll(const T& event)
        {
            if (m_elems.empty()) {
                return;
            }

            auto lastElem = std::prev(m_elems.end());

            for (auto it = m_elems.begin(); ; ++it) {
                if (!it->isDeleted) {
                    if (auto observer = it->observer.lock()) {
                        observer->OnChange(event);
                    } else {
                        it->isDeleted = true;
                    }
                }
                if (it == lastElem) {
                    break;
                }
            }

            m_elems.remove_if([](const StoredObserver<T>& node) {
                return node.isDeleted || node.observer.expired();
            });
        }

    private:
        std::list<StoredObserver<T>> m_elems;
    };
}

#endif // OOD_L1_SHAPES_OBSERVERSTORAGETWO_H