#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include "../../observe/storage/ObserverStorage.h"
#include "IShapeObserver.h"

namespace model {
    class IObservableShape
    {
    public:
        virtual ~IObservableShape() = default;

        void Subscribe(IShapeObserver* observer)
        {
            m_observerStorage.AddObserver(observer);
        }

        void Unsubscribe(IShapeObserver* observer)
        {
            m_observerStorage.RemoveObserver(observer);
        }
    protected:
        void Notify(const ShapeEventType& eventType) {
            const auto event = ConstructEvent(eventType);

            auto observers = m_observerStorage.GetObservers();
            for (const auto& observer : observers) {
                if (observer->isRemoved || observer->observer == nullptr) {
                    continue;
                }
                observer->observer->OnShapeChange(event);
            }

            m_observerStorage.Unlock();
        }
    private:
        ObserverStorage<IShapeObserver> m_observerStorage;

        virtual ShapeEvent ConstructEvent(const ShapeEventType& event) = 0;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H