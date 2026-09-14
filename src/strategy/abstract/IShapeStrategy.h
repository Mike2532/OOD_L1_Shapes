#ifndef IBASESTRATEGY_H
#define IBASESTRATEGY_H
#include <format>
#include <regex>

namespace strategy {
    class IShapeStrategy
    {
    public:
        virtual ~IShapeStrategy() = default;
        virtual void Move(double dx, double dy) = 0;
        virtual void Draw() = 0; //todo add params)
        virtual std::string GetArgsAsString() = 0;
        virtual std::string GetStrategyName() = 0;

    protected:
        void RequireColorIsCorrect(const std::string& color)
        {
            std::regex pattern("^#[0-9a-f]{6}$");
            if (std::regex_match(color, pattern)) {
                return;
            }
            throw std::invalid_argument("invalid color. Color must be format #rrggbb");
        }

        void RequireNumberIsNonNegative(const std::string& numberName, double number)
        {
            if (number < 0.0 ) {
                throw std::invalid_argument(numberName + " must be non negative");
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
