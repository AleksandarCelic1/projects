#include "goldsapphirering.hpp"

GoldSapphireRing::GoldSapphireRing()
{
  this->health_points_increase_ = 3;
  this->buy_value_ = static_cast<int>(Values::RING) * SCALING_FACTOR_FOUR;
  this->sell_value_ = static_cast<int>(Values::RING);
}