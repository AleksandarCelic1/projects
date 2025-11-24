#ifndef STONESWORD_HPP
#define STONESWORD_HPP

#include "sword.hpp"
class Armor;
class Inventory;



class StoneSword : public Sword
{
  public:
    StoneSword();
    StoneSword(const StoneSword& copy) = delete;
    ~StoneSword() = default;
};

#endif