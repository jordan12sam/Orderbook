#include <Book.hpp>

Book::Book() {
    buyTree = new LimitTree(Side::buy);
    sellTree = new LimitTree(Side::sell);
};

void Book::placeOrder(Order order) {
    LimitTree *oppositeBook = order.side ? sellTree : buyTree;
    orderMap.insert({order.orderId, order});

    while((order.volume > 0) && (!oppositeBook->empty()) && (oppositeBook->top().price <= order.price)) {
        Order otherOrder = *oppositeBook->top().front();
        double tradePrice = otherOrder.price;
        int tradeVolume = std::min(order.volume, otherOrder.volume);
        otherOrder.volume -= tradeVolume;
        order.volume -= tradeVolume;
        spdlog::info("Made by {}, OrderID={}. Taken by {}, OrderID={}. {} shares @ {}.");

        if(otherOrder.volume == 0) {
            cancelOrder(otherOrder);
        }
    }
};