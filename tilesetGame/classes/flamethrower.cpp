#include "flamethrower.hpp"

Flamethrower::Flamethrower(FlamethrowerType type) : MapObjects() 
{
  this->type_ = type;
  this->flame_damage_ = 1;
  this->frame_duration_ = 0.4f;

  if(type == FlamethrowerType::VERTICAL) { setAnimationState(AnimationState::VERTICAL_FLAMETHROWER);}
  else if(type == FlamethrowerType::HORIZONTAL) { setAnimationState(AnimationState::HORIZONTAL_FLAMETHROWER);}
}


void Flamethrower::updateAnimation(float delta_time)
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
      if(this->animation_state_ == AnimationState::VERTICAL_FLAMETHROWER)
      {
        setAnimationState(AnimationState::VERTICAL_FLAMETHROWER);
      }
      else if(this->animation_state_ == AnimationState::HORIZONTAL_FLAMETHROWER)
      {
        setAnimationState(AnimationState::HORIZONTAL_FLAMETHROWER);
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void Flamethrower::handleFlameThrowerLogic(Soldier* player) noexcept
{
  int player_x = player->getXcoordinate();
  int player_y = player->getYcoordinate();



  if(this->type_ == FlamethrowerType::VERTICAL)
  {
    if(this->x_ == player_x && this->y_ + 1 == player_y && this->current_frame_ == 1) // second frame biggest fire!
    {
      if(player->getAnimationState() == AnimationState::SOLDIER_IDLE)
      {
        player->setCurrentHealth(player->getCurrentHealth() - this->flame_damage_);
        
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
  else if( this->type_ == FlamethrowerType::HORIZONTAL)
  {
    if((this->x_ + 1 == player_x || this->x_ == player_x) && this->y_ == player_y && this->current_frame_ == 1) // second frame biggest fire!
    {
      if(player->getAnimationState() == AnimationState::SOLDIER_IDLE)
      {
        player->setCurrentHealth(player->getCurrentHealth() - this->flame_damage_);

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
}




