#ifndef OOD_L1_SHAPES_OBSERVERSTORAGE_H
#define OOD_L1_SHAPES_OBSERVERSTORAGE_H
#include <vector>


namespace model {
    template <typename T>
    struct Observer {
        T* observer;
        bool isRemoved;
    };

    template <typename T>
    class ObserverStorage
    {
    public:
        std::vector<std::shared_ptr<Observer<T>>> GetObservers() {
            m_isLocked = true;
            return m_observers;
        }

        void Unlock() {
            m_isLocked = false;
            FlushChanges();
        }

        void AddObserver(T* observer) {
            for (auto observerToAdd : m_observersToAdd) {
                if (observerToAdd == observer) {
                    return;
                }
            }
            for (auto storedObservers : m_observers) {
                if (storedObservers->observer == observer) {
                    storedObservers->isRemoved = false;
                    return;
                }
            }

            if (m_isLocked) {
                m_observersToAdd.push_back(observer);
                return;
            }
            m_observers.push_back(std::make_shared<Observer<T>>(observer, false));
        }

        void RemoveObserver(T* observer) {
            if (observer == nullptr) {
                return;
            }

            auto it = std::find(m_observersToAdd.begin(), m_observersToAdd.end(), observer);
            if (it != m_observersToAdd.end()) {
                m_observersToAdd.erase(it);
                return;
            }

            for (auto& storedObserver : m_observers) {
                if (storedObserver->observer == observer && !storedObserver->isRemoved) {
                    storedObserver->isRemoved = true;
                    return;
                }
            }
        }
    private:
        bool m_isLocked = false;
        std::vector<std::shared_ptr<Observer<T>>> m_observers;
        std::vector<T*> m_observersToAdd;

        void FlushChanges() {
            FilterDeletedObservers();
            AddNewObservers();
        }

        void FilterDeletedObservers() {
            std::erase_if(m_observers, [](const std::shared_ptr<Observer<T>>& obs) {
                return obs->isRemoved;
            });
        }

        void AddNewObservers() {
            for (auto observer : m_observersToAdd) {
                m_observers.emplace_back(std::make_shared<Observer<T>>(observer, false));
            }
            m_observersToAdd.clear();
        }
    };
}

#endif //OOD_L1_SHAPES_OBSERVERSTORAGE_H