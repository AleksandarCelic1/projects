#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "attributes.hpp"
#include "stats.hpp"
#include "inventory.hpp"
#include "armory.hpp"

class Character
{
  private:
    int world_x_;
    int world_y_; 


    Stats stats_;
    Attributes attributes_;
    ClassType class_;
    Inventory* inventory_;
    Armory* armory_;

    CharacterAnimationState animation_state_;
    size_t animation_index_;

  public:
    // Constructor, Copy Constructor, Destructor
    Character(ClassType type);
    Character(const Character& copy) = delete;
    ~Character() = default; // see later if there is something to be deleted << !

    // Getters
    int getWorldX() const { return this->world_x_; }
    int getWorldY() const { return this->world_y_; }

    
    Stats& getStats() { return this->stats_; }
    Attributes& getAttributes() { return this->attributes_; }
    ClassType getClassType() { return this->class_; }
    Inventory* getInvetory() { return this->inventory_; }

    CharacterAnimationState getAnimationState() const { return this->animation_state_; }
    size_t getAnimationIndex() const { return this->animation_index_; }

    // Setters
    void setWorldX(int& new_x) noexcept { this->world_x_ = new_x; }
    void setWorldY(int& new_y) noexcept { this->world_y_ = new_y; }
    void setAnimationState(CharacterAnimationState& new_state) noexcept { this->animation_state_ = new_state; }
    void setAnimationIndex(size_t& new_index) noexcept { this->animation_index_ = new_index; }
    void setInventory(Inventory* new_inventory) noexcept { this->inventory_ = new_inventory; }

    // Functions
    

    virtual void render(SDL_Renderer* renderer, std::unordered_map<CharacterAnimationState, SDL_Surface*> map) = 0;

};


#endif