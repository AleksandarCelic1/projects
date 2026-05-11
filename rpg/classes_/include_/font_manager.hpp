#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include "bitmap.hpp"

class Game;

class FontManager
{
  private:
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