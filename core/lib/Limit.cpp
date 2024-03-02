#include <Limit.hpp>

Limit::Limit(int price) {
    this->price = price;
}

int Limit::getPrice() const {
    return price;
}