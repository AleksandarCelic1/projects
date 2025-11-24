#ifndef GOLDSWORD_HPP
#define GOLDSWORD_HPP

#include "sword.hpp"
class Armor;
class Inventory;



class GoldSword : public Sword
{
  public:
    GoldSword();
    GoldSword(const GoldSword& copy) = delete;
    ~GoldSword() = default;
};

#endif