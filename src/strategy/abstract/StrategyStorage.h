#ifndef OOD_L1_SHAPES_STRATEGYSTORAGE_H
#define OOD_L1_SHAPES_STRATEGYSTORAGE_H

#include <memory>
#include <optional>
#include <vector>

#include "StrategyConstructFn.h"

namespace strategy {
    class StrategyStorage
    {
    public:
        std::optional<std::shared_ptr<IShapeStrategy>> Construct(const std::string& strategyName, const std::vector<std::string>& args)
        {
            if (storage.contains(strategyName)) {
                return storage[strategyName](args);
            }
            return std::nullopt;
        }

    protected:
        static void Store(const std::string& strategyName, StrategyConstructFn strategyConstructFn)
        {
            storage[strategyName] = std::move(strategyConstructFn);
        }

    private:
        inline static std::unordered_map<std::string, StrategyConstructFn> storage;
    };
}

#endif //OOD_L1_SHAPES_STRATEGYSTORAGE_H
