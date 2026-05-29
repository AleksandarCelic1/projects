#include "../include_/container.hpp"

Container::Container(std::vector<std::vector<Item*>> items) 
  : items_(items)
  {}

Container::~Container()
{
  int rows = items_.size();
  for(int index = 0; index < rows; index++)
  {
    int columns = items_.at(index).size();
    for(int inner = 0; inner < columns; inner++)
    {
      MemoryFreeingUtils::clearPointer(items_.at(index).at(inner));
    }
  }
}