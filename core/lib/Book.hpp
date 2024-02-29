#pragma once

#include <LimitTree.hpp>
#include <Limit.hpp>
#include <Order.hpp>
#include <Side.hpp>
#include <Price.hpp>

#include <spdlog/spdlog.h>

#include <queue>
#include <vector>
#include <functional>

class Book {
public:
    std::shared_ptr<LimitTree> buyTree;
    std::shared_ptr<LimitTree> sellTree;
    std::unordered_map<int, Order> orderMap;
    std::unordered_map<bool, std::unordered_map<Price, int>> volumeMap = {{true, {}}, {false, {}}};
    std::unordered_map<bool, std::unordered_map<Price, std::shared_ptr<Limit>>> limitMap = {{true, {}}, {false, {}}};

    Book();
    void placeOrder(Order order);
    void cancelOrder(int id);
    int getVolumeAtPrice(double price, bool side);
    void addOrderToTree(Order order);
    std::shared_ptr<LimitTree> getTree(bool side) const;
    std::shared_ptr<LimitTree> getOtherTree(bool side) const;
};