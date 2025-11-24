#include "armory.hpp"
#include "ring.hpp"
#include "trinket.hpp"
#include "sword.hpp"

Armor::Armor()
{
  this->first_ring_ = nullptr;
  this->second_ring_ = nullptr;
  this->first_trinket_ = nullptr;
  this->second_trinket_ = nullptr;
  this->main_sword_ = nullptr;
}

Armor::~Armor()
{
  if(this->first_ring_ != nullptr)
  {
    delete first_ring_;
    first_ring_ = nullptr;
  }

  if(this->second_ring_ != nullptr)
  {
    delete second_ring_;
    second_ring_ = nullptr;
  }

  if(this->first_trinket_ != nullptr)
  {
    delete first_trinket_;
    first_trinket_ = nullptr;
  }

  if(this->second_trinket_ != nullptr)
  {
    delete second_trinket_;
    second_trinket_ = nullptr;
  }

  if(this->main_sword_ != nullptr)
  {
    delete main_sword_;
    main_sword_ = nullptr;
  }
}