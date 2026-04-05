#ifndef SPELL_HPP
#define SPELL_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"

class Enemy;
class Character;

class Spell
{
  private:

    bool usable_; 
    size_t timer_until_usalbe_;

    SpellInformation::SpellType type_;
    SpellInformation::SpellID id_;
    SpellInformation::SpellCooldown cdr_;


  public:

    // Constructor Destructor Copy Constructor
    Spell(SpellInformation::SpellType new_type, SpellInformation::SpellID new_id, SpellInformation::SpellCooldown new_cdr);
    Spell(const Spell& copy) = delete;
    virtual ~Spell() = default; // < - - - - - - - - Not entirely Sure

    // Getters
    bool isUsable() const { return this->usable_; }
    size_t getTimer() const { return this->timer_until_usalbe_; }

    SpellInformation::SpellType getType() const { return this->type_; }
    SpellInformation::SpellID getID() const { return this->id_; }
    SpellInformation::SpellCooldown getCDR() const { return this->cdr_; }

    // Setters
    void setUsable(bool& new_bool) { this->usable_ = new_bool; }
    void setTimer(size_t& new_timer) { this->timer_until_usalbe_ = new_timer; }
    void setType(SpellInformation::SpellType& new_type) { this->type_ = new_type; }
    void setID(SpellInformation::SpellID& new_id) { this->id_ = new_id; }
    void setCDR(SpellInformation::SpellCooldown& new_cdr) { this->cdr_ = new_cdr; }


    // Pure Virtual
    virtual void castSpell(Character* player, Enemy* enemy) = 0;
};


#endif