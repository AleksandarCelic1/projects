#ifndef ARROWTRAP_HPP
#define ARROWTRAP_HPP


#include "mapObjects.hpp"
#include "soldier.hpp"


class ArrowTrap : virtual public MapObjects
{
  private:
    int arrow_damage_;

  public:
    ArrowTrap();
    ArrowTrap(const ArrowTrap& copy) = delete;
    ~ArrowTrap() = default;

    void updateAnimation(float delta_time) override;
    void handleArrowTrapLogic(Soldier* player) noexcept;
};

#endif