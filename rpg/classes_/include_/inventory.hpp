#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "container.hpp"

/*
  Inventory could use a list of some sort of Containers(new_class), which are obtainable/upgradable
  through the playthrough, which are essentially a 2D arrays which contain items(new_class) <!> 
*/
class Inventory
{
  private:
    std::vector<Container*> containers_;
    size_t gold_;
    size_t silver_;
    size_t bronze_;
    
  
  public:
  // Constructor Destructor Copy Constructor
  Inventory() = default;
  Inventory(size_t gold, size_t silver, size_t bronze, std::vector<Container*> containers);
  Inventory(const Inventory& copy) = delete;
  ~Inventory() = default;

  // Getters
  std::vector<Container*>& getContainers() noexcept { return this->containers_; } 
  size_t getGold() const { return this->gold_; }
  size_t getSilver() const { return this->silver_; }
  size_t getBronze() const { return this->bronze_; }

  // Setters

  // Functions 
  void setNewContainers(std::vector<Container*>& new_containers) noexcept { this->containers_ = new_containers; }
  void addNewContainer(Container* new_container) noexcept;
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