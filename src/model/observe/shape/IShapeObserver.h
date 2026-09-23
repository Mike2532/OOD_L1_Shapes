#ifndef OOD_L1_SHAPES_ISHAPEOBSERVER_H
#define OOD_L1_SHAPES_ISHAPEOBSERVER_H
#include "ShapeEvent.h"

namespace model {
    class IShapeObserver
    {
    public:
        virtual ~IShapeObserver() = default;
        virtual void OnShapeChange(const ShapeEvent& shapeEvent) = 0;
    };
}

#endif //OOD_L1_SHAPES_ISHAPEOBSERVER_H