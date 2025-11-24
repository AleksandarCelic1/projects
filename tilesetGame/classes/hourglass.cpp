#include "hourglass.hpp"
#include "../celaUtility.hpp"

Hourglass::Hourglass()
{
  this->animation_timer_ = 0.0f;
  this->current_frame_ = 0;
  this->is_animating_frame_ = false;
  this->total_frames_ = 0;
  this->frame_duration_ = 0.2f;

  this->should_rotate_ = false;
  setAnimationState(AnimationState::HOURGLASS_ROTATING);
}

void Hourglass::setAnimationState(AnimationState new_state)
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

void Hourglass::renderHourglass(Tools* main_tools) noexcept
{
  int screen_width = main_tools->getScreenWidth();
  int screen_height = main_tools->getScreenHeight();

  SDL_Rect hourglass_rect;

  hourglass_rect.w = static_cast<int>(AnimationsSize::HOURGLASS_BOTH) * SCALING_FACTOR_FOUR;
  hourglass_rect.h = static_cast<int>(AnimationsSize::HOURGLASS_BOTH) * SCALING_FACTOR_FOUR;


  hourglass_rect.x = hourglass_rect.w;
  hourglass_rect.y = screen_height - ( 2 * hourglass_rect.h);

  if(!should_rotate_) 
  { 
    SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_animations[this->animation_state_][26], nullptr, &hourglass_rect);
    return; 
  }
  else
  {
    SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_animations[this->animation_state_][this->current_frame_], nullptr, &hourglass_rect);
  }
}

void Hourglass::updateAnimation(float delta_time) noexcept
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
      if(this->animation_state_ == AnimationState::HOURGLASS_ROTATING)
      {
        this->should_rotate_ = false;
        // Constant Moving Animation !
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}