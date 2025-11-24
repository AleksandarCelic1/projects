#ifndef NEEDLES_HPP
#define NEEDLES_HPP

#include "mapObjects.hpp"
#include "soldier.hpp"

class Needles : virtual public MapObjects
{
  private:
    int needle_damage_;
  public:
    Needles();
    Needles(const Needles& copy) = delete;
    ~Needles() = default;

    void updateAnimation(float delta_time) override;
    void handleNeedlesLogic(Soldier* player) noexcept;
};

#endif