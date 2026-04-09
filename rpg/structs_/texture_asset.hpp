#ifndef TEXTURE_ASSET_HPP
#define TEXTURE_ASSET_HPP

#include <SDL.h>
#include <iostream>

struct TextureAsset
{
  SDL_Texture* texture_;
  int width_;
  int height_; 
};


#endif