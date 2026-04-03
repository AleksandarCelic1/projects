#ifndef ENUMS__HPP
#define ENUMS__HPP

typedef enum 
{
  TEMPLAR = 0,
  KNIGHT = 1,
  WIZARD = 2,
  PRIEST = 3
  
} ClassType;


typedef enum
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
} TemplarBaseStats;

typedef enum
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
} WizardBaseStats;

typedef enum
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
} PriestBaseStats;

typedef enum
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
} KnightBaseStats;

#endif