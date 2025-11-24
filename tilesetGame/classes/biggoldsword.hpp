#ifndef BIGGOLDSWORD_HPP
#define BIGGOLDSWORD_HPP

#include "sword.hpp"
class Armor;
class Inventory;



class BigGoldSword : public Sword
{
  public:
    BigGoldSword();
    BigGoldSword(const BigGoldSword& copy) = delete;
    ~BigGoldSword() = default;
};

#endif