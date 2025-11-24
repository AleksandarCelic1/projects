#ifndef POTION_HPP
#define POTION_HPP

#include "item.hpp"

class Potion : virtual public Item
{
  public:
    Potion();
    Potion(const Potion& copy) = delete;
    ~Potion() = default;

    void use(Character* player) override;
};

#endif