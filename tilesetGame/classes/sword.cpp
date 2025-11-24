#include "sword.hpp"
#include "armory.hpp"
#include "inventory.hpp"

Sword::Sword()
{
  this->sell_value_ = static_cast<int>(Values::SWORD);
  this->equiped_ = false; 
}


void Sword::use(Character* player) 
{
  if(player->getArmor()->getSword() == nullptr && this->equiped_ == false)
  {
    player->getArmor()->setMainSword(this);
    this->equiped_ = true;
    player->setBaseDamage(player->getBaseDamage() + this->attack_power_boost_);
    player->getInventory()->getArmorFromInventory()[ArmorSlot::SWORD].setItem(this);
  }
  else if(player->getArmor()->getSword() == this)
  {
    Sword* placeholder = player->getArmor()->getSword();
    player->getArmor()->setMainSword(nullptr);
    placeholder->setEquiped(false);
    player->getInventory()->addItem(placeholder);
    player->setBaseDamage(player->getBaseDamage() - placeholder->attack_power_boost_);
    player->getInventory()->getArmorFromInventory()[ArmorSlot::SWORD].setItem(nullptr);
  }
}