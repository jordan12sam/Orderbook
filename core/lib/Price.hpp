#pragma once

#include <functional>

class Price{
private:
    int iprice;
public:
    Price(double dprice);
    const int getInt() const;
    const bool operator==(const Price& other) const;
};

template <>
struct std::hash<Price>
{
  std::size_t operator()(const Price& price) const {
    return ((std::hash<int>()(price.getInt())));
  }
};