#ifndef STATUS_ATTR_ENUMS_HPP
#define STATUS_ATTR_ENUMS_HPP

enum TemplarBaseStats
{
  BASE_HP = 0,
  BASE_MANA = 0,
  BASE_PHY_AP = 0,
  BASE_SPELL_POWER = 0,
  BASE_MR = 0,
  BASE_ARMOR = 0,
  BASE_MELEE_RANGE = 0,
  BASE_SPELL_RANGE = 0,
  BASE_GCD = 0,
  BASE_ARP = 0,
  BASE_SPELL_PEN = 0,

  // The next enums are divided by 100 to aquire correct float number as C++ doesnt support 
  // floats/doubles in enums

  BASE_ATTACK_SPEED = 0,
  BASE_SPELL_HASTE = 0,
  BASE_HIT_RATING = 0,
  BASE_PHY_CRIT_CHANCE = 0,
  BASE_SPELL_CRIT_CHANCE = 0,
  BASE_MOVEMENT_SPEED = 0,
  BASE_LIFESTEAL = 0,
  BASE_TENACITY = 0
} ;

enum WizardBaseStats
{
  BASE_HP = 0,
  BASE_MANA = 0,
  BASE_PHY_AP = 0,
  BASE_SPELL_POWER = 0,
  BASE_MR = 0,
  BASE_ARMOR = 0,
  BASE_MELEE_RANGE = 0,
  BASE_SPELL_RANGE = 0,
  BASE_GCD = 0,
  BASE_ARP = 0,
  BASE_SPELL_PEN = 0,

  // The next enums are divided by 100 to aquire correct float number as C++ doesnt support 
  // floats/doubles in enums

  BASE_ATTACK_SPEED = 0,
  BASE_SPELL_HASTE = 0,
  BASE_HIT_RATING = 0,
  BASE_PHY_CRIT_CHANCE = 0,
  BASE_SPELL_CRIT_CHANCE = 0,
  BASE_MOVEMENT_SPEED = 0,
  BASE_LIFESTEAL = 0,
  BASE_TENACITY = 0
} ;

enum class PriestBaseStats
{
  BASE_HP = 0,
  BASE_MANA = 0,
  BASE_PHY_AP = 0,
  BASE_SPELL_POWER = 0,
  BASE_MR = 0,
  BASE_ARMOR = 0,
  BASE_MELEE_RANGE = 0,
  BASE_SPELL_RANGE = 0,
  BASE_GCD = 0,
  BASE_ARP = 0,
  BASE_SPELL_PEN = 0,

  // The next enums are divided by 100 to aquire correct float number as C++ doesnt support 
  // floats/doubles in enums

  BASE_ATTACK_SPEED = 0,
  BASE_SPELL_HASTE = 0,
  BASE_HIT_RATING = 0,
  BASE_PHY_CRIT_CHANCE = 0,
  BASE_SPELL_CRIT_CHANCE = 0,
  BASE_MOVEMENT_SPEED = 0,
  BASE_LIFESTEAL = 0,
  BASE_TENACITY = 0
} ;

enum class KnightBaseStats
{
  BASE_HP = 0,
  BASE_MANA = 0,
  BASE_PHY_AP = 0,
  BASE_SPELL_POWER = 0,
  BASE_MR = 0,
  BASE_ARMOR = 0,
  BASE_MELEE_RANGE = 0,
  BASE_SPELL_RANGE = 0,
  BASE_GCD = 0,
  BASE_ARP = 0,
  BASE_SPELL_PEN = 0,

  // The next enums are divided by 100 to aquire correct float number as C++ doesnt support 
  // floats/doubles in enums

  BASE_ATTACK_SPEED = 0,
  BASE_SPELL_HASTE = 0,
  BASE_HIT_RATING = 0,
  BASE_PHY_CRIT_CHANCE = 0,
  BASE_SPELL_CRIT_CHANCE = 0,
  BASE_MOVEMENT_SPEED = 0,
  BASE_LIFESTEAL = 0,
  BASE_TENACITY = 0
};

enum class TemplarBaseAttr
{
  BASE_STR = 0,
  BASE_DEX = 0,
  BASE_INT = 0,
  BASE_WIS = 0,
  BASE_HAV = 0,
  BASE_CHA = 0,
  BASE_INS = 0,
  BASE_PCT = 0,
  BASE_VMP = 0,
  BASE_FTH = 0,
  BASE_TNC = 0
};

enum class KnightBaseAttr
{
  BASE_STR = 0,
  BASE_DEX = 0,
  BASE_INT = 0,
  BASE_WIS = 0,
  BASE_HAV = 0,
  BASE_CHA = 0,
  BASE_INS = 0,
  BASE_PCT = 0,
  BASE_VMP = 0,
  BASE_FTH = 0,
  BASE_TNC = 0
};

enum class WizardBaseAttr
{
  BASE_STR = 0,
  BASE_DEX = 0,
  BASE_INT = 0,
  BASE_WIS = 0,
  BASE_HAV = 0,
  BASE_CHA = 0,
  BASE_INS = 0,
  BASE_PCT = 0,
  BASE_VMP = 0,
  BASE_FTH = 0,
  BASE_TNC = 0
};

enum class PriestBaseAttr
{
  BASE_STR = 0,
  BASE_DEX = 0,
  BASE_INT = 0,
  BASE_WIS = 0,
  BASE_HAV = 0,
  BASE_CHA = 0,
  BASE_INS = 0,
  BASE_PCT = 0,
  BASE_VMP = 0,
  BASE_FTH = 0,
  BASE_TNC = 0
};
#endif