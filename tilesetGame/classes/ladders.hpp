#ifndef LADDERS_HPP
#define LADDERS_HPP

#include "mapObjects.hpp"

class Game;
class Soldier;

class Ladder : virtual public MapObjects
{
  public:
    Ladder() = default;
    Ladder(const Ladder& copy) = delete;
    ~Ladder() = default;

    void updateAnimation(float delta_time) override;
    void use(Game* player) noexcept;
};


#endif