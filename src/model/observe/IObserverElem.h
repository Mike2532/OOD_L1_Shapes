#ifndef OOD_L1_SHAPES_IOBSERVERSTORAGEELEM_H
#define OOD_L1_SHAPES_IOBSERVERSTORAGEELEM_H

template <typename T>
class IObserverElem
{
public:
    virtual ~IObserverElem() = default;
    virtual void OnChange(const T& event) = 0;
};

#endif //OOD_L1_SHAPES_IOBSERVERSTORAGEELEM_H