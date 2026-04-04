#include "../include_/character.hpp"

void Character::addBronze(int& bronze)
{
  this->bronze_ += bronze;

  if(this->bronze_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertBronzeToSilver();
  }
}

void Character::addSilver(int& silver)
{
  this->silver_ += silver;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Character::addGold(int& gold)
{
  this->gold_ += gold;
  checkGoldCapacity();
}


void Character::subtractBronze(int& bronze)
{
  this->bronze_ -= bronze;
}

void Character::subtractSilver(int& silver)
{
  this->silver_ -= silver;
}

void Character::subtractGold(int& gold)
{
  this->gold_ -= gold;
}

void Character::convertBronzeToSilver()
{
  this->bronze_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->silver_ += 1;
  if(this->silver_ > MAXIMUM_BRONZE_AND_SILVER)
  {
    convertSilverToGold();
  }
}

void Character::convertSilverToGold()
{
  this->silver_ -= MAXIMUM_BRONZE_AND_SILVER;
  this->gold_ += 1;
  checkGoldCapacity();
}

void Character::checkGoldCapacity()
{
  if(this->gold_ > MAXIMUM_GOLD)
  {
    this->gold_ = MAXIMUM_GOLD;
  }
}

void Character::convertGoldToSilver()
{
  if(this->gold_ > 0)
  {
    this->gold_ -= 1;
    this->silver_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}

void Character::convertSilverToBronze()
{
  if(this->silver_ > 0)
  {
    this->silver_ -= 1;
    this->bronze_ += MAXIMUM_BRONZE_AND_SILVER;
  }
}