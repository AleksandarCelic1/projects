#include "../include_/character.hpp"
#include "../include_/game.hpp"

Character::Character(int world_x, int world_y, size_t level,
                     Stats* stats, Attributes* attr, ClassType type, 
                     Inventory* inventory, Armory* armory, CharacterAnimationState animation_state, 
                     size_t animation_index)
: world_x_(world_x), 
  world_y_ (world_y), 
  level_(level), 
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