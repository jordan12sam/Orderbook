#include <Order.hpp>

Order::Order() {
    this->timestamp = std::time(nullptr);
}

Order::Order(unsigned long int id, bool side, unsigned long int price, unsigned long int volume, std::string client) {
    this->id = id;
    this->timestamp = std::time(nullptr);
    this->side = side;
    this->price = price;
    this->volume = volume;
    this->client = client;
}