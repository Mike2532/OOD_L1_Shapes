#ifndef OOD_L1_SHAPES_IPICTUREOBSERVER_H
#define OOD_L1_SHAPES_IPICTUREOBSERVER_H

#include "PictureEvent.h"

namespace model {
    class IPictureObserver
    {
    public:
        virtual ~IPictureObserver() = default;
        virtual void OnChange(const PictureEvent& event) = 0;
    };
}

#endif //OOD_L1_SHAPES_IPICTUREOBSERVER_H