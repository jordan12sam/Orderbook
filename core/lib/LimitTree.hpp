#pragma once

#include <queue>
#include <vector>
#include <functional>

#include <Limit.hpp>
#include <Side.hpp>

class LimitTree {
private:
    Side side;
    class LimitCompare{
    private:
        Side side;
    public:
        LimitCompare(Side side) : side{side} {};
        const bool operator() (Limit limit1, Limit limit2);
    };
public:
    LimitTree(Side side);
    std::priority_queue<Limit, std::vector<Limit>, LimitCompare> heap{LimitCompare{side}};
    const Side getSide();
};

