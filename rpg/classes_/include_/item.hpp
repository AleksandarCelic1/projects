#ifndef ITEM_HPP
#define ITEM_HPP


#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../namespaces_/namespaces.hpp"

class Item
{
  private:
    size_t sell_value_;
 

  public:
    Item() = default;
    Item(const Item& copy) = delete;
    virtual ~Item();






  // Will be pure virtual, also there will be Equipemnt that derives from this, so we have equipemnt and sellable items separate!
};







#endif