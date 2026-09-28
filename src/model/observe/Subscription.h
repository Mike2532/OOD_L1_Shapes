#ifndef OOD_L1_SHAPES_SUBSCRIPTION_H
#define OOD_L1_SHAPES_SUBSCRIPTION_H
#include <functional>

namespace model {
    class Subscription
    {
    public:
        explicit Subscription(const std::function<void()>& onDestroy, int subscriptionId)
            : m_onDestroy(onDestroy), m_subscriptionId(subscriptionId)
        {
        }

        ~Subscription()
        {
            if (m_onDestroy) {
                m_onDestroy();
            }
        }

        Subscription(const Subscription&) = delete;
        Subscription& operator=(const Subscription&) = delete;

        Subscription(Subscription&& other) noexcept
            :m_onDestroy(other.m_onDestroy), m_subscriptionId(other.m_subscriptionId)
        {
            other.m_onDestroy = nullptr;
        }

        Subscription& operator=(Subscription&& other) noexcept
        {
            std::swap(m_onDestroy, other.m_onDestroy);
            std::swap(m_subscriptionId, other.m_subscriptionId);
            return *this;
        }

        void Unsubscribe()
        {
            if (m_onDestroy) {
                m_onDestroy();
            }
        }

        int GetSubscriptionId() const
        {
            return m_subscriptionId;
        }
    private:
        std::function<void()> m_onDestroy;
        int m_subscriptionId;
    };
}

#endif //OOD_L1_SHAPES_SUBSCRIPTION_H