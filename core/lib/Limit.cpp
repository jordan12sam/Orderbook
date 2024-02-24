#include <Limit.hpp>

const bool Limit::operator==(const Limit& other) {
    return price == other.price;
};

const bool Limit::operator>(const Limit& other) {
    return price > other.price;
};

const bool Limit::operator!=(const Limit& other) {
    return !operator==(other);
};

const bool Limit::operator<(const Limit& other) {
    return !operator>(other);
};

const bool Limit::operator>=(const Limit& other) {
    return (operator>(other) && operator==(other));
};

const bool Limit::operator<=(const Limit& other) {
    return (operator<(other) && operator==(other));
};