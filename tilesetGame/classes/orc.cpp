#include "orc.hpp"
#include "map.hpp"
#include "../celaUtility.hpp"

Orc::Orc(OrcType type)
{
  this->base_damage_ = 1;
  this->base_health_ = 2; // 2

  this->target_x_ = -1;
  this->target_y_ = -1;
  this->cooldown_for_bfs_ = 5.0f;
  this->can_call_bfs_ = false;
  
  

  this->money_ = 0;
  this->which_attack_to_perform_ = 1;

  this->current_tile_tag_ = 0;
  this->previous_tile_tag_ = 0;

  this->looking_down_ = false;
  this->looking_left_= false;
  this->looking_right_ = true;
  this->looking_up_ = false;

  this->animation_state_ = AnimationState::ORC_IDLE;
  this->can_attack_ = true;
  this->can_move_ = true;

  this->animation_timer_ = 0.0f;
  this->current_frame_ = 0;
  this->is_animating_frame_ = true;
  this->total_frames_ = static_cast<int>(AnimationsSize::AMOUNT_OF_ORC_IDLE_FRAMES);
  this->frame_duration_ = 0.1f;

  this->time_since_last_attack_ = 0.0f;
  this->attack_cooldown_ = 2.0f;

  this->x_axis_ = 0.0f;
  this->y_axis_ = 0.0f;
  this->target_x_axis = 0.0f;
  this->target_y_axis = 0.0f;

  this->is_dead_ = false;;
  this->ready_to_be_removed_ = false;
  this->death_timer_ = 0.0f;

  if(type == OrcType::PLATED) 
  { 
    this->base_damage_ *= SCALING_FACTOR_TWO;
    this->base_health_ *= SCALING_FACTOR_TWO; 
    this->animation_state_ = AnimationState::ORC_PLATED_IDLE;
  }
  else if(type == OrcType::ELITE) 
  { 
    this->base_damage_ *= SCALING_FACTOR_FOUR; 
    this->base_health_ *= SCALING_FACTOR_FOUR; 
    this->animation_state_ = AnimationState::ORC_ELITE_IDLE;
  }

  this->current_damage_ = base_damage_;
  this->current_health_ = base_health_;

  this->type_ = type;
}

void Orc::updateBFSCooldown(float& delta_time) noexcept
{
  if(!can_call_bfs_)
  {
    time_since_last_bfs_ += delta_time;

    if(time_since_last_bfs_ >= cooldown_for_bfs_)
    {
      this->can_call_bfs_ = true;
      time_since_last_bfs_ = 0.0f;
    }
  }
}

void Orc::handleAttackAnimationLogicForEliteOrcs()
{
  if(this->which_attack_to_perform_ == static_cast<int>(AttackVariationEliteOrcs::BASIC))
  {
    setAnimationState(AnimationState::ORC_ELITE_FIRST_ATTACK);
  }
  else if(this->which_attack_to_perform_ == static_cast<int>(AttackVariationEliteOrcs::WHIRLWIND))
  {
    setAnimationState(AnimationState::ORC_ELITE_SECOND_ATTACK);
  }
  else if(this->which_attack_to_perform_ == static_cast<int>(AttackVariationEliteOrcs::SMASH))
  {
    setAnimationState(AnimationState::ORC_ELITE_THIRD_ATTACK);
  }



  this->which_attack_to_perform_++;

  if(this->which_attack_to_perform_ > MAX_AMOUNT_OF_ATTACK_VARIATIONS)
  {
    this->which_attack_to_perform_ = static_cast<int>(AttackVariationEliteOrcs::BASIC);
  }
}

void Orc::updateAttackCooldown(float& delta_time) noexcept
{
  if(!can_attack_)
  {
    time_since_last_attack_ += delta_time;

    if(time_since_last_attack_ >= attack_cooldown_)
    {
      this->can_attack_ = true;
      time_since_last_attack_ = 0.0f;
    }
  }
}


void Orc::ability(Game* game) 
{
  // will make lifesteal later
} 

Orc::~Orc()
{
  // check out whats there to destruct
}

