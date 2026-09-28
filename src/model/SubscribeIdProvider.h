#ifndef OOD_L1_SHAPES_SUBSCRIBEIDPROVIDER_H
#define OOD_L1_SHAPES_SUBSCRIBEIDPROVIDER_H

class SubscribeIdProvider
{
public:
    SubscribeIdProvider() = delete;
    ~SubscribeIdProvider() = delete;

    static int GetNextSubscribeId()
    {
        return m_subscribeId++;
    }
private:
    inline static int m_subscribeId = 0;
};

#endif //OOD_L1_SHAPES_SUBSCRIBEIDPROVIDER_H