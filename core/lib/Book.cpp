#include <Book.hpp>

Book::Book() {
    buyTree = std::make_shared<LimitTree>(Side::buy);
    sellTree = std::make_shared<LimitTree>(Side::sell);
};

void Book::placeOrder(std::shared_ptr<Order> order) {
    spdlog::trace("Placing order [id: {}, buy={}]", order->id, order->side);
    std::shared_ptr<LimitTree> otherTree = getOtherTree(order->side);
    std::shared_ptr<LimitTree> thisTree  = getTree(order->side);

    while((order->volume > 0) && (!otherTree->empty()) && (otherTree->top()->getPrice() <= order->price)) {
        std::shared_ptr<Order> otherOrder = otherTree->top()->front();
        spdlog::trace("Matching orders [id={}, {}].", order->id, otherOrder->id);
        int tradePrice = otherOrder->price;
        int tradeVolume = std::min(order->volume, otherOrder->volume);
        otherOrder->volume -= tradeVolume;
        order->volume -= tradeVolume;

        spdlog::info("Made by {}, [id={}]. Taken by {}, [id={}]. {} shares @ {}.", 
        otherOrder->client,
        otherOrder->id,
        order->client,
        order->id,
        tradeVolume,
        order->price);

        if(otherOrder->volume == 0) {
            cancelOrder(otherOrder->id);
        }
    }

    if (order->volume > 0) {
        spdlog::trace("Order [id={}] has vol, adding to tree [side={}].", order->id, order->side);
        addOrderToTree(order);
    }
    spdlog::trace("Order placed [id: {}, buy={}]", order->id, order->side);
};

void Book::cancelOrder(int id) {
    if (orderMap.contains(id)) {
        std::shared_ptr<Order> order = orderMap.at(id);
        std::shared_ptr<Limit> limit = limitMap.at(order->side).at(order->price);
        limit->remove(order);
        if (limit->size() == 0) {
            std::shared_ptr<LimitTree> thisTree = getTree(order->side);
            thisTree->remove(limit);
            limitMap.at(order->side).erase(limit->getPrice());
        }
        volumeMap.at(order->side).at(order->price) -= order->volume;
        orderMap.erase(id);
        spdlog::info(std::format("Order [{}] cancelled by {}.", id, order->client));
    }
};

int Book::getVolumeAtPrice(int price, bool side) {
    return volumeMap.at(side).contains(price) ? volumeMap.at(side).at(price) : 0;
}

void Book::addOrderToTree(std::shared_ptr<Order> order) {
    orderMap.insert({order->id, order});
    spdlog::trace("Inserted id: {} into order map.", order->id);
    if (!limitMap.at(order->side).contains(order->price)) {
        std::shared_ptr<Limit> limit = std::make_shared<Limit>(order->price);
        limitMap.at(order->side).insert({order->price, limit});
        spdlog::trace("Inserted limit [price={}] into limit map.", order->price);
        volumeMap.at(order->side).insert({order->price, order->volume});
        getTree(order->side)->push(limit);
    }
    else {
        volumeMap.at(order->side).at(order->price) += order->volume;
    }
    limitMap.at(order->side).at(order->price)->push_back(order);
    spdlog::trace("Order [id: {}] added to tree [buy={}].", order->id, order->side);
};

std::shared_ptr<LimitTree> Book::getTree(bool side) const {
    return side ? buyTree : sellTree;
};

std::shared_ptr<LimitTree> Book::getOtherTree(bool side) const {
    return getTree(!side);
};