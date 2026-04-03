#include "attributes.hpp"
#include "stats.hpp"


Attributes::Attributes()
{
  // Do when making a Character >> Stats ctor >> Attr ctor >> adjust everything after Attr
  
}

Attributes:: Attributes(int loaded_str, int loaded_dex, int loaded_int, int loaded_wisd, int loaded_havoc,
int loaded_chaos, int loaded_isg, int loaded_percp, int loaded_vamp, int loaded_faith, int loaded_tenacity)
{
  this->strenght_ = loaded_str;
  this->dexterity_ = loaded_dex;
  this->intellect_ = loaded_int;
  this->wisdom_ = loaded_wisd;
  this->havoc_ = loaded_havoc;
  this->chaos_ = loaded_chaos;
  this->insight_ = loaded_isg;
  this->perception_ = loaded_percp;
  this->vamp_ = loaded_vamp;
  this->faith_ = loaded_faith;
  this->tenacity_ = loaded_tenacity;

  // Do i need to recalculate the stats here << !
}


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

void Attributes::addHavoc(int& havoc, Stats* placeholder)
{
  this->havoc_ += havoc;

  adjustArmorPenetration(placeholder);
}


void Attributes::addChaos(int& chaos, Stats* placeholder)
{
  this->chaos_ += chaos;

  adjustSpellPenetration(placeholder);
}

void Attributes::addInsight(int& insight, Stats* placeholder)
{
  this->insight_ += insight;

  adjustMeleeRange(placeholder);
}

void Attributes::addPerception(int& perception, Stats* placeholder)
{
  this->perception_ += perception;

  adjustSpellRange(placeholder);
}

void Attributes::addVamp(int& vamp, Stats* placeholder)
{
  this->vamp_ += vamp;

  adjustLifesteal(placeholder);
}


void Attributes::addFaith(int& faith, Stats* placeholder)
{
  this->faith_ += faith;

  adjustGlobalCooldown(placeholder);
}

void Attributes::addTenacity(int& tenacity, Stats* placeholder)
{
  this->tenacity_ += tenacity;

  adjustTenacity(placeholder);
}


// SUBTRACT < -- !
void Attributes::subtractStrength(int& strength, Stats* placeholder)
{
  this->strenght_ -= strength;

  adjustBaseHealth(placeholder);
  adjustPhysicalPower(placeholder);
  adjustCurrentHealth(placeholder);
}

void Attributes::subtractDexterity(int& dexterity, Stats* placeholder)
{
  this->dexterity_ -= dexterity;

  adjustPhysicalPower(placeholder);
  adjustAttackSpeed(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::subtractIntellect(int& intellect, Stats* placeholder)
{
  this->intellect_ -= intellect;

  adjustSpellPower(placeholder);
  adjustBaseMana(placeholder);
  adjustCurrentMana(placeholder);
}

void Attributes::subtractWisdom(int& wisdom, Stats* placeholder)
{
  this->wisdom_ -= wisdom;

  adjustSpellPower(placeholder);
  adjustSpellHaste(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::subtractHavoc(int& havoc, Stats* placeholder)
{
  this->havoc_ -= havoc;

  adjustArmorPenetration(placeholder);
}

void Attributes::subtractChaos(int& chaos, Stats* placeholder)
{
  this->chaos_ -= chaos;

  adjustSpellPenetration(placeholder);
}

void Attributes::subtractInsight(int& insight, Stats* placeholder)
{
  this->insight_ -= insight;

  adjustMeleeRange(placeholder);
}

void Attributes::subtractPerception(int& perception, Stats* placeholder)
{
  this->perception_ -= perception;

  adjustSpellRange(placeholder);
}

void Attributes::subtractVamp(int& vamp, Stats* placeholder)
{
  this->vamp_ -= vamp;

  adjustLifesteal(placeholder);
}

void Attributes::subtractFaith(int& faith, Stats* placeholder)
{
  this->faith_ -= faith;

  adjustGlobalCooldown(placeholder);
}

void Attributes::subtractTenacity(int& tenacity, Stats* placeholder)
{
  this->tenacity_ -= tenacity;

  adjustTenacity(placeholder);
}