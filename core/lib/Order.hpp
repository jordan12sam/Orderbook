#pragma once

#include <Side.hpp>

#include <iostream>
#include <ctime>

class Order {
public:
    bool operator==(const Order& rhs) const = default;

    int id;
    std::time_t timestamp;
    bool side;
    int price;
    int volume;
    std::string client;
};