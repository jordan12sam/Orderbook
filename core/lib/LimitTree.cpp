#include <LimitTree.hpp>

bool LimitCompare::operator() (Limit limit1, Limit limit2) {
    return side ? (limit1.getPrice() < limit2.getPrice()) : (limit1.getPrice() > limit2.getPrice());
};

const Side LimitTree::getSide() {
    return side;
};
