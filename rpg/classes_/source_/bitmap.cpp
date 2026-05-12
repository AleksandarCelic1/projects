#include "../include_/bitmap.hpp"


BitMap::BitMap(SDL_Texture* bitmap)
{
  this->bitmap_ = bitmap;
  // Here we need to make a WHOLE MAP of Glyphs*
  // Letters lowercase

  this->makeAllGlyphs();
}

BitMap::~BitMap()
{
  for(auto& iterator : this->glyphs_)
  {
    if(iterator.second != nullptr)
    {
      delete iterator.second;
      iterator.second = nullptr;
    }
  }
}

void BitMap::makeAllGlyphs() noexcept
{
  /* Why do i need a map for this doesnt vector just work here ?!?*/
  std::vector<SDL_Rect> vec = makeOffsetsVector();

  char key = 'A';

  for(auto iterator : vec)
  {
    std::cout << key << " " << iterator.x << " " << iterator.y << std::endl;
    this->makeGlyph(key, iterator);
    key++;

    if(key == 'Z' + 1)
    {
      key = 'a';
    }
  }
}

void BitMap::makeGlyph(char key, SDL_Rect src_rect) noexcept
{
  this->glyphs_.insert({key, new Glyph(src_rect)});
}

std::vector<SDL_Rect> BitMap::makeOffsetsVector() noexcept
{
  std::vector<SDL_Rect> vec;

  int x_offset = 0;
  int y_offset = 0;

  for(int index = 0; index < AMOUNT_OF_LETTERS; index++)
  {
    /*First we have 26 capital letters and then 26 lowercase letters and then numbers 0-9*/
    if(index % 26 == 0 && index != 0)
    {
      x_offset = 0;
      y_offset += LETTER_WIDTH_AND_HEIGHT;
    }

    SDL_Rect placeholder;
    placeholder.x = x_offset;
    placeholder.y = y_offset;
    placeholder.w = LETTER_WIDTH_AND_HEIGHT;
    placeholder.h = LETTER_WIDTH_AND_HEIGHT;

    vec.push_back(placeholder);

    x_offset += LETTER_WIDTH_AND_HEIGHT;

    /* Debug printfs <!> */
    // std::cout << x_offset << " " << y_offset << std::endl;

  }

  return vec;
}


Glyph* BitMap::getGlyph(char key) const 
{
  Glyph* retval = static_cast<Glyph*>(ExceptionHandler::get(this->glyphs_, key));
  return retval;
}