#ifndef AUTOREGISTERSTRATEGY_H
#define AUTOREGISTERSTRATEGY_H

#include <vector>
#include "StrategyStorage.h"
#include "IShapeStrategy.h"

namespace strategy {
    template <typename StrategyNamed>
    concept HasStrategyName = requires {
        {StrategyNamed::GetStrategyName()} -> std::same_as<std::string>;
    };

    template <typename T, typename StrategyNamed>
    class AutoRegisterStrategy : private StrategyStorage, public IShapeStrategy
    {
        struct Register {
            Register() {
                StrategyStorage::Store(StrategyNamed::GetStrategyName(), [](const std::vector<std::string>& args) {
                    return std::make_unique<T>(args);
                });
            }
        };
        inline static Register r;
    };

}
#endif // AUTOREGISTERSTRATEGY_H
