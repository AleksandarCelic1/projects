#include "stats.hpp"

Stats::Stats(ClassType type)
{
  switch (type)
  {
    case TEMPLAR:
      assignBaseStatsToTemplar();
      break;
    case KNIGHT:
      assignBaseStatsToKnight();
      break;
    case WIZARD:
      assignBaseStatsToWizard();
      break;
    case PRIEST:
      assignBaseStatsToPriest();
      break;
    default:
      std::cout << "[DEBUG] Stats.cpp, ClassType given does not match any normal class type!\n";
      break;
  }
}


Stats::Stats(int loaded_base_hp, int loaded_current_hp, int loaded_base_mana, int loaded_current_mana,
int loaded_physical_power, int loaded_sp, float loaded_attack_speed, float loaded_spell_haste,
float loaded_hit_rating, float loaded_phy_crit, float loaded_mag_crit, int loaded_magic_resis,
int loaded_armor, int loaded_melee_range, int loaded_spell_range, int loaded_gcd, int loaded_arpen, int loaded_spellpen,
float loaded_movespeed, float loaded_lifesteal, float loaded_tenacity)
{
  this->base_health_ = loaded_base_hp;
  this->current_health_ = loaded_current_hp;
  this->base_mana_ = loaded_base_mana;
  this->current_mana_ = loaded_current_mana;
  this->physical_power_ = loaded_physical_power;
  this->spell_power_ = loaded_sp;
  this->attack_speed_ = loaded_attack_speed;
  this->spell_haste_ = loaded_spell_haste;
  this->hit_rating_ = loaded_hit_rating;
  this->physical_crit_chance_ = loaded_phy_crit;
  this->magic_crit_chance_ = loaded_mag_crit;
  this->magic_resistance_ = loaded_magic_resis;
  this->armor_ = loaded_armor;
  this->melee_range_ = loaded_melee_range;
  this->spell_range_ = loaded_spell_range;
  this->global_cooldown_ = loaded_gcd;
  this->armor_penetration_ = loaded_arpen;
  this->spell_penetration_ = loaded_spellpen;
  this->movement_speed_ = loaded_movespeed;
  this->lifesteal_ = loaded_lifesteal;
  this->tenacity_ = loaded_tenacity;
}

void Stats::assignBaseStatsToKnight()
{
  this->base_health_ = static_cast<int>(KnightBaseStats::BASE_HP);
  this->current_health_ = this->base_health_;

  this->base_mana_ = static_cast<int>(KnightBaseStats::BASE_MANA);
  this->current_mana_ = this->base_mana_;

  this->physical_power_ = static_cast<int>(KnightBaseStats::BASE_PHY_AP);
  this->spell_power_ = static_cast<int>(KnightBaseStats::BASE_SPELL_POWER);

  this->attack_speed_ = static_cast<float>(KnightBaseStats::BASE_ATTACK_SPEED) / 100.0f;
  this->spell_haste_ = static_cast<float>(KnightBaseStats::BASE_SPELL_HASTE) / 100.0f;
  
  this->hit_rating_ = static_cast<float>(KnightBaseStats::BASE_HIT_RATING) / 100.0f;

  this->physical_crit_chance_ = static_cast<float>(KnightBaseStats::BASE_PHY_CRIT_CHANCE) / 100.0f;
  this->magic_crit_chance_ = static_cast<float>(KnightBaseStats::BASE_SPELL_CRIT_CHANCE) / 100.0f;

  this->magic_resistance_ = static_cast<int>(KnightBaseStats::BASE_MR);
  this->armor_ = static_cast<int>(KnightBaseStats::BASE_ARMOR);
  this->melee_range_ = static_cast<int>(KnightBaseStats::BASE_MELEE_RANGE);
  this->spell_range_ = static_cast<int>(KnightBaseStats::BASE_SPELL_RANGE);
  this->global_cooldown_ = static_cast<int>(KnightBaseStats::BASE_GCD);

  this->armor_penetration_ = static_cast<int>(KnightBaseStats::BASE_ARP);
  this->spell_penetration_ = static_cast<int>(KnightBaseStats::BASE_SPELL_PEN);

  this->movement_speed_ = static_cast<float>(KnightBaseStats::BASE_MOVEMENT_SPEED) / 100.0f;
  this->lifesteal_ = static_cast<float>(KnightBaseStats::BASE_LIFESTEAL) / 100.0f;
  this->tenacity_ = static_cast<float>(KnightBaseStats::BASE_TENACITY) / 100.0f;
}

