#ifndef MEMORY_FREEING_UTILS_HPP
#define MEMORY_FREEING_UTILS_HPP

namespace MemoryFreeingUtils
{
  template <typename Map, typename Key> 
  void clearMap(Map& container, Key& key) noexcept
  {
    for(auto iterator : container)
    {
      if(iterator.second != nullptr)
      {
        free(iterator.second);
        iterator.second = nullptr;
      }
    }
  }

  template <typename T>
  void clearVector(std::vector<T>& vec) noexcept
  {
    for(auto iterator : vec)
    {
      if(iterator != nullptr)
      {
        free(iterator);
        iterator = nullptr;
      }
    }
  }

};

#endif