#include "ring.hpp"
#include "armory.hpp"
#include "inventory.hpp"

Ring::Ring()
{
  this->sell_value_ = static_cast<int>(Values::RING);
  this->equiped_ = false;
}

void Ring::use(Character* player)
{
  if(player->getArmor()->getFirstRing() == this)
  {
    Ring* placeholder = player->getArmor()->getFirstRing();
    player->getArmor()->setFirstRing(nullptr);
    placeholder->equiped_ = false;
    player->getInventory()->addItem(placeholder);
    player->setBaseHealth(player->getBaseHealth() - placeholder->health_points_increase_);
    player->getInventory()->getArmorFromInventory()[ArmorSlot::RING_ONE].setItem(nullptr);
    return;
  }
  
  if(player->getArmor()->getSecondRing() == this)
  {
    Ring* placeholder = player->getArmor()->getSecondRing();
    player->getArmor()->setSecondRing(nullptr);
    placeholder->equiped_ = false;
    player->getInventory()->addItem(placeholder);
    player->setBaseHealth(player->getBaseHealth() - placeholder->health_points_increase_);
    player->getInventory()->getArmorFromInventory()[ArmorSlot::RING_TWO].setItem(nullptr);
    return;
  }


  if(player->getArmor()->getFirstRing() == nullptr && this->equiped_ == false)
  {
    player->getArmor()->setFirstRing(this);
    player->setBaseHealth(player->getBaseHealth() + this->health_points_increase_);
    this->equiped_ = true;
    player->getInventory()->getArmorFromInventory()[ArmorSlot::RING_ONE].setItem(this);
    return;
  }
  
  if(player->getArmor()->getSecondRing() == nullptr && this->equiped_ == false)
  {
    player->getArmor()->setSecondRing(this);
    player->setBaseHealth(player->getBaseHealth() + this->health_points_increase_);
    this->equiped_ = true;
    player->getInventory()->getArmorFromInventory()[ArmorSlot::RING_TWO].setItem(this);
    return;
  }
}