void Stats::assignBaseStatsToWizard()
{
  this->base_health_ = static_cast<int>(WizardBaseStats::BASE_HP);
  this->current_health_ = this->base_health_;

  this->base_mana_ = static_cast<int>(WizardBaseStats::BASE_MANA);
  this->current_mana_ = this->base_mana_;

  this->physical_power_ = static_cast<int>(WizardBaseStats::BASE_PHY_AP);
  this->spell_power_ = static_cast<int>(WizardBaseStats::BASE_SPELL_POWER);

  this->attack_speed_ = static_cast<float>(WizardBaseStats::BASE_ATTACK_SPEED) / 100.0f;
  this->spell_haste_ = static_cast<float>(WizardBaseStats::BASE_SPELL_HASTE) / 100.0f;
  
  this->hit_rating_ = static_cast<float>(WizardBaseStats::BASE_HIT_RATING) / 100.0f;

  this->physical_crit_chance_ = static_cast<float>(WizardBaseStats::BASE_PHY_CRIT_CHANCE) / 100.0f;
  this->magic_crit_chance_ = static_cast<float>(WizardBaseStats::BASE_SPELL_CRIT_CHANCE) / 100.0f;

  this->magic_resistance_ = static_cast<int>(WizardBaseStats::BASE_MR);
  this->armor_ = static_cast<int>(WizardBaseStats::BASE_ARMOR);
  this->melee_range_ = static_cast<int>(WizardBaseStats::BASE_MELEE_RANGE);
  this->spell_range_ = static_cast<int>(WizardBaseStats::BASE_SPELL_RANGE);
  this->global_cooldown_ = static_cast<int>(WizardBaseStats::BASE_GCD);

  this->armor_penetration_ = static_cast<int>(WizardBaseStats::BASE_ARP);
  this->spell_penetration_ = static_cast<int>(WizardBaseStats::BASE_SPELL_PEN);

  this->movement_speed_ = static_cast<float>(WizardBaseStats::BASE_MOVEMENT_SPEED) / 100.0f;
  this->lifesteal_ = static_cast<float>(WizardBaseStats::BASE_LIFESTEAL) / 100.0f;
  this->tenacity_ = static_cast<float>(WizardBaseStats::BASE_TENACITY) / 100.0f;
}

void Stats::assignBaseStatsToPriest()
{
  this->base_health_ = static_cast<int>(PriestBaseStats::BASE_HP);
  this->current_health_ = this->base_health_;

  this->base_mana_ = static_cast<int>(PriestBaseStats::BASE_MANA);
  this->current_mana_ = this->base_mana_;

  this->physical_power_ = static_cast<int>(PriestBaseStats::BASE_PHY_AP);
  this->spell_power_ = static_cast<int>(PriestBaseStats::BASE_SPELL_POWER);

  this->attack_speed_ = static_cast<float>(PriestBaseStats::BASE_ATTACK_SPEED) / 100.0f;
  this->spell_haste_ = static_cast<float>(PriestBaseStats::BASE_SPELL_HASTE) / 100.0f;
  
  this->hit_rating_ = static_cast<float>(PriestBaseStats::BASE_HIT_RATING) / 100.0f;

  this->physical_crit_chance_ = static_cast<float>(PriestBaseStats::BASE_PHY_CRIT_CHANCE) / 100.0f;
  this->magic_crit_chance_ = static_cast<float>(PriestBaseStats::BASE_SPELL_CRIT_CHANCE) / 100.0f;

  this->magic_resistance_ = static_cast<int>(PriestBaseStats::BASE_MR);
  this->armor_ = static_cast<int>(PriestBaseStats::BASE_ARMOR);
  this->melee_range_ = static_cast<int>(PriestBaseStats::BASE_MELEE_RANGE);
  this->spell_range_ = static_cast<int>(PriestBaseStats::BASE_SPELL_RANGE);
  this->global_cooldown_ = static_cast<int>(PriestBaseStats::BASE_GCD);

  this->armor_penetration_ = static_cast<int>(PriestBaseStats::BASE_ARP);
  this->spell_penetration_ = static_cast<int>(PriestBaseStats::BASE_SPELL_PEN);

  this->movement_speed_ = static_cast<float>(PriestBaseStats::BASE_MOVEMENT_SPEED) / 100.0f;
  this->lifesteal_ = static_cast<float>(PriestBaseStats::BASE_LIFESTEAL) / 100.0f;
  this->tenacity_ = static_cast<float>(PriestBaseStats::BASE_TENACITY) / 100.0f;
}
