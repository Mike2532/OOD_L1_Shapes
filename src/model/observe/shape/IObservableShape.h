#ifndef OOD_L1_SHAPES_INOTIFICATEDSHAPE_H
#define OOD_L1_SHAPES_INOTIFICATEDSHAPE_H

#include "ShapeEvent.h"
#include "../../SubscribeIdProvider.h"
#include <boost/signals2.hpp>

namespace model {
    class IObservableShape
    {
    public:
        virtual ~IObservableShape() = default;

        boost::signals2::scoped_connection SubscribeToMove(const std::function<void(ShapeMovedEvent)>& handler)
        {
            return m_movedSignal.connect(handler);
        }

        boost::signals2::scoped_connection SubscribeToChangedStrategy(const std::function<void(ShapeChangedStrategyEvent)> &handler)
        {
            return m_changedStrategySignal.connect(handler);
        }

        boost::signals2::scoped_connection SubscribeToChangedColor(const std::function<void(ShapeChangedColorEvent)>& handler)
        {
            return m_changedColorSignal.connect(handler);
        }
    protected:
        boost::signals2::signal<void(const ShapeMovedEvent&)> m_movedSignal;
        boost::signals2::signal<void(const ShapeChangedColorEvent&)> m_changedColorSignal;
        boost::signals2::signal<void(const ShapeChangedStrategyEvent&)> m_changedStrategySignal;
    };
}

#endif //OOD_L1_SHAPES_INOTIFICATEDSHAPE_H