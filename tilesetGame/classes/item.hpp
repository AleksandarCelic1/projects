#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL.h>
#include "character.hpp"
#include "../enums.hpp"

class Item
{
  protected:
    int sell_value_;
    int buy_value_;

  public:

    Item() = default;
    Item(const Item& copy) = delete;
    virtual ~Item();

    virtual void use(Character* player) = 0;
    void sell(Character* player);
    bool buy(Character* player);

};
#endif