#pragma once

#include <iostream>
#include <ctime>

#include <Side.hpp>

class Order {
private:
public:
    Order();
    int orderId;
    std::time_t timestamp;
    Side side;
    double price;
    int volume;
    std::string client;
};