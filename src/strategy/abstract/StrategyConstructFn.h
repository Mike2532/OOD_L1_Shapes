#ifndef STRATEGYCONSTRUCTFN_H
#define STRATEGYCONSTRUCTFN_H

#include <functional>
#include <memory>

#include "IShapeStrategy.h"

namespace strategy {
    using StrategyConstructFn = std::function<std::unique_ptr<IShapeStrategy>(const std::vector<std::string>&)>;
}

#endif // STRATEGYCONSTRUCTFN_H
