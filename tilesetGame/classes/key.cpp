#include "key.hpp"

Key::Key(KeyType new_type) : MapObjects() 
{
  if(new_type == KeyType::SILVER_KEY) { setAnimationState(AnimationState::SILVER_KEY);}
  else if ( new_type == KeyType::GOLD_KEY) { setAnimationState(AnimationState::GOLD_KEY);}

  this->type_ = new_type;
}

void Key::updateAnimation(float delta_time) 
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
      if(this->animation_state_ == AnimationState::SILVER_KEY)
      {
        setAnimationState(AnimationState::SILVER_KEY);
      }
      else if(this->animation_state_ == AnimationState::GOLD_KEY)
      {
        setAnimationState(AnimationState::GOLD_KEY);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
  
}