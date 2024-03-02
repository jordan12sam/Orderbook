#pragma once

#include <Order.hpp>

#include <queue>
#include <vector>
#include <functional>

class Limit : public std::list<Order>{
private:
    int price;
public:
    Limit(int price);
    int getPrice() const;
};