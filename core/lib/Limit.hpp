#pragma once

#include <queue>
#include <vector>
#include <functional>

#include <Order.hpp>

class Limit : public std::list<Order>{
private:
    double price;
public:
    Limit(double price);
    double getPrice() const;
};