#include "../include_/attributes.hpp"
#include "../include_/stats.hpp"

Attributes::Attributes(ClassType type)
{
  // Do when making a Character >> Stats ctor >> Attr ctor >> adjust everything after Attr
  switch (type)
  {
    case TEMPLAR:
      assignBaseAttrToTemplar();
      break;
    case KNIGHT:
      assignBaseAttrToKnight();
      break;
    case WIZARD:
      assignBaseAttrToWizard();
      break;
    case PRIEST:
      assignBaseAttrToPriest();
      break;
    default:
      std::cout << "[DEBUG] Stats.cpp, ClassType given does not match any normal class type!\n";
      break;
  }


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


void Attributes::addStrength(int& strength, Stats* placeholder) noexcept
{
  this->strenght_ += strength;

  adjustBaseHealth(placeholder);
  adjustPhysicalPower(placeholder);
  adjustCurrentHealth(placeholder);
}

void Attributes::addDexterity(int& dexterity, Stats* placeholder) noexcept
{
  this->dexterity_ += dexterity;

  adjustPhysicalPower(placeholder);
  adjustAttackSpeed(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::addIntellect(int& intellect, Stats* placeholder) noexcept
{
  this->intellect_ += intellect;

  adjustSpellPower(placeholder);
  adjustBaseMana(placeholder);
  adjustCurrentMana(placeholder);
}


void Attributes::addWisdom(int& wisdom, Stats* placeholder) noexcept
{
  this->wisdom_ += wisdom;

  adjustSpellPower(placeholder);
  adjustSpellHaste(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::addHavoc(int& havoc, Stats* placeholder) noexcept
{
  this->havoc_ += havoc;

  adjustArmorPenetration(placeholder);
}


void Attributes::addChaos(int& chaos, Stats* placeholder) noexcept
{
  this->chaos_ += chaos;

  adjustSpellPenetration(placeholder);
}

void Attributes::addInsight(int& insight, Stats* placeholder) noexcept
{
  this->insight_ += insight;

  adjustMeleeRange(placeholder);
}

void Attributes::addPerception(int& perception, Stats* placeholder) noexcept
{
  this->perception_ += perception;

  adjustSpellRange(placeholder);
}

void Attributes::addVamp(int& vamp, Stats* placeholder) noexcept
{
  this->vamp_ += vamp;

  adjustLifesteal(placeholder);
}


void Attributes::addFaith(int& faith, Stats* placeholder) noexcept
{
  this->faith_ += faith;

  adjustGlobalCooldown(placeholder);
}

void Attributes::addTenacity(int& tenacity, Stats* placeholder) noexcept
{
  this->tenacity_ += tenacity;

  adjustTenacity(placeholder);
}


// SUBTRACT < -- !
void Attributes::subtractStrength(int& strength, Stats* placeholder) noexcept
{
  this->strenght_ -= strength;

  adjustBaseHealth(placeholder);
  adjustPhysicalPower(placeholder);
  adjustCurrentHealth(placeholder);
}

void Attributes::subtractDexterity(int& dexterity, Stats* placeholder) noexcept
{
  this->dexterity_ -= dexterity;

  adjustPhysicalPower(placeholder);
  adjustAttackSpeed(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::subtractIntellect(int& intellect, Stats* placeholder) noexcept
{
  this->intellect_ -= intellect;

  adjustSpellPower(placeholder);
  adjustBaseMana(placeholder);
  adjustCurrentMana(placeholder);
}

void Attributes::subtractWisdom(int& wisdom, Stats* placeholder) noexcept
{
  this->wisdom_ -= wisdom;

  adjustSpellPower(placeholder);
  adjustSpellHaste(placeholder);
  adjustMovementSpeed(placeholder);
}

void Attributes::subtractHavoc(int& havoc, Stats* placeholder) noexcept
{
  this->havoc_ -= havoc;

  adjustArmorPenetration(placeholder);
}

void Attributes::subtractChaos(int& chaos, Stats* placeholder) noexcept
{
  this->chaos_ -= chaos;

  adjustSpellPenetration(placeholder);
}

void Attributes::subtractInsight(int& insight, Stats* placeholder) noexcept
{
  this->insight_ -= insight;

  adjustMeleeRange(placeholder);
}

void Attributes::subtractPerception(int& perception, Stats* placeholder) noexcept
{
  this->perception_ -= perception;

  adjustSpellRange(placeholder);
}

void Attributes::subtractVamp(int& vamp, Stats* placeholder) noexcept
{
  this->vamp_ -= vamp;

  adjustLifesteal(placeholder);
}

void Attributes::subtractFaith(int& faith, Stats* placeholder) noexcept
{
  this->faith_ -= faith;

  adjustGlobalCooldown(placeholder);
}

void Attributes::subtractTenacity(int& tenacity, Stats* placeholder) noexcept
{
  this->tenacity_ -= tenacity;

  adjustTenacity(placeholder);
}

void Attributes::assignBaseAttrToTemplar() noexcept
{
  this->strenght_ = static_cast<int>(TemplarBaseAttr::BASE_STR);
  this->dexterity_ = static_cast<int>(TemplarBaseAttr::BASE_DEX);

  this->intellect_ = static_cast<int>(TemplarBaseAttr::BASE_INT);
  this->wisdom_ = static_cast<int>(TemplarBaseAttr::BASE_WIS);

  this->havoc_ = static_cast<int>(TemplarBaseAttr::BASE_HAV);
  this->chaos_ = static_cast<int>(TemplarBaseAttr::BASE_CHA);

  this->insight_ = static_cast<int>(TemplarBaseAttr::BASE_INS);
  this->perception_ = static_cast<int>(TemplarBaseAttr::BASE_PCT);

  this->vamp_ = static_cast<int>(TemplarBaseAttr::BASE_VMP);
  this->faith_ = static_cast<int>(TemplarBaseAttr::BASE_FTH);
  this->tenacity_ = static_cast<int>(TemplarBaseAttr::BASE_TNC);
}

void Attributes::assignBaseAttrToKnight() noexcept
{
  this->strenght_ = static_cast<int>(KnightBaseAttr::BASE_STR);
  this->dexterity_ = static_cast<int>(KnightBaseAttr::BASE_DEX);

  this->intellect_ = static_cast<int>(KnightBaseAttr::BASE_INT);
  this->wisdom_ = static_cast<int>(KnightBaseAttr::BASE_WIS);

  this->havoc_ = static_cast<int>(KnightBaseAttr::BASE_HAV);
  this->chaos_ = static_cast<int>(KnightBaseAttr::BASE_CHA);

  this->insight_ = static_cast<int>(KnightBaseAttr::BASE_INS);
  this->perception_ = static_cast<int>(KnightBaseAttr::BASE_PCT);

  this->vamp_ = static_cast<int>(KnightBaseAttr::BASE_VMP);
  this->faith_ = static_cast<int>(KnightBaseAttr::BASE_FTH);
  this->tenacity_ = static_cast<int>(KnightBaseAttr::BASE_TNC);
}

void Attributes::assignBaseAttrToWizard() noexcept
{
  this->strenght_ = static_cast<int>(WizardBaseAttr::BASE_STR);
  this->dexterity_ = static_cast<int>(WizardBaseAttr::BASE_DEX);

  this->intellect_ = static_cast<int>(WizardBaseAttr::BASE_INT);
  this->wisdom_ = static_cast<int>(WizardBaseAttr::BASE_WIS);

  this->havoc_ = static_cast<int>(WizardBaseAttr::BASE_HAV);
  this->chaos_ = static_cast<int>(WizardBaseAttr::BASE_CHA);

  this->insight_ = static_cast<int>(WizardBaseAttr::BASE_INS);
  this->perception_ = static_cast<int>(WizardBaseAttr::BASE_PCT);

  this->vamp_ = static_cast<int>(WizardBaseAttr::BASE_VMP);
  this->faith_ = static_cast<int>(WizardBaseAttr::BASE_FTH);
  this->tenacity_ = static_cast<int>(WizardBaseAttr::BASE_TNC);
}

void Attributes::assignBaseAttrToPriest() noexcept
{
  this->strenght_ = static_cast<int>(PriestBaseAttr::BASE_STR);
  this->dexterity_ = static_cast<int>(PriestBaseAttr::BASE_DEX);

  this->intellect_ = static_cast<int>(PriestBaseAttr::BASE_INT);
  this->wisdom_ = static_cast<int>(PriestBaseAttr::BASE_WIS);

  this->havoc_ = static_cast<int>(PriestBaseAttr::BASE_HAV);
  this->chaos_ = static_cast<int>(PriestBaseAttr::BASE_CHA);

  this->insight_ = static_cast<int>(PriestBaseAttr::BASE_INS);
  this->perception_ = static_cast<int>(PriestBaseAttr::BASE_PCT);

  this->vamp_ = static_cast<int>(PriestBaseAttr::BASE_VMP);
  this->faith_ = static_cast<int>(PriestBaseAttr::BASE_FTH);
  this->tenacity_ = static_cast<int>(PriestBaseAttr::BASE_TNC);
}

void Attributes::adjustBaseHealth(Stats* placeholder) noexcept
{

}

void Attributes::adjustCurrentHealth(Stats* placeholder) noexcept
{

}

void Attributes::adjustBaseMana(Stats* placeholder) noexcept
{

}

void Attributes::adjustCurrentMana(Stats* placeholder) noexcept
{

}

void Attributes::adjustPhysicalPower(Stats* placeholder) noexcept
{

}

void Attributes::adjustSpellPower(Stats* placeholder) noexcept
{

}

void Attributes::adjustAttackSpeed(Stats* placeholder) noexcept
{

}

void Attributes::adjustSpellHaste(Stats* placeholder) noexcept
{

}

void Attributes::adjustHitRating(Stats* placeholder) noexcept
{

}

void Attributes::adjustPhysicalCritChance(Stats* placeholder) noexcept
{

}

void Attributes::adjustMagicCritChance(Stats* placeholder) noexcept
{

}

void Attributes::adjustMagicResistence(Stats* placeholder) noexcept
{

}

void Attributes::adjustArmor(Stats* placeholder) noexcept
{

}

void Attributes::adjustMeleeRange(Stats* placeholder) noexcept
{

}

void Attributes::adjustSpellRange(Stats* placeholder) noexcept
{

}

void Attributes::adjustGlobalCooldown(Stats* placeholder) noexcept
{

}

void Attributes::adjustMovementSpeed(Stats* placeholder) noexcept
{

}

void Attributes::adjustArmorPenetration(Stats* placeholder) noexcept
{

}

void Attributes::adjustSpellPenetration(Stats* placeholder) noexcept
{

}

void Attributes::adjustLifesteal(Stats* placeholder) noexcept
{

}

void Attributes::adjustTenacity(Stats* placeholder) noexcept
{

}