#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../../include_/character.hpp"

class Knight : public Character
{
  private:
  

  public:
    // Constructor Destructor Copy Constructor
    Knight() = default;
    
    Knight(ClassType type);
    Knight(int world_x, int world_y, size_t level, 
            Stats* stats, Attributes* attr, ClassType type,
            Inventory* inventory, Armory* armory, 
            CharacterAnimationState animation_state, 
            size_t animation_index);

    Knight(const Knight& copy) = delete;
    ~Knight();


};


#endif