#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "attributes.hpp"
#include "stats.hpp"
#include "inventory.hpp"
#include "armory.hpp"

class Game;

class Character
{
  private:
    /*
      Regarding the "character_id_" there are two scenarios:
        1. when creating the character throught the Character-Creation-Menu the ID becomes an INVALID_MAGIC_NUMBER until we save
           the character by doing INSERT query, and the ID will be assigned to that specific row
        2. When an account gets logged in we can retrieve the CharID so we can later by save modify it <!> 
    */

    size_t character_id_; 
    size_t level_;
    int world_x_;
    int world_y_; 
    

    ClassType class_;

    Stats* stats_;
    Attributes* attributes_;
    Inventory* inventory_;
    Armory* armory_;

    CharacterAnimationState animation_state_;
    AnimationInfo animation_info; // Do we need this <?>
    size_t animation_index_;
    

  public:
    // Constructor, Copy Constructor, Destructor
    Character(ClassType type);
    Character(int world_x, int world_y, size_t level, size_t char_id, Stats* stats, Attributes* attr, ClassType type, Inventory* inventory, Armory* armory, CharacterAnimationState animation_state, size_t animation_index);
    Character(const Character& copy) = delete;
    virtual ~Character() = default; // see later if there is something to be deleted << !

    // Getters
    int getWorldX() const { return this->world_x_; }
    int getWorldY() const { return this->world_y_; }

    
    Stats* getStats() { return this->stats_; }
    Attributes* getAttributes() { return this->attributes_; }
    ClassType getClassType() { return this->class_; }
    Inventory* getInvetory() { return this->inventory_; }

    CharacterAnimationState getAnimationState() const { return this->animation_state_; }
    AnimationInfo& getAnimationInfo() noexcept { return this->animation_info; }
    size_t getAnimationIndex() const { return this->animation_index_; }
    size_t getLevel() const { return this->level_; }

    // Setters
    void setWorldX(int& new_x) noexcept { this->world_x_ = new_x; }
    void setWorldY(int& new_y) noexcept { this->world_y_ = new_y; }
    void setLevel(size_t new_level) noexcept { this->level_ = new_level; }
    void setAnimationState(CharacterAnimationState& new_state) noexcept { this->animation_state_ = new_state; }
    void setAnimationIndex(size_t& new_index) noexcept { this->animation_index_ = new_index; }
    void setInventory(Inventory* new_inventory) noexcept { this->inventory_ = new_inventory; }
    void setAnimationInfo(AnimationInfo new_anim_info) noexcept { this->animation_info = new_anim_info; }

    // Functions
    
    virtual void render(SDL_Renderer* renderer, std::unordered_map<CharacterAnimationState, SDL_Surface*> map) = 0;
    virtual void update(Game& game);

};


#endif