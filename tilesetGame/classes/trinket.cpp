#include "trinket.hpp"
#include "armory.hpp"
#include "inventory.hpp"
#include "soldier.hpp"

Trinket::Trinket(TrinketType type)
{

  this->type_ = type;
  this->sell_value_ = static_cast<int>(Values::TRINKET);
  this->equiped_ = false;
  this->buy_value_ = static_cast<int>(Values::TRINKET) * SCALING_FACTOR_FOUR;
}

void Trinket::use(Character* player) 
{

  Soldier* soldier = dynamic_cast<Soldier*>(player);
  if(soldier == nullptr) { return;}


  if(soldier->getArmor()->getFirstTrinket() == this)
  {
    Trinket* placeholder = soldier->getArmor()->getFirstTrinket();
    soldier->getArmor()->setFirstTrinket(nullptr);
    placeholder->equiped_ = false;
    handleTrinketLogic(soldier);
    soldier->getInventory()->addItem(placeholder);
    soldier->getInventory()->getArmorFromInventory()[ArmorSlot::TRINKET_ONE].setItem(nullptr);
    return;
  }
  
  if(soldier->getArmor()->getSecondTrinket() == this)
  {
    Trinket* placeholder = soldier->getArmor()->getSecondTrinket();
    soldier->getArmor()->setSecondTrinket(nullptr);
    placeholder->equiped_ = false;
    handleTrinketLogic(soldier);
    soldier->getInventory()->addItem(placeholder);
    soldier->getInventory()->getArmorFromInventory()[ArmorSlot::TRINKET_TWO].setItem(nullptr);
    return;
  }


  if(soldier->getArmor()->getFirstTrinket() == nullptr && this->equiped_ == false)
  {
    soldier->getArmor()->setFirstTrinket(this);
    this->equiped_ = true;
    handleTrinketLogic(soldier);
    soldier->getInventory()->getArmorFromInventory()[ArmorSlot::TRINKET_ONE].setItem(this);
    return;
  }
  
  if(soldier->getArmor()->getSecondTrinket() == nullptr && this->equiped_ == false)
  {
    soldier->getArmor()->setSecondTrinket(this);
    this->equiped_ = true;
    handleTrinketLogic(soldier);
    soldier->getInventory()->getArmorFromInventory()[ArmorSlot::TRINKET_TWO].setItem(this);
    return;
  }
}


void Trinket::handleTrinketLogic(Soldier* player) noexcept
{
  if(this->equiped_)
  {
    if(this->type_ == TrinketType::RUBY) { player->increaseAbilityDamage();}
    else if(this->type_ == TrinketType::SAPPHIRE) { player->increaseAbilityDamage(); player->increaseAbilityDamage();}
    else if(this->type_ == TrinketType::GOLDRUBY) { player->increaseAbilityDamage(); player->increaseAbilityDamage(); player->increaseAbilityHeal();}
  }
  else if(!this->equiped_)
  {
    if(this->type_ == TrinketType::RUBY) { player->decreaseAbilityDamage();}
    else if(this->type_ == TrinketType::SAPPHIRE) { player->decreaseAbilityDamage(); player->decreaseAbilityDamage();}
    else if(this->type_ == TrinketType::GOLDRUBY) { player->decreaseAbilityDamage(); player->decreaseAbilityDamage(); player->decreaseAbilityHeal();}
  }
}





