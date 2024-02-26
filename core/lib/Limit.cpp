#include <Limit.hpp>

Limit::Limit(double price) {
    this->price = price;
}

double Limit::getPrice() const {
    return price;
}