#include "rubyring.hpp"

RubyRing::RubyRing()
{
  this->health_points_increase_ = 1;
  this->buy_value_ = static_cast<int>(Values::RING) * SCALING_FACTOR_TWO;
}