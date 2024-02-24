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
private:
    Book();
    LimitTree *buyTree;
    LimitTree *sellTree;
    std::unordered_map<int, Order> orderMap;
    std::unordered_map<double, int> volumeMap;
    std::unordered_map<double, Limit> limitMap;
public:
    void placeOrder(Order order);
    void cancelOrder(Order order);
    void getVolumeAtPrice();
};