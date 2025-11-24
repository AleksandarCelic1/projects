#ifndef RING_HPP
#define RING_HPP

#include "item.hpp"
class Inventory;
class Armor;

class Ring : virtual public Item
{
  protected:
    bool equiped_;
    int health_points_increase_;
  public:
    Ring();
    Ring(const Ring& copy) = delete;
    ~Ring() = default;

    void use(Character* player) override; // Ovo ce se implementirati kad budem napravio ARMORY!
};

#endif