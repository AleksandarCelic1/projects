#include "arrowtrap.hpp"

ArrowTrap::ArrowTrap() : MapObjects() 
{
  this->arrow_damage_ = 1;
  this->frame_duration_ = 0.4f;
  setAnimationState(AnimationState::ARROW_TRAP_ANIMATION);

}


void ArrowTrap::updateAnimation(float delta_time)
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
      if(this->animation_state_ == AnimationState::ARROW_TRAP_ANIMATION)
      {
        setAnimationState(AnimationState::ARROW_TRAP_ANIMATION);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void ArrowTrap::handleArrowTrapLogic(Soldier* player) noexcept
{
  int player_x = player->getXcoordinate();
  int player_y = player->getYcoordinate();

  if(this->x_ == player_x && this->y_ + 1 == player_y && this->current_frame_ == 3) // second frame biggest fire!
  {
    if(player->getAnimationState() == AnimationState::SOLDIER_IDLE)
    {
      player->setCurrentHealth(player->getCurrentHealth() - this->arrow_damage_);
      if(player->getCurrentHealth() <= 0)
      {
        player->setAnimationState(AnimationState::SOLDIER_DEATH);
      }
      else
      {
        player->setAnimationState(AnimationState::SOLDIER_HURT);
      } 
    }
  }
}




