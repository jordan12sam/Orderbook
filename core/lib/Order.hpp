#pragma once

#include <iostream>
#include <ctime>

#include <Side.hpp>

class Order {
public:
    Order();
    bool operator==(const Order& rhs) const = default;

    int id;
    std::time_t timestamp;
    Side side;
    double price;
    int volume;
    std::string client;
};