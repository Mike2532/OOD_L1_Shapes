#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include "IShapeObserver.h"
#include "../storage/ObserverService.h"

namespace model {
    class IObservableShape
    {
    public:
        virtual ~IObservableShape() = default;

        void Subscribe(const std::weak_ptr<IObserverElem<ShapeEvent>>& observer)
        {
            m_observerService.AddElement(observer);
        }

        void Unsubscribe(const std::weak_ptr<IObserverElem<ShapeEvent>>& observer)
        {
            m_observerService.RemoveElement(observer);
        }
    protected:
        void Notify(const ShapeEventType& eventType) {
            const auto event = ConstructEvent(eventType);
            m_observerService.NotifyAll(event);
        }
    private:
        ObserverService<ShapeEvent> m_observerService;

        virtual ShapeEvent ConstructEvent(const ShapeEventType& event) = 0;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H