#ifndef WIZARD_HPP
#define WIZARD_HPP

#include "../../include_/character.hpp"

class Wizard : public Character
{
  private:
  

  public:
    // Constructor Destructor Copy Constructor
    Wizard() = default;
    
    Wizard(ClassType type);
    Wizard(int world_x, int world_y, size_t level, 
            Stats* stats, Attributes* attr, ClassType type,
            Inventory* inventory, Armory* armory, 
            CharacterAnimationState animation_state, 
            size_t animation_index);

    Wizard(const Wizard& copy) = delete;
    ~Wizard();


};


#endif