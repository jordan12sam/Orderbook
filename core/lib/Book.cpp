#include <Book.hpp>

Book::Book() {
    buyTree = std::make_shared<LimitTree>(Side::buy);
    sellTree = std::make_shared<LimitTree>(Side::sell);
};

void Book::placeOrder(Order order) {
    std::shared_ptr<LimitTree> otherBook = order.side ? sellTree : buyTree;
    std::shared_ptr<LimitTree> book  = order.side ? buyTree : sellTree;
    orderMap.insert({order.id, order});

    while((order.volume > 0) && (!otherBook->empty()) && (otherBook->top().getPrice() <= order.price)) {
        Order otherOrder = otherBook->top().front();
        double tradePrice = otherOrder.price;
        int tradeVolume = std::min(order.volume, otherOrder.volume);
        otherOrder.volume -= tradeVolume;
        order.volume -= tradeVolume;
        spdlog::info(std::format("Made by {}, [{}]. Taken by {}, [{}]. {} shares @ {}.", otherOrder.client, otherOrder.id, order.client, order.id, tradeVolume, order.price));

        if(otherOrder.volume == 0) {
            cancelOrder(otherOrder);
        }
    }
};

void Book::cancelOrder(Order order) {

};