void Orc::detectEnemies(Map* current_level_map) noexcept
{
  int current_x_cord = this->getXcoordinate();
  int current_y_cord = this->getYcoordinate();


  int width_of_current_level = current_level_map->getGrid()[0].size();
  int height_of_current_level = current_level_map->getGrid().size();

  if(width_of_current_level <= 0 || height_of_current_level <= 0)
  {
    return;
  } 

  int tile_tag = 0;
  for(int index = current_y_cord - ENEMY_SENSOR_RADIUS; index <= current_y_cord + ENEMY_SENSOR_RADIUS; index++)
  {
    for(int inner = current_x_cord - ENEMY_SENSOR_RADIUS; inner <= current_x_cord + ENEMY_SENSOR_RADIUS; inner++)
    {
      try
      {
        tile_tag = current_level_map->getGrid().at(index).at(inner);
        if(tile_tag == 3)
        {
          this->target_locked_ = true;
          std::pair<int,int> player_coords = {inner, index};
          this->player_spotted_at_ = player_coords;
        }
      }
      catch(std::out_of_range){ }
    }
  }
}

void Orc::moveOrcAcrossMapUsingActualPath(Tools* main_tool, Map* current_level_map, float delta_time) noexcept
{
  if(actual_path_.empty()) { return;}

  if(!this->canMove()) { return; }


  
  if(this->type_ == OrcType::CLASSIC) {this->setAnimationState(AnimationState::ORC_WALKING);}
  else if(this->type_ == OrcType::PLATED) { this->setAnimationState(AnimationState::ORC_PLATED_WALK);}
  else if(this->type_ == OrcType::ELITE) { this->setAnimationState(AnimationState::ORC_ELITE_WALK);}

  Detection detect = Detection::NOTHING_DETECTED;
    
    

  this->enemyInRange(current_level_map, detect);
  if(detect != Detection::NOTHING_DETECTED) { this->actual_path_.clear(); return;}

  int new_x = this->actual_path_[0].first;
  int new_y = this->actual_path_[0].second;

  int reservation_x = -1;
  int reservation_y = -1;

  try
  {
    if(this->actual_path_.size() == 1)
    {
      reservation_x = this->actual_path_.at(0).first;
      reservation_y = this->actual_path_.at(0).second;
      this->target_x_ = reservation_x;
      this->target_y_ = reservation_y;
    }
    else
    {
      this->actual_path_.at(1);
      reservation_x = this->actual_path_.at(1).first;
      reservation_y = this->actual_path_.at(1).second;
      this->target_x_ = reservation_x;
      this->target_y_ = reservation_y;
    }
      
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
    
  // NE DIRAJ RADI NEKAKO KAKO NE ZNAM

  int old_x = this->getXcoordinate();
  int old_y = this->getYcoordinate();

  if(old_x == new_x && old_y == new_y) 
  {
    actual_path_.erase(actual_path_.begin());
    return;
  }

  Movement direction;
  int tile_tag = current_level_map->getGrid()[new_y][new_x];
    

  if(old_x < new_x) { direction = Movement::RIGHT; setLookingDirection(Movement::RIGHT);}
  else if(old_x > new_x) { direction = Movement::LEFT; setLookingDirection(Movement::LEFT);}
  else if(old_y < new_y) { direction = Movement::DOWNWARDS; setLookingDirection(Movement::DOWNWARDS);}
  else if(old_y > new_y) { direction = Movement::UPWARDS; setLookingDirection(Movement::UPWARDS);}

  if(this->getCurrentTileTag() != 0 && 
  (this->getCurrentTileTag() < static_cast<int>(Grid::FLOOR_NEW_ONE) 
  || this->getCurrentTileTag() > static_cast<int>(Grid::FLOOR_NEW_THREE)))
  {
    this->setCurrentTileTag(static_cast<int>(Grid::FLOOR));
  }

  current_level_map->getGrid()[old_y][old_x] = this->current_tile_tag_;


  if(tile_tag != 0 && (tile_tag < static_cast<int>(Grid::FLOOR_NEW_ONE) || tile_tag > static_cast<int>(Grid::FLOOR_NEW_THREE))) { tile_tag = 0;}
  this->setPreviousTileTag(this->getCurrentTileTag());
  this->setCurrentTileTag(tile_tag);





  calculateTargetCoordsForLerp(main_tool, direction, delta_time);
  actual_path_.erase(actual_path_.begin());
  
}



