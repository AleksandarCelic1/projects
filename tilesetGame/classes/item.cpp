#include "item.hpp"

Item::~Item()
{
  // texture;
}


void Item::sell(Character* player) 
{
  player->setMoney(player->getMoney() + this->sell_value_);
}

bool Item::buy(Character* player) 
{
  if(player->getMoney() >= this->buy_value_)
  {
    player->setMoney(player->getMoney() - this->buy_value_);
  }
  else 
  {
    return false;
  }

  return true;
}