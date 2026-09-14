#ifndef OOD_L1_SHAPES_POINT_H
#define OOD_L1_SHAPES_POINT_H

namespace strategy {
    class Point
    {
    public:
        Point() = default;

        Point(const double x, const double y)
            : m_xCoord(x), m_yCoord(y)
        {
        }

        void Move(const double dx, const double dy)
        {
            m_xCoord -= dx;
            m_yCoord -= dy;
        }

        std::pair<double, double> GetCoords() const
        {
            return std::make_pair(m_xCoord, m_yCoord);
        }
    private:
        double m_xCoord = 0;
        double m_yCoord = 0;
    };
}

#endif //OOD_L1_SHAPES_POINT_H