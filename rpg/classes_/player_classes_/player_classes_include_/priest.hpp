#ifndef PRIEST_HPP
#define PRIEST_HPP

#include "../../include_/character.hpp"

class Priest : public Character
{
  private:
  

  public:
    // Constructor Destructor Copy Constructor
    Priest() = default;
    
    Priest(ClassType type);
    Priest(int world_x, int world_y, size_t level, 
            Stats* stats, Attributes* attr, ClassType type,
            Inventory* inventory, Armory* armory, 
            CharacterAnimationState animation_state, 
            size_t animation_index);

    Priest(const Priest& copy) = delete;
    ~Priest();


};


#endif