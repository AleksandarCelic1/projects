#include "coin.hpp"

Coin::Coin() 
{
  this->sell_value_ = static_cast<int>(Values::NO_VALUE);
}

void Coin::use(Character* player)
{
  // cant use Coin!
}