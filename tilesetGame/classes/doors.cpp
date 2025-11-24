#include "doors.hpp"
#include "map.hpp"

Doors::Doors(int current_level, DoorType type) : MapObjects()
{
  if(current_level > 0)
  {
    can_be_opened_ = false;
  }
  else
  {
    can_be_opened_ = true;
  }

  this->type_ = type;
}


void Doors::updateAnimation(float delta_time) 
{
  // Currently there is no animation!
}

void Doors::useDoors(Map* current_level_map, Soldier* player) noexcept
{
  int amount_of_gold_keys = player->getAmountOfGoldKeys();
  int amount_of_silver_keys = player->getAmountOfSilverKeys();

  if(can_be_opened_)
  {
    if(this->type_ == DoorType::VERTICAL) {current_level_map->getGrid()[this->y_][this->x_] = 0;}
    else if(this->type_ == DoorType::HORIZONTAL_LEFT) { current_level_map->getGrid()[this->y_][this->x_] = 0; current_level_map->getGrid()[this->y_][this->x_ + 1] = 0;}
    else if(this->type_ == DoorType::HORIZONTAL_RIGHT) { current_level_map->getGrid()[this->y_][this->x_] = 0; current_level_map->getGrid()[this->y_][this->x_ - 1] = 0;}
  }
  else if (!can_be_opened_)
  {
    if(this->type_ == DoorType::VERTICAL)
    {
      if(amount_of_silver_keys > 0) 
      {
        player->setAmountOfSilverKeys(amount_of_silver_keys - 1);
        can_be_opened_ = true;
      }
    }
    else if(this->type_ == DoorType::HORIZONTAL_LEFT || this->type_ == DoorType::HORIZONTAL_RIGHT)
    {
      if(amount_of_gold_keys > 0)
      {
        player->setAmountOfGoldKeys(amount_of_gold_keys - 1);
        can_be_opened_ = true;
      }
    }

    // Find a key in inventory but thats for later development
  }
}