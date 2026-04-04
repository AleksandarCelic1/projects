#ifndef STATS_HPP
#define STATS_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"


class Stats
{
  private:
    int base_health_;
    int current_health_;

    int base_mana_;
    int current_mana_;

    int physical_power_;
    int spell_power_;

    float attack_speed_; // FORMULA 1/ attack speed to achieve 
    float spell_haste_;
    
    float hit_rating_;

    float physical_crit_chance_;
    float magic_crit_chance_;

    int magic_resistance_;
    int armor_;
    int melee_range_;
    int spell_range_;
    int global_cooldown_;

    int armor_penetration_;
    int spell_penetration_;

    float movement_speed_;
    float lifesteal_;
    float tenacity_;

  public:
    // Constructor Destructor Copy Constructor 
    Stats(ClassType type);
    Stats(int loaded_base_hp, int loaded_current_hp, int loaded_base_mana, int loaded_current_mana, int loaded_physical_power, int loaded_sp, float loaded_attack_speed,
          float loaded_spell_haste, float loaded_hit_rating, float loaded_phy_crit, float loaded_mag_crit, int loaded_magic_resis,
          int loaded_armor, int loaded_melee_range, int loaded_spell_range, int loaded_gcd, int loaded_arpen, int loaded_spellpen,
          float loaded_movespeed, float loaded_lifesteal, float loaded_tenacity);
    Stats(const Stats* copy) = delete;
    ~Stats() = default;    
    // Getters
    int getBaseHealth() const { return this->base_health_; }
    int getCurrentHealth() const { return this->current_health_; }
    int getBaseMana() const { return this->base_mana_; }
    int getCurrentMana() const { return this->current_mana_; }
    int getPhysicalPower() const { return this->physical_power_; }
    int getSpellPower() const { return this->spell_power_; }
    float getAttackSpeed() const { return this->attack_speed_; }
    float getSpellHaste() const { return this->spell_haste_; }
    float getHitRating() const { return this->hit_rating_; }
    float getPhysicalCritChance() const { return this->physical_crit_chance_; }
    float getMagicCritChance() const { return this->magic_crit_chance_; }
    int getMagicResistance() const { return this->magic_resistance_; }
    int getArmor() const { return this->armor_; }
    int getMeleeRange() const { return this->melee_range_; }
    int getSpellRange() const { return this->spell_range_; }
    int getGlobalCooldown() const { return this->global_cooldown_; }
    float getMovementSpeed() const { return this->movement_speed_; }
    int getArmorPenetration() const { return this->armor_penetration_; }
    int getSpellPenetration() const { return this->spell_penetration_; }
    int getLifeSteal() const { return this->lifesteal_; }
    float getTenacity() const { return this->tenacity_; }

    // Setters
    void setBaseHealth(int& base_health) { this->base_health_ = base_health; }
    void setCurrentHealth(int& current_health) { this->current_health_ = current_health; }
    void setBaseMana(int& base_mana) { this->base_mana_ = base_mana; }
    void setCurrentMana(int& current_mana) { this->current_mana_ = current_mana; }
    void setPhysicalPower(int& physical_power) { this->physical_power_ = physical_power; }
    void setSpellPower(int& spell_power) { this->spell_power_ = spell_power; }
    void setAttackSpeed(float& attack_speed) { this->attack_speed_ = attack_speed; }
    void setSpellHaste(float& spell_haste) { this->spell_haste_ = spell_haste; }
    void setHitRating(float& hit_rating) { this->hit_rating_ = hit_rating; }
    void setPhysicalCritChance(float& physical_crit_chance) { this->physical_crit_chance_ = physical_crit_chance; }
    void setMagicCritChance(float& magic_crit_chance) { this->magic_crit_chance_ = magic_crit_chance; }
    void setMagicResistance(int& magic_resistence) { this->magic_resistance_ = magic_resistence; }
    void setArmor(int& armor) { this->armor_ = armor; }
    void setMeleeRange(int& melee_range) { this->melee_range_ = melee_range; }
    void setSpellRange(int& spell_range) { this->spell_range_ = spell_range; }
    void setGlobalCooldown(int& global_cooldown) { this->global_cooldown_ = global_cooldown; }
    void setMovementSpeed(float& movement_speed) { this->movement_speed_ = movement_speed; }
    void setArmorPenetration(int& armor_pen) { this->armor_penetration_ = armor_pen; }
    void setSpellPenetration(int& spell_pen) { this->spell_penetration_ = spell_pen; }
    void setLifeSteal(float& lifesteal) { this->lifesteal_ = lifesteal; }
    void setTenacity(float& tenacity) { this->tenacity_ = tenacity; }


    // Functions

    void assignBaseStatsToTemplar() noexcept;
    void assignBaseStatsToKnight() noexcept;
    void assignBaseStatsToWizard() noexcept;
    void assignBaseStatsToPriest() noexcept;



    

};


#endif