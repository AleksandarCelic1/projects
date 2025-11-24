#include "sapphirering.hpp"

SapphireRing::SapphireRing()
{
  this->health_points_increase_ = 2;
  this->buy_value_ = static_cast<int>(Values::RING) * SCALING_FACTOR_THREE;
}