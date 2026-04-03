#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "../../constants_/constants.hpp"
#include "../../constants_/enums.hpp"

class Stats;

class Attributes
{
  private:
    int strenght_;
    int dexterity_;

    int intellect_;
    int wisdom_;

    int havoc_;
    int chaos_;

    int insight_;
    int perception_;

    int vamp_;
    int faith_;
    int tenacity_;

  public:
    // Constructor Destructor Copy Constructor 
    Attributes();
    Attributes(int loaded_str, int loaded_dex, int loaded_int, int loaded_wisd, int loaded_havoc,
    int loaded_chaos, int loaded_isg, int loaded_percp, int loaded_vamp, int loaded_faith, int loaded_tenacity);
    Attributes(const Attributes& copy) = delete;
    ~Attributes() = default;

    // Getters
    int getStrength() const { return this->strenght_; }
    int getDexterity() const { return this->dexterity_; }
    int getIntellect() const { return this->intellect_; }
    int getWisdom() const { return this->wisdom_; }
    int getHavoc() const { return this->havoc_; }
    int getChaos() const { return this->chaos_; }
    int getInsight() const { return this->insight_; }
    int getPerception() const { return this->perception_; }
    int getVamp() const { return this->vamp_; }
    int getFaith() const { return this->faith_; }
    int getTenacity() const { return this->tenacity_; }

    // Setters

    void addStrength(int& strength, Stats* placeholder) noexcept;
    void addDexterity(int& dexterity, Stats* placeholder) noexcept;
    void addIntellect(int& intellect, Stats* placeholder) noexcept;
    void addWisdom(int& wisdom, Stats* placeholder) noexcept;
    void addHavoc(int& havoc, Stats* placeholder) noexcept;
    void addChaos(int& chaos, Stats* placeholder) noexcept;
    void addInsight(int& insight, Stats* placeholder) noexcept;
    void addPerception(int& perception, Stats* placeholder) noexcept;
    void addVamp(int& vamp, Stats* placeholder) noexcept;
    void addFaith(int& faith, Stats* placeholder) noexcept;
    void addTenacity(int& tenacity, Stats* placeholder) noexcept;

    void subtractStrength(int& strength, Stats* placeholder) noexcept;
    void subtractDexterity(int& dexterity, Stats* placeholder) noexcept;
    void subtractIntellect(int& intellect, Stats* placeholder) noexcept;
    void subtractWisdom(int& wisdom, Stats* placeholder) noexcept;
    void subtractHavoc(int& havoc, Stats* placeholder) noexcept;
    void subtractChaos(int& chaos, Stats* placeholder) noexcept;
    void subtractInsight(int& insight, Stats* placeholder) noexcept;
    void subtractPerception(int& perception, Stats* placeholder) noexcept;
    void subtractVamp(int& vamp, Stats* placeholder) noexcept;
    void subtractFaith(int& faith, Stats* placeholder) noexcept;
    void subtractTenacity(int& tenacity, Stats* placeholder) noexcept;

    // Functions 
    void adjustBaseHealth(Stats* placeholder) noexcept;
    void adjustCurrentHealth(Stats* placeholder) noexcept;
    void adjustBaseMana(Stats* placeholder) noexcept;
    void adjustCurrentMana(Stats* placeholder) noexcept;
    void adjustPhysicalPower(Stats* placeholder) noexcept;
    void adjustSpellPower(Stats* placeholder) noexcept;
    void adjustAttackSpeed(Stats* placeholder) noexcept;
    void adjustSpellHaste(Stats* placeholder) noexcept;
    void adjustHitRating(Stats* placeholder) noexcept;
    void adjustPhysicalCritChance(Stats* placeholder) noexcept;
    void adjustMagicCritChance(Stats* placeholder) noexcept;
    void adjustMagicResistence(Stats* placeholder) noexcept;
    void adjustArmor(Stats* placeholder) noexcept;
    void adjustMeleeRange(Stats* placeholder) noexcept;
    void adjustSpellRange(Stats* placeholder) noexcept;
    void adjustGlobalCooldown(Stats* placeholder) noexcept;    
    void adjustMovementSpeed(Stats* placeholder) noexcept;
    void adjustArmorPenetration(Stats* placeholder) noexcept;
    void adjustSpellPenetration(Stats* placeholder) noexcept; 
    void adjustLifesteal(Stats* placeholder) noexcept; 
    void adjustTenacity(Stats* placeholder) noexcept; 

  
};


#endif