#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "attributes.hpp"
#include "stats.hpp"

class Character
{
  private:
    size_t gold_;
    size_t silver_;
    size_t bronze_;
    size_t level_;

    Stats stats_;
    Attributes attributes_;
    ClassType class_;

  public:
    // Constructor, Copy Constructor, Destructor
    Character(ClassType type);
    Character(const Character& copy) = delete;
    ~Character() = default; // see later if there is something to be deleted << !

    // Getters
    size_t getGold() const { return this->gold_; }
    size_t getSilver() const { return this->silver_; }
    size_t getBronze() const { return this->bronze_; }
    
    Stats& getStats() { return this->stats_; }
    Attributes& getAttributes() { return this->attributes_; }
    ClassType getClassType() { return this->class_; }

    // Setters

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



  
    

};


#endif