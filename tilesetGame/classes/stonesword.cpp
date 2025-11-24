#include "stonesword.hpp"
#include "armory.hpp"
#include "inventory.hpp"

StoneSword::StoneSword()
{
  this->sell_value_ = static_cast<int>(Values::SWORD);
  this->attack_power_boost_ = 1;
  this->equiped_ = false;
  this->buy_value_ = static_cast<int>(Values::SWORD) * SCALING_FACTOR_TWO;
}

