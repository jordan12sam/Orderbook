#include <iostream>
#include <ctime>

class Order {
public:
private:
    int orderId;
    std::time_t timestamp;
    bool side;
    double price;
    int volume;
    std::string client;
};