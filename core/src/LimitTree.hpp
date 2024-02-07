#include <queue>
#include <vector>
#include <functional>

#include <Limit.hpp>
#include <Side.hpp>

class LimitTree : public std::priority_queue<Limit, LimitTree>{
private:
    Side side;
public:
    LimitTree(Side side);
    const bool operator() (Limit limit1, Limit limit2);
    const Side getSide();
};
