#include "mapObjects.hpp"
#include "../celaUtility.hpp"
#include "map.hpp"


MapObjects::MapObjects()
{
  this->animation_timer_ = 0.0f;
  this->current_frame_ = 0;
  this->is_animating_frame_ = false;
  this->total_frames_ = 0;
  this->frame_duration_ = 0.2f;
}

void MapObjects::setAnimationState(AnimationState new_state)
{
  this->animation_state_ = new_state;
  this->is_animating_frame_ = true;
  this->current_frame_ = 0;
  this->animation_timer_ = 0.0f;

  auto it = textures_for_animations.find(new_state);
  if (it != textures_for_animations.end())
  {
    this->total_frames_ = it->second.size();
  }
  else
  {
    this->total_frames_ = 0;
    std::cout << "Missing textures for animation state!\n";
  }
}