#ifndef OOD_L1_SHAPES_ISTRATEGYSTORAGE_H
#define OOD_L1_SHAPES_ISTRATEGYSTORAGE_H
#include <optional>

#include "IShapeStrategy.h"

namespace strategy {
    class IStrategyStorage
    {
    public:
        virtual ~IStrategyStorage() = default;
        virtual std::optional<std::unique_ptr<IShapeStrategy>> Construct(const std::string& strategyName, const std::vector<std::string>& args) = 0;
    };
}


#endif //OOD_L1_SHAPES_ISTRATEGYSTORAGE_H