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
    bool operator()(std::shared_ptr<Limit> limit1, std::shared_ptr<Limit> limit2);
};

class LimitTree : public std::priority_queue<std::shared_ptr<Limit>, std::vector<std::shared_ptr<Limit>>, LimitCompare> {
private:
    bool side;
public:
    LimitTree(bool side) : std::priority_queue<std::shared_ptr<Limit>, std::vector<std::shared_ptr<Limit>>, LimitCompare>(LimitCompare(side)), side{side} {}
    bool remove(const std::shared_ptr<Limit>& value);
    bool getSide() const;
};

