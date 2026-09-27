#ifndef OOD_L1_SHAPES_STRATEGYSTORAGE_H
#define OOD_L1_SHAPES_STRATEGYSTORAGE_H

#include <memory>
#include <ostream>
#include <vector>

#include "IStrategyStorage.h"
#include "StrategyConstructFn.h"

namespace strategy {
    class StrategyStorage : public IStrategyStorage
    {
    public:
        std::unique_ptr<IShapeStrategy> Construct(const std::string& strategyName, const std::vector<std::string>& args)
        {
            if (storage.contains(strategyName)) {
                return storage[strategyName](args);
            }
            return nullptr;
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
