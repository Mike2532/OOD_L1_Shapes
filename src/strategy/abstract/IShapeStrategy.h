#ifndef IBASESTRATEGY_H
#define IBASESTRATEGY_H

namespace strategy {
    class IShapeStrategy
    {
    public:
        virtual ~IShapeStrategy() = default;
        virtual void Move(double dx, double dy) = 0;
        virtual void Draw() = 0; //todo add params)
    };
}

#endif // IBASESTRATEGY_H
