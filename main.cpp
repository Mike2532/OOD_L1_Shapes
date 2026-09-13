#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

class IBaseStrategy
{
public:
    virtual ~IBaseStrategy() = default;
    virtual void whoami() = 0;
};

using StrategyConstructFn = std::function<std::shared_ptr<IBaseStrategy>(const std::vector<std::string>&)>;

class StrategyStorage
{
public:
    std::optional<std::shared_ptr<IBaseStrategy>> Construct(const std::string& strategyName, const std::vector<std::string>& args)
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

template <typename T>
class AutoRegistingStrategy : private StrategyStorage, public IBaseStrategy
{
    struct Register {
        Register() {
            std::cout << "called Register for " << T::GetStrategyName() << std::endl;
            StrategyStorage::Store(T::GetStrategyName(), [](const std::vector<std::string>& args) {
                return std::make_shared<T>(args);
            });
        }
    };
    inline static Register r;
};

class Square : public AutoRegistingStrategy<Square>
{
public:
    explicit Square(const std::vector<std::string>& args)
    {
        std::cout << "called Square constructor \n";
        for (const auto& arg : args) {
            std::cout << arg << std::endl;
        }
        std::cout << "end Square constructor \n\n";
    }

    static std::string GetStrategyName()
    {
        return "square";
    }

    void whoami() override {
        std::cout << "i'm square\n";
    }
};
template class AutoRegistingStrategy<Square>;

class Circle : public AutoRegistingStrategy<Circle>
{
public:
    explicit Circle(const std::vector<std::string>& args)
    {
        std::cout << "called Circle constructor \n";
        for (const auto& arg : args) {
            std::cout << arg << std::endl;
        }
        std::cout << "end Circle constructor \n\n";
    }

    static std::string GetStrategyName()
    {
        return "circle";
    }

    void whoami() override {
        std::cout << "i'm circle\n";
    }
};
template class AutoRegistingStrategy<Circle>;


int main() {
    auto storage = StrategyStorage();

    std::string inputLine;
    while (std::getline(std::cin, inputLine)) {
        std::stringstream stream(inputLine);

        std::string strategyName;
        stream >> strategyName;

        std::vector<std::string> args;
        std::string arg;
        while (stream >> arg) {
            args.emplace_back(arg);
        }

        auto s = storage.Construct(strategyName, args);
        if (!s.has_value()) {
            std::cout << "unknown type\n";
            continue;
        }
        s->get()->whoami();
    }
}