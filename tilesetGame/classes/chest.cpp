#include "chest.hpp"
#include "map.hpp"


Chest::Chest(ChestType new_type) : MapObjects() 
{
  if(new_type == ChestType::BIG_CHEST) { setAnimationState(AnimationState::CHEST_BIG_ANIM); this->type_ = new_type;}
  else if(new_type == ChestType::MINI_CHEST) { setAnimationState(AnimationState::CHEST_MINI_ANIM); this->type_ = new_type;}

  this->opened_ = false;
}

void Chest::updateAnimation(float delta_time) 
{
  if(this->is_animating_frame_ == false) 
  {
    return;
  }

  this->animation_timer_ += delta_time;
  if(animation_timer_ >= frame_duration_)
  {
    animation_timer_ = 0.0f;
    current_frame_++;

    if(current_frame_ >= total_frames_)
    {
      if(this->animation_state_ == AnimationState::CHEST_BIG_ANIM)
      {
        setAnimationState(AnimationState::CHEST_BIG_ANIM);
      }
      else if(this->animation_state_ == AnimationState::CHEST_MINI_ANIM)
      {
        setAnimationState(AnimationState::CHEST_MINI_ANIM);
      }
      else if(this->animation_state_ == AnimationState::CHEST_MINI_OPENING)
      {
        // logic here!
        this->opened_ = true;
        this->type_ = ChestType::MINI_CHEST_OPENING;
        this->is_animating_frame_ = false;
      }
      else if(this->animation_state_ == AnimationState::CHEST_BIG_OPENINIG)
      {
        // logic here!
        this->opened_ = true;
        this->type_ = ChestType::BIG_CHEST_OPENING;
        this->is_animating_frame_ = false;
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void Chest::dropLoot(Map* current_level_map)
{
  float random_float = static_cast<float>(rand() % 100);

  if(this->type_ == ChestType::BIG_CHEST_OPENING)
  {
    if(random_float <= 15.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::BIG_GOLD_SWORD);
    }
    else if(random_float <= 20.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::GOLD_SWORD);
    }
    else if(random_float <= 75.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::STONE_SWORD);
    }
    else
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::FLOOR_NEW_ONE);
    }
  }

  if(this->type_ == ChestType::MINI_CHEST_OPENING)
  {
    if(random_float <= 5.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::RING_SAPPHIRE_GOLD);
    }
    else if(random_float <= 25.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::RING_SAPPHIRE);
    }
    else if(random_float <= 75.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::RING_RUBY);
    }
    else
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::FLOOR_NEW_ONE);
    }
  }
}