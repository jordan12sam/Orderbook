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
    std::unordered_map<int, std::shared_ptr<Order>> orderMap;
    std::unordered_map<bool, std::unordered_map<int, int>> volumeMap = {{true, {}}, {false, {}}};
    std::unordered_map<bool, std::unordered_map<int, std::shared_ptr<Limit>>> limitMap = {{true, {}}, {false, {}}};

    Book();
    void placeOrder(std::shared_ptr<Order> order);
    void cancelOrder(int id);
    int getVolumeAtPrice(int price, bool side);
    void addOrderToTree(std::shared_ptr<Order> order);
    std::shared_ptr<LimitTree> getTree(bool side) const;
    std::shared_ptr<LimitTree> getOtherTree(bool side) const;
};