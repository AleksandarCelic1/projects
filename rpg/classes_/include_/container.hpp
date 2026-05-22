#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "item.hpp"

/*
  Will be a base class which can be derived from classes like e.g.
  Bag, Chest, Shelf, Quiver, etc.
*/
class Container
{
  private:
    std::vector<std::vector<Item*>> items_;


  public:
    // Constructor Destructor Copy Constructor
    Container() = default;
    Container(Container& copy) = delete;
    ~Container();

    // Getters 
    std::vector<std::vector<Item*>>& getItems() noexcept { return this->items_; }

    // Setters
    void setItems(std::vector<std::vector<Item*>>& new_items) noexcept { this->items_ = new_items; }

    // Functions 
    void addItem(Item* new_item) noexcept;
    void removeItem(); // This function will probably change its signature


};





#endif