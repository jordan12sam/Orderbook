#include <LimitTree.hpp>

bool LimitCompare::operator() (std::shared_ptr<Limit> limit1, std::shared_ptr<Limit> limit2) {
    return side ? (limit1->getPrice() < limit2->getPrice()) : (limit1->getPrice() > limit2->getPrice());
};

bool LimitTree::remove(const std::shared_ptr<Limit>& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);

    if (it == this->c.end()) {
        return false;
    }
    if (it == this->c.begin()) {
        this->pop();
    }    
    else {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
    return true;
}

bool LimitTree::getSide() const {
    return side;
};