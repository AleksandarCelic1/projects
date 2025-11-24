#include "banner.hpp"

Banner::Banner() : MapObjects() 
{
  setAnimationState(AnimationState::BANNER);
}

void Banner::updateAnimation(float delta_time)
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
      if(this->animation_state_ == AnimationState::BANNER)
      {
        setAnimationState(AnimationState::BANNER);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}