#include "attributes.hpp"
#include "stats.hpp"


void Attributes::addStrength(int& strength, Stats* placeholder)
{
  this->strenght_ += strength;

  adjustBaseHealth(placeholder);
  adjustPhysicalPower(placeholder);
  adjustCurrentHealth(placeholder);
}

void Attributes::addDexterity(int& dexterity, Stats* placeholder)
{
  this->dexterity_ += dexterity;

  adjustPhysicalPower(placeholder);
  adjustAttackSpeed(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::addIntellect(int& intellect, Stats* placeholder)
{
  this->intellect_ += intellect;

  adjustSpellPower(placeholder);
  adjustBaseMana(placeholder);
  adjustCurrentMana(placeholder);
}


void Attributes::addWisdom(int& wisdom, Stats* placeholder)
{
  this->wisdom_ += wisdom;

  adjustSpellPower(placeholder);
  adjustSpellHaste(placeholder);
  adjustMovementSpeed(placeholder);
}




