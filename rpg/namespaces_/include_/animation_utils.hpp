#ifndef ANIMATION_UTILS_HPP
#define ANIMATION_UTILS_HPP

#include "../../structs_/structs.hpp"

namespace AnimationUtils
{
  void setTimePassed(AnimationInfo* info, float time) noexcept;
  void updateAnimation(AnimationInfo* info, size_t animation_index) noexcept; 
}


#endif