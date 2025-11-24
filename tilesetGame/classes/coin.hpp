#ifndef COIN_HPP
#define COIN_HPP

#include "item.hpp"

class Coin : virtual public Item
{
  public:
    Coin();
    Coin(const Coin& copy) = delete;
    ~Coin() = default;
    
    void use(Character* player) override;
};

#endif