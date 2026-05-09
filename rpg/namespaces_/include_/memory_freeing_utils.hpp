#ifndef MEMORY_FREEING_UTILS_HPP
#define MEMORY_FREEING_UTILS_HPP

#include "../../structs_/structs.hpp"

namespace MemoryFreeingUtils
{
  template <typename T> 
  void clearMap(T& container) noexcept
  {
    for(auto& iterator : container)
    {
      if(iterator.second != nullptr)
      {
        delete iterator.second;
        iterator.second = nullptr;
      }
    }

    container.clear();
  };

  template <typename T>
  void clearVector(std::vector<T*>& vec) noexcept
  {
    for(auto& iterator : vec)
    {
      if(iterator != nullptr)
      {
        delete iterator;
        iterator = nullptr;
      }
    }

    vec.clear();
  };

  template <typename T>
  void clearTextureAssets(std::unordered_map<T, TextureAsset>& map) noexcept
  {
    for(auto& [key, text_asset] : map)
    {
      TextureAsset& placeholder = text_asset;

      if(placeholder.texture_ != nullptr)
      {
        SDL_DestroyTexture(placeholder.texture_);
        placeholder.texture_ = nullptr;
      }
    }

    map.clear();
  }
};

#endif