#include "../include_/animation_utils.hpp"

void AnimationUtils::setTimePassed(AnimationInfo* info, float time) noexcept
{
  if(info->time_passed_ >= info->animation_delay_)
  {
    return;
  }

  info->time_passed_ += time;
}

void AnimationUtils::updateAnimation(AnimationInfo* info, size_t animation_index) noexcept
{
  /*
    You need to figure out how to update the animation index for each animation 
    withough index going out of bounds, this is somewhat doable with SDL_QueryTexture 
    to get its dimensions on runtime then dividing the width with 64 (one frame width)
    and then we get max index for the current animation since not all have a fixed 
    number of frames <!> 
  */
}