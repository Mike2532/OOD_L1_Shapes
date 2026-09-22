#ifndef OOD_L1_SHAPES_PICTUREOBSERVER_H
#define OOD_L1_SHAPES_PICTUREOBSERVER_H

#include <iosfwd>
#include <iostream>

#include "IPictureObserver.h"
#include "PictureEvent.h"

class PictureObserver : public IPictureObserver
{
public:
    explicit PictureObserver(std::ostream& output = std::cout)
            : m_output(output)
    {
    }

    void OnChange(const PictureEvent& event) override
    {
        m_output << "Picture changed. " << event.msg << std::endl;
    }
private:
    std::ostream& m_output;
};

#endif //OOD_L1_SHAPES_PICTUREOBSERVER_H