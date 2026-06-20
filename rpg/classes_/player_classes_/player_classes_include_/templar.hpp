#ifndef TEMPLAR_HPP
#define TEMPLAR_HPP

#include "../../include_/character.hpp"

class Templar : public Character
{
  private:
  

  public:
    // Constructor Destructor Copy Constructor
    Templar() = default;
    
    Templar(ClassType type);
    Templar(int world_x, int world_y, size_t level, 
            Stats* stats, Attributes* attr, ClassType type,
            Inventory* inventory, Armory* armory, 
            CharacterAnimationState animation_state, 
            size_t animation_index);

    Templar(const Templar& copy) = delete;
    ~Templar();


};


#endif