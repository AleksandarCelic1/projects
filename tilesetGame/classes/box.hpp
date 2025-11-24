#ifndef BOX_HPP
#define BOX_HPP

#include "mapObjects.hpp"


enum class BoxType
{
  WOOD_MINI_BOX,
  WOOD_BIG_BOX,
  IRON_MINI_BOX,
  IRON_BIG_BOX
};

class Map;


class Box : virtual public MapObjects
{
  private:
    BoxType type_;
    bool opened_;

  public:
    Box() = default;
    Box(BoxType new_type);
    Box(const Box& copy) = delete;
    ~Box() = default;

    void updateAnimation(float delta_time) override;
    void dropLoot(Map* current_level_map);

    BoxType getType() const { return this->type_;}
    bool getOpenedStatus() const { return this->opened_;}

    void setOpenStatus(bool x) { this->opened_ = x;}
    void setType(BoxType new_type) { this->type_ = new_type;}

};


#endif