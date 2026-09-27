#ifndef OOD_L1_SHAPES_OBSERVERSTORAGETWO_H
#define OOD_L1_SHAPES_OBSERVERSTORAGETWO_H

#include <list>
#include "IObserverElem.h"

template <typename T>
struct ObserverNode
{
    std::weak_ptr<IObserverElem<T>> observer;
    bool isDeleted = false;
};

template <typename T>
class ObserverService
{
public:
    void AddElement(std::weak_ptr<IObserverElem<T>> elem)
    {
        auto newShared = elem.lock();
        if (!newShared) {
            return;
        }

        for (const auto& node : elems) {
            auto existingShared = node.observer.lock();
            if (existingShared && existingShared.get() == newShared.get()) {
                return;
            }
        }

        elems.push_back({elem, false});
    }

    void RemoveElement(std::weak_ptr<IObserverElem<T>> elem)
    {
        auto targetShared = elem.lock();
        if (!targetShared) {
            return;
        }

        for (auto& node : elems) {
            auto existingShared = node.observer.lock();
            if (existingShared && existingShared.get() == targetShared.get()) {
                node.isDeleted = true;
                return;
            }
        }
    }

    void NotifyAll(const T& event)
    {
        if (elems.empty()) {
            return;
        }

        auto lastElem = elems.end();
        --lastElem;

        for (auto it = elems.begin(); ; ++it) {
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

        elems.remove_if([](const ObserverNode<T>& node) {
            return node.isDeleted || node.observer.expired();
        });
    }

private:
    std::list<ObserverNode<T>> elems;
};

#endif // OOD_L1_SHAPES_OBSERVERSTORAGETWO_H