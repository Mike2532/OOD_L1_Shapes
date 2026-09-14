#ifndef IBASESTRATEGY_H
#define IBASESTRATEGY_H
#include <format>
#include <regex>

#include "../../gfx/abstract/ICanvas.h"

namespace strategy {
    class IShapeStrategy
    {
    public:
        virtual ~IShapeStrategy() = default;
        virtual void Move(double dx, double dy) = 0;
        virtual void Draw(std::unique_ptr<gfx::ICanvas>& canvas, const std::string& color) = 0;
        virtual std::string GetArgsAsString() = 0;
        virtual std::string GetStrategyName() = 0;

    protected:
        void RequireNumberIsNonNegative(const std::string& numberName, double number)
        {
            if (number <= 0.0 ) {
                throw std::invalid_argument(numberName + " must be positive");
            }
        }

        void RequireArgumentsSize(int targetSize, const std::vector<std::string>& args)
        {
            if (args.size() != targetSize) {
                throw std::runtime_error("wrong number of arguments. Found: " + std::to_string(args.size()) + " Expected: " + std::to_string(targetSize));
            }
        }

        std::string ConvertNumberToString(double number) const
        {
            return std::format("{:.2f}", number);;
        }
    };
}

#endif // IBASESTRATEGY_H
