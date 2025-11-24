#include "character.hpp"
#include "../celaUtility.hpp"
#include "map.hpp"
#include "game.hpp"

void Character::setLookingDirection(Movement direction) noexcept
{
  switch (direction)
  {
  case Movement::UPWARDS:
    this->looking_up_ = true;
    this->looking_down_ = false;
    this->looking_right_ = false;
    this->looking_left_ = false;
    break;
  case Movement::DOWNWARDS:
    this->looking_up_ = false;
    this->looking_down_ = true;
    this->looking_right_ = false;
    this->looking_left_ = false;
    break;
  case Movement::LEFT:
    this->looking_up_ = false;
    this->looking_down_ = false;
    this->looking_right_ = false;
    this->looking_left_ = true;
    break;
  case Movement::RIGHT:
    this->looking_up_ = false;
    this->looking_down_ = false;
    this->looking_right_ = true;
    this->looking_left_ = false;
    break;
  default:
    break;
  }
}

void Character::enemyInRange(Map* current_level, Detection& direction_where_orc)
{
  if(this->getXcoordinate() - 1 >= 0)
  {
    if(current_level->getGrid()[this->getYcoordinate()][this->getXcoordinate() - 1] == 4
    || current_level->getGrid()[this->getYcoordinate()][this->getXcoordinate() - 1] == 3)
    {
      direction_where_orc = Detection::DETECTED_LEFT;
      return;
    }
  }
  
  if(this->getXcoordinate() + 1 < current_level->getGrid()[this->getYcoordinate()].size()) // was X 
  {
    if(current_level->getGrid()[this->getYcoordinate()][this->getXcoordinate() + 1] == 4
    || current_level->getGrid()[this->getYcoordinate()][this->getXcoordinate() + 1] == 3)
    {
      direction_where_orc =  Detection::DETECTED_RIGHT;
      return;
    }
  }
  
  if(this->getYcoordinate() - 1 >= 0)
  {
    if(current_level->getGrid()[this->getYcoordinate() - 1][this->getXcoordinate()] == 4
    || current_level->getGrid()[this->getYcoordinate() - 1][this->getXcoordinate()] == 3)
    {
      direction_where_orc = Detection::DETECTED_UP;
      return;
    }
  }
  
  if(this->getYcoordinate() + 1 < current_level->getGrid().size())
  {
    if(current_level->getGrid()[this->getYcoordinate() + 1][this->getXcoordinate()] == 4
    || current_level->getGrid()[this->getYcoordinate() + 1][this->getXcoordinate()] == 3)
    {
      direction_where_orc = Detection::DETECTED_DOWN;
      return;
    }
  }


  return;
}

void Character::setAnimationState(AnimationState new_state) noexcept
{
  if(this->animation_state_ != new_state)
  {
    this->animation_state_ = new_state;
    this->is_animating_frame_ = true;
    this->current_frame_ = 0; // look into this its a map not an array 
    this->animation_timer_ = 0.0f;

    this->total_frames_ = textures_for_animations[this->animation_state_].size();
  }
}

Detection Character::getLookingDireciton() noexcept
{
  if (this->isLookingLeft())
  {
    return Detection::DETECTED_LEFT;
  }
  else if (this->isLookingRight())
  {
    return Detection::DETECTED_RIGHT;
  }
  if (this->isLookingUp())
  {
    return Detection::DETECTED_UP;
  }
  if (this->isLookingDown())
  {
    return Detection::DETECTED_DOWN;
  }

  return Detection::NOTHING_DETECTED;
}

bool Character::isDeathAnimationFinished() 
{
  Orc* placeholder = dynamic_cast<Orc*>(this);
  if(placeholder == nullptr) { return false; }

  if(placeholder->getAnimationState() != AnimationState::ORC_DEATH && placeholder->getAnimationState() != AnimationState::ORC_PLATED_DEATH
  && placeholder->getAnimationState() != AnimationState::SOLDIER_DEATH && placeholder->getAnimationState() != AnimationState::ORC_ELITE_DEATH) return false;

  int total_frames = placeholder->total_frames_;

  if(total_frames <= 0)
  {
    return false;
  }

  if(placeholder->getCurrentFrame() >= total_frames - 1 && placeholder->isFullyDead())
  {
    return true;
  }

  return false;
}

