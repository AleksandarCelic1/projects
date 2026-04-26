#include "../include_/font_manager.hpp"

FontManager::~FontManager()
{
  if(this->bitmap_in_use_ != nullptr)
  {
    free(this->bitmap_in_use_);
    this->bitmap_in_use_ = nullptr;
  }

  if(this->bitmap_1270 != nullptr)
  {
    free(this->bitmap_1270);
    this->bitmap_1270 = nullptr;
  }

  if(this->bitmap_1920 != nullptr)
  {
    free(this->bitmap_1920);
    this->bitmap_1920 = nullptr;
  }

  if(this->bitmap_2560 != nullptr)
  {
    free(this->bitmap_2560);
    this->bitmap_2560 = nullptr;
  }
}