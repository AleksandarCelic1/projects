#include "box.hpp"
#include "map.hpp"

Box::Box(BoxType new_type) : MapObjects() 
{
  if(new_type == BoxType::IRON_BIG_BOX) { setAnimationState(AnimationState::BOX_BIG_IRON);}
  else if(new_type == BoxType::IRON_MINI_BOX) { setAnimationState(AnimationState::BOX_SMALL_IRON);}
  else if(new_type == BoxType::WOOD_BIG_BOX) { setAnimationState(AnimationState::BOX_BIG_WOOD);}
  else if(new_type == BoxType::WOOD_MINI_BOX) { setAnimationState(AnimationState::BOX_SMALL_WOOD);}

  this->type_ = new_type;
  opened_ = false;
}

void Box::updateAnimation(float delta_time) 
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
      if(this->animation_state_ == AnimationState::BOX_BIG_IRON)
      {
        setAnimationState(AnimationState::BOX_BIG_IRON);
      }
      else if(this->animation_state_ == AnimationState::BOX_SMALL_IRON)
      {
        setAnimationState(AnimationState::BOX_SMALL_IRON);
      }
      else if(this->animation_state_ == AnimationState::BOX_BIG_WOOD)
      {
        setAnimationState(AnimationState::BOX_BIG_WOOD);
      }
      else if(this->animation_state_ == AnimationState::BOX_SMALL_WOOD)
      {
        setAnimationState(AnimationState::BOX_SMALL_WOOD);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void Box::dropLoot(Map* current_level_map)
{
  // Sutra ovo uradi imas upute na gpt kako se pravi dropRates
  float random_float = static_cast<float>(rand() % 100);
  std::cout << random_float << std::endl;

  if(this->type_ == BoxType::IRON_MINI_BOX || this->type_ == BoxType::WOOD_MINI_BOX)
  {
    if(random_float <= 25.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::HEALTH_POT);
    }
    else if(random_float <= 50.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::MUSHROOM);
    }
    else if(random_float <= 75.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::COIN);
    }
    else 
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::FLOOR_NEW_ONE);
    }
  }


  if(this->type_ == BoxType::IRON_BIG_BOX || this->type_ == BoxType::WOOD_BIG_BOX)
  {
    if(random_float <= 5.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::STONE_SWORD);
    }
    else if(random_float <= 25.0f)
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::RING_SAPPHIRE);
    }
    else 
    {
      current_level_map->getGrid()[this->y_][this->x_] = static_cast<int>(Grid::FLOOR_NEW_ONE);
    }
  }
}




