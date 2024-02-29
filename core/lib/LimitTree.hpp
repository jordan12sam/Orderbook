#pragma once

#include <Limit.hpp>
#include <Side.hpp>

#include <queue>
#include <vector>
#include <functional>

class LimitCompare {
private:
    bool side;
public:
    LimitCompare(bool side) : side{side} {}
    bool operator()(Limit limit1, Limit limit2);
};

class LimitTree : public std::priority_queue<Limit, std::vector<Limit>, LimitCompare> {
private:
    bool side;
public:
    LimitTree(bool side) : std::priority_queue<Limit, std::vector<Limit>, LimitCompare>(LimitCompare(side)), side{side} {}
    bool remove(const Limit& value);
    bool getSide() const;
};

