#ifndef OOD_L1_SHAPES_PICTUREOBSERVER_H
#define OOD_L1_SHAPES_PICTUREOBSERVER_H

#include <iosfwd>
#include <iostream>

#include "PictureEvent.h"
#include "../shape/ShapeEvent.h"

namespace model {
    class PictureObserver
    {
    public:
        explicit PictureObserver(std::ostream& output = std::cout)
                : m_output(output)
        {
        }

        void OnShapeRemoved(const ShapeRemovedEvent& event) {
            m_output << "Removed " << event.shapeId << " from Picture" << std::endl;
        }

        void OnShapeAdded(const ShapeAddedEvent& event) {
            m_output << "Added " << event.shapeId << " to Picture" << std::endl;
        }

        void OnShapeMoved(const ShapeMovedEvent& event) {
            m_output << "Picture changed. " << event.shapeId
                     << ": shape " << event.shapeId << " change coords. New coords: "
                     << event.newCoords << std::endl;
        }

        void OnShapeChangedStrategy(const ShapeChangedStrategyEvent &event) {
            m_output << "Picture changed. " << event.shapeId
                     << ": shape " << event.shapeId << " change strategy. New strategy: "
                     << event.newStrategyName << std::endl;
        }

        void OnShapeChangedColor(const ShapeChangedColorEvent &event) {
            m_output << "Picture changed. " << event.shapeId
                     << ": shape " << event.shapeId << " change color. New color: "
                     << event.newColor << std::endl;
        }

    private:
        std::ostream& m_output;
    };
}

#endif //OOD_L1_SHAPES_PICTUREOBSERVER_H