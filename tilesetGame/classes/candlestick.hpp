#ifndef CANDLESTICK_HPP
#define CANDLESTICK_HPP

#include "mapObjects.hpp"

class Candlestick : virtual public MapObjects
{
  public:
    Candlestick();
    Candlestick(const Candlestick& copy) = delete;
    ~Candlestick() = default;

    void updateAnimation(float delta_time) override;
};

#endif