#include <LimitTree.hpp>
LimitTree::LimitTree(Side Side) {
    this->side = side;
}

const bool LimitTree::operator() (Limit order1, Limit order2) {
    return side ? (order1 > order2) : (order1 < order2);
};

const Side LimitTree::getSide() {
    return side;
};
