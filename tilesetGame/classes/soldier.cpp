#include "soldier.hpp"
#include "../celaUtility.hpp"
#include "../gameFunctions.hpp"

Soldier::Soldier()
{
  this->special_ability_hourglass_cooldown_ = new Hourglass();
  this->base_damage_ = 1;
  this->base_health_ = 5;
  this->current_damage_ = base_damage_;
  this->current_health_ = base_health_; 
  this->animation_state_ = AnimationState::SOLDIER_IDLE;
  this->can_attack_ = true;
  this->can_move_ = true;

  this->animation_timer_ = 0.0f;
  this->current_frame_ = 0;
  this->is_animating_frame_ = true;
  this->total_frames_ = static_cast<int>(AnimationsSize::AMOUNT_OF_SOLDIER_IDLE_FRAMES);
  this->frame_duration_ = 0.1f;

  this->money_ = 10;
  this->amount_of_gold_keys_ = 0;
  this->amount_of_silver_keys_ = 0;


  this->looking_down_ = false;
  this->looking_left_= false;
  this->looking_right_ = true;

  this->ability_damage_ = ABILITY_DAMAGE_AND_HP_RESTORATION;
  this->ability_hp_restoration_ = ABILITY_DAMAGE_AND_HP_RESTORATION;
  this->can_use_special_ability_ = true;


  this->x_axis_ = 0;
  this->y_axis_ = 0;
  this->target_x_axis = 0;
  this->target_y_axis = 0;

  this->items_ = nullptr;
  this->armor_ = new Armor();

  this->looking_up_ = false;
  this->is_in_shop_ = false;

  this->is_dead_ = false;;
  this->ready_to_be_removed_ = false;
  this->death_timer_ = 0.0f;

  this->current_level_ = 1;
  this->last_level_visited_ = current_level_;
  this->idle_zone_index_ = static_cast<int>(Ranges::LEVELS);

  // see what to do with sld text rect and other stuff
}


void Soldier::ability(Game* game) 
{
  // New logic hourglas Cooldown
  if(this->special_ability_hourglass_cooldown_->isRotating()) { return; }
  else 
  {
    this->special_ability_hourglass_cooldown_->setRotatingStatus(true);
    this->special_ability_hourglass_cooldown_->setAnimationState(AnimationState::HOURGLASS_ROTATING);
  }


  Map* current_level_map = game->getMaps()[this->current_level_ - 1];
  std::vector<Character*>& orcs_current_level = game->getEnemiesOnLevel()[this->current_level_ - 1];
  int tag = -1;

  this->setAnimationState(AnimationState::SOLDIER_SPECIAL_ABILITY);

  this->setCurrentHealth(this->getCurrentHealth() + this->ability_hp_restoration_);
  if(this->getCurrentHealth() > this->getBaseHealth()) { this->setCurrentHealth(this->getBaseHealth());}
  

  int x_range = this->x_;
  int y_range = this->y_;

  for(int index = this->y_ - SOLDIER_SPECIAL_ABILITY_RANGE; index <= this->y_ + SOLDIER_SPECIAL_ABILITY_RANGE; index++)
  {
    for(int inner = this->x_ - SOLDIER_SPECIAL_ABILITY_RANGE; inner <= this->x_ + SOLDIER_SPECIAL_ABILITY_RANGE; inner++)
    {
      tag = current_level_map->getGrid()[index][inner]; 

      if(tag == static_cast<int>(Grid::CHARACTER_ORC))
      {
        int ind = 0;
        ind = validOrc(orcs_current_level, inner, index);
        if(ind != -1)
        {
          Orc* placeholder = dynamic_cast<Orc*>(orcs_current_level[ind]);
          if(placeholder == nullptr || placeholder->isDead()) { continue;}

          placeholder->setCurrentTileTag(static_cast<int>(Grid::FLOOR_NEW_ONE));
          placeholder->setCurrentHealth(placeholder->getCurrentHealth() - this->ability_damage_);
          if(placeholder->getOrcType() == OrcType::CLASSIC) { placeholder->setAnimationState(AnimationState::ORC_HURT);}
          else if(placeholder->getOrcType() == OrcType::PLATED) { placeholder->setAnimationState(AnimationState::ORC_PLATED_HURT);}

          if(placeholder->getCurrentHealth() <= 0)
          { // isto plated death
            orcs_current_level[ind]->setDead();
            if(placeholder->getOrcType() == OrcType::CLASSIC) { orcs_current_level[ind]->setAnimationState(AnimationState::ORC_DEATH);}
            else if(placeholder->getOrcType() == OrcType::PLATED ) { orcs_current_level[ind]->setAnimationState(AnimationState::ORC_PLATED_DEATH);}
            else if(placeholder->getOrcType() == OrcType::ELITE) { orcs_current_level[ind]->setAnimationState(AnimationState::ORC_ELITE_DEATH);}
          }

        }
      }

      if(tag == static_cast<int>(Grid::FLOOR) || tag == static_cast<int>(Grid::FLOOR_NEW_ONE) || tag ==
        static_cast<int>(Grid::FLOOR_NEW_TWO) || tag == static_cast<int>(Grid::FLOOR_NEW_THREE))
      { 
        current_level_map->getGrid()[index][inner] = static_cast<int>(Grid::FLOOR_NEW_ONE);
      }
      else { continue; }// UBACI TEXTURE PA TESTIRAJ
    }
  }


  

}

Soldier::~Soldier()
{
  // check out whats there to destruct
}


std::pair<int, int> Soldier::checkMapObjNearby(Map* current_level_map, Detection where_looking) noexcept
{
  int x = this->getXcoordinate();
  int y = this->getYcoordinate();
  

  if( where_looking == Detection::DETECTED_LEFT && x - 1 > 0)
  {
    return { x - 1, y};
  }

  if( where_looking == Detection::DETECTED_RIGHT && x + 1 < current_level_map->getGrid()[0].size())
  {
    return { x + 1, y};
  }

  if( where_looking == Detection::DETECTED_UP && y - 1 > 0)
  {
    return { x, y - 1};
  }

  if( where_looking == Detection::DETECTED_DOWN && y + 1 < current_level_map->getGrid().size())
  {
    return { x, y + 1};
  }

  return {-1,-1};
}


















