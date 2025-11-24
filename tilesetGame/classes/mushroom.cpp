#include "mushroom.hpp"

Mushroom::Mushroom()
{
  this->sell_value_ = static_cast<int>(Values::MUSHROOM);
  this->buy_value_ = static_cast<int>(Values::MUSHROOM) * SCALING_FACTOR_FOUR;

}

void Mushroom::use(Character* player) 
{
  player->setCurrentHealth(player->getCurrentHealth() - 1);
  // logika da umres treba ici ovde!
  // poisonous!
}