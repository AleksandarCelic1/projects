#include "torch.hpp"

Torch::Torch(TorchType x) : MapObjects()
{ 
  if(x == TorchType::HORIZONTAL_TORCH) { setAnimationState(AnimationState::TORCHES_FLAME_HORIZONTAL_WALL);}
  else if ( x == TorchType::VERTICAL_TORCH) { setAnimationState(AnimationState::TORCHES_VERTICAL_WALL);}
  else if( x == TorchType::VERTICAL_TORCH_INVERTED) { setAnimationState(AnimationState::TORCHES_VERTICAL_WALL);}

  type_ = x;
}

void Torch::updateAnimation(float delta_time) 
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
      if(this->animation_state_ == AnimationState::TORCHES_FLAME_HORIZONTAL_WALL)
      {
        setAnimationState(AnimationState::TORCHES_FLAME_HORIZONTAL_WALL);
      }
      else if(this->animation_state_ == AnimationState::TORCHES_VERTICAL_WALL)
      {
        setAnimationState(AnimationState::TORCHES_VERTICAL_WALL);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}