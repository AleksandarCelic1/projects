#include "../include_/character.hpp"

void Character::addBronze(int& bronze) noexcept
{
  this->bronze_ += bronze;

  if(this->bronze_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertBronzeToSilver();
  }
}

void Character::addSilver(int& silver) noexcept
{
  this->silver_ += silver;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Character::addGold(int& gold) noexcept
{
  this->gold_ += gold;
  checkGoldCapacity();
}


void Character::subtractBronze(int& bronze) noexcept
{
  this->bronze_ -= bronze;
}

void Character::subtractSilver(int& silver) noexcept
{
  this->silver_ -= silver;
}

void Character::subtractGold(int& gold) noexcept
{
  this->gold_ -= gold;
}

void Character::convertBronzeToSilver() noexcept
{
  this->bronze_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->silver_ += 1;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Character::convertSilverToGold() noexcept
{
  this->silver_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->gold_ += 1;
  checkGoldCapacity();
}

void Character::checkGoldCapacity() noexcept
{
  if(this->gold_ > MAXIMUM_GOLD)
  {
    this->gold_ = MAXIMUM_GOLD;
  }
}

void Character::convertGoldToSilver() noexcept
{
  if(this->gold_ > 0)
  {
    this->gold_ -= 1;
    this->silver_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}

void Character::convertSilverToBronze() noexcept
{
  if(this->silver_ > 0)
  {
    this->silver_ -= 1;
    this->bronze_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}