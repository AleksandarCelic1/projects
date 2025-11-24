#ifndef ARMORY_HPP
#define ARMORY_HPP

#include <iostream>

class Ring;
class Trinket;
class Sword;

class Armor
{
  private:
    Ring* first_ring_;
    Ring* second_ring_;
    Trinket* first_trinket_;
    Trinket* second_trinket_;
    Sword* main_sword_;
  public:
    Armor();
    Armor(const Armor& copy) = delete;
    ~Armor();

    // Getters
    Ring* getFirstRing() const {return this->first_ring_;}
    Ring* getSecondRing() const {return this->second_ring_;}
    Trinket* getFirstTrinket() const {return this->first_trinket_;}
    Trinket* getSecondTrinket() const {return this->second_trinket_;}
    Sword* getSword() const {return this->main_sword_;}

    // Setters

    void setFirstRing(Ring* new_ring_first) {this->first_ring_ = new_ring_first;}
    void setSecondRing(Ring* new_ring_second) {this->second_ring_ = new_ring_second;}
    void setFirstTrinket(Trinket* new_trinket_first) {this->first_trinket_ = new_trinket_first;}
    void setSecondTrinket(Trinket* new_trinket_second) {this->second_trinket_ = new_trinket_second;}
    void setMainSword(Sword* new_sword) {this->main_sword_ = new_sword;}




};


#endif