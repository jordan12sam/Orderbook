#pragma once

#include <Side.hpp>

#include <iostream>
#include <ctime>

class Order {
public:
    Order();
    Order(unsigned long int id, bool side, unsigned long int price, unsigned long int volume, std::string client);
    bool operator==(const Order& rhs) const = default;

    unsigned long int id;
    std::time_t timestamp;
    bool side;
    unsigned long int price;
    unsigned long int volume;
    std::string client;
};