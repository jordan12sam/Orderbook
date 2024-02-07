#include <queue>
#include <vector>
#include <functional>

#include <Order.hpp>

class Limit : public std::list<Order>{
private:
public:
    double price;
    const bool operator==(const Limit& other);
    const bool operator!=(const Limit& other);
    const bool operator>(const Limit& other);
    const bool operator<(const Limit& other);
    const bool operator>=(const Limit& other);
    const bool operator<=(const Limit& other);
};