void Character::updateAnimation(float delta_time) noexcept
{
  if(this->is_animating_frame_ == false) 
  {
    return;
  }

  this->animation_timer_ += delta_time;
  if(animation_timer_ >= frame_duration_)
  {
    animation_timer_ -= frame_duration_;
    current_frame_++;

    if(current_frame_ >= total_frames_)
    {
      if( this->animation_state_ == AnimationState::SOLDIER_IDLE || this->animation_state_ == AnimationState::ORC_IDLE
        || this->animation_state_ == AnimationState::ORC_PLATED_IDLE || this->animation_state_ == AnimationState::ORC_ELITE_IDLE)
      {
        this->current_frame_ = 0;
      }
      else if(this->animation_state_ == AnimationState::SOLDIER_ATTACK)
      {
        setAnimationState(AnimationState::SOLDIER_IDLE);
        this->can_attack_ = true;
      }
      else if(this->animation_state_ == AnimationState::SOLDIER_WALKING)
      {
        this->can_move_ = true;
        setAnimationState(AnimationState::SOLDIER_IDLE);
      }
      else if(this->animation_state_ == AnimationState::SOLDIER_HURT)
      {
        setAnimationState(AnimationState::SOLDIER_IDLE);
      }
      else if(this->animation_state_ == AnimationState::SOLDIER_SPECIAL_ABILITY)
      {
        // probaly need cooldown so check it!
        setAnimationState(AnimationState::SOLDIER_IDLE);
      }
      else if(this->animation_state_ == AnimationState::ORC_PLATED_WALK || this->animation_state_ == AnimationState::ORC_PLATED_ATTACK
      || this->animation_state_ == AnimationState::ORC_PLATED_HURT)
      {
        setAnimationState(AnimationState::ORC_PLATED_IDLE);
      }
      else if(this->animation_state_ == AnimationState::ORC_ELITE_WALK || this->animation_state_ == AnimationState::ORC_ELITE_HURT
      || this->animation_state_ == AnimationState::ORC_ELITE_FIRST_ATTACK || this->animation_state_ == AnimationState::ORC_ELITE_SECOND_ATTACK
      || this->animation_state_ == AnimationState::ORC_ELITE_THIRD_ATTACK )
      {
        setAnimationState(AnimationState::ORC_ELITE_IDLE);
      }
      else if(this->animation_state_ == AnimationState::ORC_ATTACKING
      || this->animation_state_ == AnimationState::ORC_HURT)
      {
        setAnimationState(AnimationState::ORC_IDLE);
      }
      else if(this->animation_state_ == AnimationState::ORC_WALKING)
      {
        setAnimationState(AnimationState::ORC_IDLE);
      }
      else if(this->animation_state_ == AnimationState::ORC_DEATH
      || this->animation_state_ == AnimationState::ORC_PLATED_DEATH
      || this->animation_state_ == AnimationState::SOLDIER_DEATH
      || this->animation_state_ == AnimationState::ORC_ELITE_DEATH)
      {
        // Dead!
        //setAnimationState(AnimationState::ORC_IDLE);
        this->is_dead_ = true;
        this->ready_to_be_removed_ = false;
        this->is_animating_frame_ = false;
        this->death_timer_ = 0.0f;
        this->current_frame_ -= 1;
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void Character::updateDeathTimerCooldown(float& delta_time) noexcept
{
  if(this->is_dead_)
  {
    this->death_timer_ += delta_time;

    if(death_timer_ >= 1.0f) // Waiting 1 second on last frame
    {
      this->ready_to_be_removed_ = true;
    }
  }
}

void Character::calculateTargetCoordsForLerp(Tools* tool, Movement direction, float delta_time)
{

  Soldier* player = dynamic_cast<Soldier*>(tool->getGame()->getSoldier());
  Map* current_lvl_map = tool->getGame()->getMaps()[player->getCurrentLevel() - 1];
  int map_height = current_lvl_map->getGrid().size() * static_cast<int>(Grid::TILE_SIZE); // ovo ne trebamozes izbaciti tool!
  int map_width = current_lvl_map->getGrid()[0].size() * static_cast<int>(Grid::TILE_SIZE);

  int x_off_set = (tool->getScreenWidth() - map_width) / 2;
  int y_off_set = (tool->getScreenHeight() - map_height) / 2;

  

  const int tile = static_cast<int>(Grid::TILE_SIZE);

  int destination_x = 0;
  int destination_y = 0;

  if(direction == Movement::UPWARDS) { destination_y = -1;}
  else if(direction == Movement::DOWNWARDS) {destination_y = 1;}
  else if(direction == Movement::LEFT) { destination_x = -1;}
  else if(direction == Movement::RIGHT) { destination_x = 1;}

  int new_x = this->getXcoordinate() + destination_x;
  int new_y = this->getYcoordinate() + destination_y;

  this->setTargetXAxis(new_x * tile);
  this->setTargetYAxis(new_y * tile);
  this->setMovingStatus(false);
}

void Character::findCoordsLevelStart(Game* game) 
{
  Map* map_current = game->getMaps()[this->current_level_ - 1];
  
  for(int index = 0; index < map_current->getGrid().size(); index++)
  {
    for(int inner = 0; inner < map_current->getGrid()[0].size(); inner++)
    {
      if(map_current->getGrid()[index][inner] == 3)
      {
        this->x_ = inner;
        this->y_ = index;

        const int tile = static_cast<int>(Grid::TILE_SIZE);
        this->x_axis_ = inner * tile;
        this->y_axis_ = index * tile;
        
        this->target_x_axis = this->x_axis_;
        this->target_y_axis = this->y_axis_;
        break;
      }
    }
  }
}

float lerp(float A, float B, float T) // From point A to point B
{
  return A + (B - A) * T;
}

void Character::updateLerp(Tools* main_tools, Map* current_level, float delta_time)
{
  if(this->canMove()) { return;} // Meaning he can move, but its not MOVING!

  float time = 10.f * delta_time;
  if(time > 1.f) { time = 1.f;}

  x_axis_ = lerp(x_axis_, this->target_x_axis, time);
  y_axis_ = lerp(y_axis_, this->target_y_axis, time);
  
  if(std::fabs(x_axis_ - target_x_axis) < 0.1f && std::fabs(y_axis_ - target_y_axis) < 0.1f)
  {
    x_axis_ = target_x_axis;
    y_axis_ = target_y_axis;

    const int tile = static_cast<int>(Grid::TILE_SIZE);
    int tile_x = static_cast<int>(std::lround(x_axis_ / tile));
    int tile_y = static_cast<int>(std::lround(y_axis_ / tile));

    this->setXcoordinate(tile_x);
    this->setYcoordinate(tile_y);

    if(Soldier* placeholder = dynamic_cast<Soldier*>(this))
    {
      current_level->getGrid()[placeholder->y_][placeholder->x_] = static_cast<int>(Grid::CHARACTER_SOLD);
      std::vector<Character*>& current_level_enemies = main_tools->getGame()->getEnemiesOnLevel()[placeholder->getCurrentLevel() - 1];
      this->can_move_ = true;
      enemySensorChecker(placeholder ,current_level, current_level_enemies);
      
    }
    else if(Orc* placeholder = dynamic_cast<Orc*>(this))
    {
      current_level->getGrid()[placeholder->y_][placeholder->x_] = static_cast<int>(Grid::CHARACTER_ORC);
      placeholder->target_x_ = -1;
      placeholder->target_y_ = -1;
    }

    this->can_move_ = true;
  }
}
