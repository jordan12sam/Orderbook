#include <Price.hpp>

Price::Price(double dprice) {
    iprice = int(dprice*1e6);
}

const int Price::getInt() const {
    return iprice;
}

const bool Price::operator==(const Price& other) const {
    return iprice == other.iprice;
}