#pragma once

#include <LimitTree.hpp>
#include <Limit.hpp>
#include <Order.hpp>
#include <Side.hpp>

#include <spdlog/spdlog.h>

#include <queue>
#include <vector>
#include <functional>

class Book {
public:
    std::shared_ptr<LimitTree> buyTree;
    std::shared_ptr<LimitTree> sellTree;
    std::unordered_map<int, Order> orderMap;
    std::unordered_map<double, int> volumeMap;
    std::unordered_map<double, Limit> limitMap;

    Book();
    void placeOrder(Order order);
    void cancelOrder(Order order);
    void getVolumeAtPrice();
};