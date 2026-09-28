#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include "ShapeEvent.h"
#include "../storage/ObserverManager.h"
#include "../Subscription.h"
#include "../../SubscribeIdProvider.h"

namespace model {
    class IObservableShape
    {
    public:
        virtual ~IObservableShape() = default;

        Subscription Subscribe(const std::weak_ptr<IObserverElem<ShapeEvent>>& observer)
        {
            m_observerService.AddElement(observer);
            auto callback = [this, observer] () {
                m_observerService.RemoveElement(observer);
            };
            const auto subscriptionId = SubscribeIdProvider::GetNextSubscribeId();
            m_subscriptionId = subscriptionId;

            return Subscription(callback, subscriptionId);
        }

        int GetSubscriptionId()
        {
            return m_subscriptionId;
        }
    protected:
        void Notify(const ShapeEventType& eventType) {
            const auto event = ConstructEvent(eventType);
            m_observerService.NotifyAll(event);
        }
    private:
        ObserverManager<ShapeEvent> m_observerService;
        int m_subscriptionId;

        virtual ShapeEvent ConstructEvent(const ShapeEventType& event) = 0;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H