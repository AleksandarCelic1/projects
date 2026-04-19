#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"


class Inventory
{
  private:
    size_t gold_;
    size_t silver_;
    size_t bronze_;
    size_t level_;
  
  public:
  // Constructor Destructor Copy Constructor
  Inventory() = default;
  Inventory(const Inventory& copy) = delete;
  ~Inventory() = default;

  // Getters
  size_t getGold() const { return this->gold_; }
  size_t getSilver() const { return this->silver_; }
  size_t getBronze() const { return this->bronze_; }

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