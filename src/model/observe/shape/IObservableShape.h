#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include "ShapeEvent.h"
#include "../Subscription.h"
#include "../../SubscribeIdProvider.h"
#include "../signal/SignalManager.h"

namespace model {
    class IObservableShape
    {
    public:
        virtual ~IObservableShape() = default;

        Subscription SubscribeToMove(const std::function<void(ShapeMovedEvent)>& handler)
        {
            return SubscribeToSignal(handler, m_movedSignal);
        }

        Subscription SubscribeToChangedStrategy(const std::function<void(ShapeChangedStrategyEvent)> &handler)
        {
            return SubscribeToSignal(handler, m_changedStrategySignal);
        }

        Subscription SubscribeToChangedColor(const std::function<void(ShapeChangedColorEvent)>& handler)
        {
            return SubscribeToSignal(handler, m_changedColorSignal);
        }

        std::vector<int> GetSubscriptionIds()
        {
            return m_subscriptionIds;
        }
    private:
        template <typename T>
        Subscription SubscribeToSignal(
            const std::function<void(T)>& handler,
            SignalManager<T>& signalManager
        ) {
            const auto subscriptionId = SubscribeIdProvider::GetNextSubscribeId();
            signalManager.AddObserver(handler, subscriptionId);
            auto callback = [subscriptionId, &signalManager] () {
                signalManager.RemoveObserver(subscriptionId);
            };
            m_subscriptionIds.emplace_back(subscriptionId);
            return Subscription(callback, subscriptionId);
        }

        std::vector<int> m_subscriptionIds;
    protected:
        SignalManager<ShapeMovedEvent> m_movedSignal;
        SignalManager<ShapeChangedColorEvent> m_changedColorSignal;
        SignalManager<ShapeChangedStrategyEvent> m_changedStrategySignal;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H