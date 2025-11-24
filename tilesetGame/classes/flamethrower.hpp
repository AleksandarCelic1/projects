#ifndef FLAMETHROWER_HPP
#define FLAMETHROWER_HPP

#include "mapObjects.hpp"
#include "soldier.hpp"

enum class FlamethrowerType
{
  VERTICAL,
  HORIZONTAL
};

class Flamethrower : virtual public MapObjects
{
  private:
    FlamethrowerType type_;
    int flame_damage_;

  public:
    Flamethrower() = default;
    Flamethrower(FlamethrowerType type);
    Flamethrower(const Flamethrower& copy) = delete;
    ~Flamethrower() = default;

    void updateAnimation(float delta_time) override;

    FlamethrowerType getType() const { return this->type_;}
    void setType(FlamethrowerType type) { this->type_ = type;}


    void handleFlameThrowerLogic(Soldier* player) noexcept;
};

#endif