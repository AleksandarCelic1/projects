#ifndef CHEST_HPP
#define CHEST_HPP

#include "mapObjects.hpp"

class Map;

enum class ChestType
{
  MINI_CHEST,
  MINI_CHEST_OPENING,
  BIG_CHEST,
  BIG_CHEST_OPENING
};


class Chest : virtual public MapObjects
{
  private:
    ChestType type_;
    bool opened_;
  
  public:
    Chest() = default;
    Chest(ChestType new_type);
    Chest(const Chest& copy) = delete;
    ~Chest() = default;

    ChestType getType() const { return this->type_;}
    bool isChestOpened() const { return this->opened_;}

    void setChestOpenStatus(bool x) { this->opened_ = x;}
    void setType(ChestType new_type) { this->type_ = new_type;}

    void dropLoot(Map* current_level_map);



    void updateAnimation(float delta_time) override;
};

#endif