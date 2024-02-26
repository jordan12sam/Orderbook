#pragma once

#include <queue>
#include <vector>
#include <functional>

#include <Limit.hpp>
#include <Side.hpp>

class LimitCompare {
private:
    Side side;
public:
    LimitCompare(Side side) : side{side} {}
    bool operator()(Limit limit1, Limit limit2);
};

class LimitTree : public std::priority_queue<Limit, std::vector<Limit>, LimitCompare> {
private:
    Side side;
public:
    LimitTree(Side side) : std::priority_queue<Limit, std::vector<Limit>, LimitCompare>(LimitCompare(side)), side{side} {}
    const Side getSide();
};

