#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include "bitmap.hpp"

class FontManager  // Probably will use two bitmaps the 1270 will be scaled to 2560 instead of holding another one <!>
{
  private:
    // Only one will be loaded, when we switch then we load the targeted one <!>
    BitMap* bitmap_in_use_;
    BitMap* bitmap_1270;
    BitMap* bitmap_1920;
    BitMap* bitmap_2560;

  public:
    // Constructor Destructor Copy Constructor
    FontManager() = default;
    FontManager(const FontManager& copy) = delete;
    ~FontManager();

    // Getters
    BitMap* getBitmap() const noexcept { return this->bitmap_in_use_; }

    // Functions 




};




#endif