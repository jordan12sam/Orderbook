#include <Book.hpp>

Book::Book() {
    buyTree = std::make_shared<LimitTree>(Side::buy);
    sellTree = std::make_shared<LimitTree>(Side::sell);
};

void Book::placeOrder(Order order) {
    std::shared_ptr<LimitTree> otherBook = getOtherTree(order.side);
    std::shared_ptr<LimitTree> book  = getTree(order.side);
    spdlog::trace("Inserted id: {} into order map.", order.id);
    orderMap.insert({order.id, order});

    while((order.volume > 0) && (!otherBook->empty()) && (otherBook->top().getPrice() <= order.price)) {
        Order otherOrder = otherBook->top().front();
        double tradePrice = otherOrder.price;
        int tradeVolume = std::min(order.volume, otherOrder.volume);
        otherOrder.volume -= tradeVolume;
        order.volume -= tradeVolume;
        spdlog::info("Made by {}, [{}]. Taken by {}, [{}]. {} shares @ {}.", 
        otherOrder.client, otherOrder.id, order.client, order.id, tradeVolume, order.price);

        if(otherOrder.volume == 0) {
            cancelOrder(otherOrder.id);
        }
    }

    if (order.volume > 0) {
        addOrderToTree(order);
    }
    spdlog::trace("Order placed [id: {} buy={}]", order.id, order.side);
};

void Book::cancelOrder(int id) {
    spdlog::trace("Order cancellation called for id: {}.", id);
    if (orderMap.contains(id)) {
        Order order = orderMap.at(id);
        Limit limit = limitMap.at(order.side).at(Price(order.price));
        limit.remove(order);
        if (limit.size() == 0) {
            std::shared_ptr<LimitTree> book = getTree(order.side);
            book->remove(limit);
        }
        volumeMap.at(order.side).at(Price(order.price)) -= order.volume;
        orderMap.erase(id);
        spdlog::info(std::format("Order [{}] cancelled by {}.", order.client, id));
    }
};

int Book::getVolumeAtPrice(double price, bool side) {
    return volumeMap.at(side).contains(Price(price)) ? volumeMap.at(side).at(Price(price)) : 0;
}

void Book::addOrderToTree(Order order) {
    std::shared_ptr<LimitTree> book = getTree(order.side);
    if (!limitMap.at(order.side).contains(Price(order.price))) {
        limitMap.at(order.side).insert({Price(order.price), Limit(order.price)});
        volumeMap.at(order.side).insert({Price(order.price), order.volume});
    }
    else {
        volumeMap.at(order.side).at(Price(order.price)) += order.volume;
    }
    limitMap.at(order.side).at(Price(order.price)).push_front(order);
    spdlog::trace("Order [id: {}] added to tree [buy={}].", order.id, order.side);
};

std::shared_ptr<LimitTree> Book::getTree(bool side) const {
    return side ? buyTree : sellTree;
};

std::shared_ptr<LimitTree> Book::getOtherTree(bool side) const {
    return getTree(!side);
};