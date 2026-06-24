#include "../include_/character.hpp"
#include "../include_/game.hpp"

Character::Character(ClassType type)
{
  this->class_ = type;
  this->character_id_ = SIZE_T_MAX;
  this->stats_ = new Stats(type);
  this->attributes_ = new Attributes(type);

  
}

Character::Character(int world_x, int world_y, size_t level, size_t char_id,
                     Stats* stats, Attributes* attr, ClassType type, 
                     Inventory* inventory, Armory* armory, CharacterAnimationState animation_state, 
                     size_t animation_index)
: world_x_(world_x), 
  world_y_ (world_y), 
  level_(level), 
  character_id_(char_id),
  stats_(stats), 
  attributes_(attr), 
  class_(type), 
  inventory_(inventory), 
  armory_(armory), 
  animation_state_(animation_state), 
  animation_index_(animation_index) 
  {};


void Character::update(Game& game)
{
  
}

