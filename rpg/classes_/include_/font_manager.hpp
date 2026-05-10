#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include "bitmap.hpp"

class Game;

class FontManager  // Probably will use two bitmaps the 1270 will be scaled to 2560 instead of holding another one <!>
{
  private:
    // Only one will be loaded, when we switch then we load the targeted one <!>
    BitMap* bitmap_;

  public:
    // Constructor Destructor Copy Constructor
    FontManager() = default;
    FontManager(Game& game);
    FontManager(const FontManager& copy) = delete;
    ~FontManager();

    // Getters
    BitMap* getBitmap() const noexcept { return this->bitmap_; }

    // Functions 




};




#endif