#pragma once

#include <Order.hpp>

#include <queue>
#include <vector>
#include <functional>

class Limit : public std::list<Order>{
private:
    double price;
public:
    Limit(double price);
    double getPrice() const;
};