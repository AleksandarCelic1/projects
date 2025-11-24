#ifndef DOORS_HPP
#define DOORS_HPP

#include "mapObjects.hpp"
#include "soldier.hpp"

class Map;


enum class DoorType
{
  VERTICAL,
  HORIZONTAL_LEFT,
  HORIZONTAL_RIGHT
};

class Doors : virtual public MapObjects
{
  private:
    bool can_be_opened_;
    DoorType type_;

  public:
    Doors() = default;
    Doors(int current_level, DoorType type);
    Doors(const Doors& copy) = delete;
    ~Doors() = default;

    DoorType getType() const { return this->type_;}
    void setType(DoorType type) { this->type_ = type;}

    void updateAnimation(float delta_time) override;

    void useDoors(Map* current_level_map, Soldier* player) noexcept;

};


#endif