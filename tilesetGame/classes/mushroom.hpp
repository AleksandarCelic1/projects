#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include "item.hpp"

class Mushroom : virtual public Item
{
  public:
    Mushroom();
    Mushroom(const Mushroom& copy) = delete;
    ~Mushroom() = default;

    void use(Character* player) override;
};

#endif