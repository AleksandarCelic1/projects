#ifndef SPELL_ID_ENUMS_HPP
#define SPELL_ID_ENUMS_HPP

namespace SpellInformation
{
  enum class SpellType
  {
    HOLY = 0,
    SINFUL = 1
  };

  enum class SpellID
  {
    // [[[Templar]]]
    //    [Holy]

    ZEAL_OF_THE_TEMPLAR = 0,
    SACRED_DOMINION = 1,
    DAVIDS_DANCE = 2,
    BEHOLD = 3,
    TRIAL_BY_FIRE = 4,

    //    [Blessings]

    CAINS_THORNS = 5,
    ABELS_OFFERING = 6,
    MICHAELS_VANGUARD = 7,
    JOBS_PATIENCE = 8,
    SOLOMONS_WISDOM = 9,

    //    [Sinful]

    EYE_FOR_AN_EYE = 10,
    NO_SAINT_REMAINS = 11,
    UNWRITTEN_TESTAMENT = 12,
    VULTURES_PATIENCE = 13,
    UNHOLY_BARGAIN = 14,
    FORBIDDEN_FRUIT = 15

  };

  enum class SpellCooldown
  {
    
  };
};


#endif