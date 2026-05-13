#include "../include_/font_manager.hpp"
#include "../include_/game.hpp"

FontManager::FontManager(Game& game)
{
  SDL_Surface* bitmap_surface = IMG_Load("../photos_/bitmaps_/BitmapINPROGRESS.png");
  if(bitmap_surface == nullptr)
  {
    std::cout << "[ERROR] -> [FontManager::FontManager] -> IMG-Load failed <!>" << std::endl;
    return;
  }

  SDL_Texture* bitmap_texture = SDL_CreateTextureFromSurface(game.getRenderer(), bitmap_surface);
  SDL_FreeSurface(bitmap_surface);
  if(bitmap_texture == nullptr)
  {
    std::cout << "[ERROR] -> [FontManager::FontManager] -> Texture-Load failed <!>" << std::endl;
    return;
  }

  // The texture is logically 512x512 thats the source, no need to scale 

  this->bitmap_ = new BitMap(bitmap_texture);
}

FontManager::~FontManager()
{
  MemoryFreeingUtils::clearPointer(this->bitmap_);
}