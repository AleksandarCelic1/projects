#include "potion.hpp"

Potion::Potion()
{
  this->sell_value_ = static_cast<int>(Values::POTION);
  this->buy_value_ = static_cast<int>(Values::POTION) * SCALING_FACTOR_FOUR;
}

void Potion::use(Character* player)
{
  if(player->getCurrentHealth() == player->getBaseHealth())
  {
    // item will be used but not consumed!
  }
  else
  {
    player->setCurrentHealth(player->getCurrentHealth() + 1);
  }
}

