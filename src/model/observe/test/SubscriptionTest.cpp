#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "../Subscription.h"

TEST_CASE("normal desctructor")
{
    auto callback = [] () {
        std::cout << "callback()" << std::endl;
    };
    auto subscription = model::Subscription(callback, 0);
}

TEST_CASE("callback with exception")
{
    auto callback = [] () {
        throw std::exception();
    };
    auto subscription = model::Subscription(callback, 0);
}