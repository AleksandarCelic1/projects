#include "../include_/inventory.hpp"


void Inventory::addBronze(int& bronze) noexcept
{
  this->bronze_ += bronze;

  if(this->bronze_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertBronzeToSilver();
  }
}

void Inventory::addSilver(int& silver) noexcept
{
  this->silver_ += silver;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Inventory::addGold(int& gold) noexcept
{
  this->gold_ += gold;
  checkGoldCapacity();
}


void Inventory::subtractBronze(int& bronze) noexcept
{
  this->bronze_ -= bronze;
}

void Inventory::subtractSilver(int& silver) noexcept
{
  this->silver_ -= silver;
}

void Inventory::subtractGold(int& gold) noexcept
{
  this->gold_ -= gold;
}

void Inventory::convertBronzeToSilver() noexcept
{
  this->bronze_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->silver_ += 1;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Inventory::convertSilverToGold() noexcept
{
  this->silver_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->gold_ += 1;
  checkGoldCapacity();
}

void Inventory::checkGoldCapacity() noexcept
{
  if(this->gold_ > MAXIMUM_GOLD)
  {
    this->gold_ = MAXIMUM_GOLD;
  }
}

void Inventory::convertGoldToSilver() noexcept
{
  if(this->gold_ > 0)
  {
    this->gold_ -= 1;
    this->silver_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}

void Inventory::convertSilverToBronze() noexcept
{
  if(this->silver_ > 0)
  {
    this->silver_ -= 1;
    this->bronze_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}