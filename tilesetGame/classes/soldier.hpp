#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "character.hpp"
#include "hourglass.hpp"
class Tools;



const int SOLDIER_SPECIAL_ABILITY_RANGE = 1;
const int ABILITY_DAMAGE_AND_HP_RESTORATION = 2;

class Soldier : virtual public Character
{
  private:

    Hourglass* special_ability_hourglass_cooldown_;
    int ability_damage_;
    int ability_hp_restoration_;
    bool can_use_special_ability_;

    int amount_of_silver_keys_;
    int amount_of_gold_keys_;

  public:

    Soldier();
    Soldier(const Soldier& copy) = delete;
    ~Soldier();

    int getAmountOfSilverKeys() const { return this->amount_of_silver_keys_;}
    int getAmountOfGoldKeys() const { return this->amount_of_gold_keys_;}
    Hourglass* getHourglass() const { return this->special_ability_hourglass_cooldown_;}

    void setHourglass(Hourglass* hourglass) { this->special_ability_hourglass_cooldown_ = hourglass;}
    void setAmountOfSilverKeys(int amount) { this->amount_of_silver_keys_ = amount;}
    void setAmountOfGoldKeys(int amount) { this->amount_of_gold_keys_ = amount;}



    void increaseAbilityDamage() { this->ability_damage_++; }
    void increaseAbilityHeal() { this->ability_hp_restoration_++; }
    void decreaseAbilityDamage() { this->ability_damage_--;}
    void decreaseAbilityHeal() { this->ability_hp_restoration_--;}
    
    void ability(Game* game) override;
    std::pair<int, int> checkMapObjNearby(Map* current_level_map, Detection where_looking) noexcept;
};

#endif