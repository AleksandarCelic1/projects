#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "attributes.hpp"
#include "stats.hpp"

class Character
{
  private:
    int world_x_;
    int world_y_; 

    size_t gold_;
    size_t silver_;
    size_t bronze_;
    size_t level_;

    Stats stats_;
    Attributes attributes_;
    ClassType class_;

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

    size_t getGold() const { return this->gold_; }
    size_t getSilver() const { return this->silver_; }
    size_t getBronze() const { return this->bronze_; }
    
    Stats& getStats() { return this->stats_; }
    Attributes& getAttributes() { return this->attributes_; }
    ClassType getClassType() { return this->class_; }

    CharacterAnimationState getAnimationState() const { return this->animation_state_; }
    size_t getAnimationIndex() const { return this->animation_index_; }

    // Setters
    void setWorldX(int& new_x) noexcept { this->world_x_ = new_x; }
    void setWorldY(int& new_y) noexcept { this->world_y_ = new_y; }
    void setAnimationState(CharacterAnimationState& new_state) noexcept { this->animation_state_ = new_state; }
    void setAnimationIndex(size_t& new_index) noexcept { this->animation_index_ = new_index; }

    // Functions
    void addGold(int& gold) noexcept;
    void addSilver(int& silver) noexcept;
    void addBronze(int& bronze) noexcept;

    // Subtract Functions dont handle Underflow as they are protected by 
    // future implementation of Shop Mechanism with converter functions
    void subtractGold(int& gold) noexcept;
    void subtractSilver(int& silver) noexcept;
    void subtractBronze(int& bronze) noexcept;

    // Gaining/Getting Gold Mechanism
    void convertBronzeToSilver() noexcept;
    void convertSilverToGold() noexcept;

    // Buying Stuff with Gold Mechanism
    void convertGoldToSilver() noexcept;
    void convertSilverToBronze() noexcept;

    void checkGoldCapacity() noexcept;

    virtual void render(SDL_Renderer* renderer, std::unordered_map<CharacterAnimationState, SDL_Surface*> map) = 0;



  
    

};


#endif