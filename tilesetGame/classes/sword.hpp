#ifndef SWORD_HPP
#define SWORD_HPP

#include "item.hpp"
class Armor;
class Inventory;

class Sword : virtual public Item
{
  protected:
    bool equiped_;
    int attack_power_boost_;
  public:
    Sword();
    Sword(const Sword& copy) = delete;
    ~Sword() = default;

    bool getEquiped() const { return this->equiped_;}
    int getAPBoost() const { return this->attack_power_boost_;}

    void setEquiped(bool x) {this->equiped_ = x;}

    void use(Character* player) override;
};

#endif