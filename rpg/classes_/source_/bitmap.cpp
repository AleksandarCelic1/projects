#include "../include_/bitmap.hpp"


BitMap::BitMap(SDL_Texture* bitmap)
{
  this->bitmap_ = bitmap;
  // Here we need to make a WHOLE MAP of Glyphs*
  // Letters lowercase
  /*this->glyphs_['a'] = new Glyph();
  this->glyphs_['b'] = new Glyph();
  this->glyphs_['c'] = new Glyph();
  this->glyphs_['d'] = new Glyph();
  this->glyphs_['e'] = new Glyph();
  this->glyphs_['f'] = new Glyph();
  this->glyphs_['g'] = new Glyph();
  this->glyphs_['h'] = new Glyph();
  this->glyphs_['i'] = new Glyph();
  this->glyphs_['j'] = new Glyph();
  this->glyphs_['k'] = new Glyph();
  this->glyphs_['l'] = new Glyph();
  this->glyphs_['m'] = new Glyph();
  this->glyphs_['n'] = new Glyph();
  this->glyphs_['o'] = new Glyph();
  this->glyphs_['p'] = new Glyph();
  this->glyphs_['q'] = new Glyph();
  this->glyphs_['r'] = new Glyph();
  this->glyphs_['s'] = new Glyph();
  this->glyphs_['t'] = new Glyph();
  this->glyphs_['u'] = new Glyph();
  this->glyphs_['v'] = new Glyph();
  this->glyphs_['w'] = new Glyph();
  this->glyphs_['x'] = new Glyph();
  this->glyphs_['y'] = new Glyph();
  this->glyphs_['z'] = new Glyph();

  // Letters uppercase
  this->glyphs_['A'] = new Glyph();
  this->glyphs_['B'] = new Glyph();
  this->glyphs_['C'] = new Glyph();
  this->glyphs_['D'] = new Glyph();
  this->glyphs_['E'] = new Glyph();
  this->glyphs_['F'] = new Glyph();
  this->glyphs_['G'] = new Glyph();
  this->glyphs_['H'] = new Glyph();
  this->glyphs_['I'] = new Glyph();
  this->glyphs_['J'] = new Glyph();
  this->glyphs_['K'] = new Glyph();
  this->glyphs_['L'] = new Glyph();
  this->glyphs_['M'] = new Glyph();
  this->glyphs_['N'] = new Glyph();
  this->glyphs_['O'] = new Glyph();
  this->glyphs_['P'] = new Glyph();
  this->glyphs_['Q'] = new Glyph();
  this->glyphs_['R'] = new Glyph();
  this->glyphs_['S'] = new Glyph();
  this->glyphs_['T'] = new Glyph();
  this->glyphs_['U'] = new Glyph();
  this->glyphs_['V'] = new Glyph();
  this->glyphs_['W'] = new Glyph();
  this->glyphs_['X'] = new Glyph();
  this->glyphs_['Y'] = new Glyph();
  this->glyphs_['Z'] = new Glyph();

  // Numbers
  this->glyphs_['0'] = new Glyph();
  this->glyphs_['1'] = new Glyph();
  this->glyphs_['2'] = new Glyph();
  this->glyphs_['3'] = new Glyph();
  this->glyphs_['4'] = new Glyph();
  this->glyphs_['5'] = new Glyph();
  this->glyphs_['6'] = new Glyph();
  this->glyphs_['7'] = new Glyph();
  this->glyphs_['8'] = new Glyph();
  this->glyphs_['9'] = new Glyph();

  // Space
  this->glyphs_[' '] = new Glyph();

  // Special characters
  this->glyphs_[')'] = new Glyph();
  this->glyphs_['!'] = new Glyph();
  this->glyphs_['@'] = new Glyph();
  this->glyphs_['#'] = new Glyph();
  this->glyphs_['$'] = new Glyph();
  this->glyphs_['%'] = new Glyph();
  this->glyphs_['^'] = new Glyph();
  this->glyphs_['&'] = new Glyph();
  this->glyphs_['*'] = new Glyph();
  this->glyphs_['('] = new Glyph();

  this->glyphs_['-'] = new Glyph();
  this->glyphs_['_'] = new Glyph();
  this->glyphs_['='] = new Glyph();
  this->glyphs_['+'] = new Glyph();
  this->glyphs_['['] = new Glyph();
  this->glyphs_['{'] = new Glyph();
  this->glyphs_[']'] = new Glyph();
  this->glyphs_['}'] = new Glyph();
  this->glyphs_['\\'] = new Glyph();
  this->glyphs_['|'] = new Glyph();
  this->glyphs_[';'] = new Glyph();
  this->glyphs_[':'] = new Glyph();
  this->glyphs_['\''] = new Glyph();
  this->glyphs_['"'] = new Glyph();
  this->glyphs_[','] = new Glyph();
  this->glyphs_['<'] = new Glyph();
  this->glyphs_['.'] = new Glyph();
  this->glyphs_['>'] = new Glyph();
  this->glyphs_['/'] = new Glyph();
  this->glyphs_['?'] = new Glyph();
  this->glyphs_['`'] = new Glyph();
  this->glyphs_['~'] = new Glyph();*/
}

BitMap::~BitMap()
{
  for(auto iterator : this->glyphs_)
  {
    if(iterator.second != nullptr)
    {
      free(iterator.second);
      iterator.second = nullptr;
    }
  }
}

void BitMap::makeAllGlyphs() noexcept
{
  std::unordered_map<BitMapOffsets, SDL_Rect> map = makeOffsetsMap();

  char key = 'A';

  for(auto iterator : map)
  {
    this->makeGlyph(key, iterator.second);
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

std::unordered_map<BitMapOffsets, SDL_Rect> BitMap::makeOffsetsMap() noexcept
{
  std::unordered_map<BitMapOffsets, SDL_Rect> map;

  int x_offset = 0;
  int y_offset = 0;

  for(int index = 0; index < AMOUNT_OF_LETTERS; index++)
  {
    /*First we have 26 capital letters and then 26 lowercase letters and then numbers 0-9*/
    if(index % 26 == 0 && index != 0)
    {
      y_offset += LETTER_WIDTH_AND_HEIGHT;
    }

    SDL_Rect placeholder;
    placeholder.x = x_offset;
    placeholder.y = y_offset;
    placeholder.w = LETTER_WIDTH_AND_HEIGHT;
    placeholder.h = LETTER_WIDTH_AND_HEIGHT;

    BitMapOffsets key = static_cast<BitMapOffsets>(index);
    map.insert({key, placeholder});

    x_offset += LETTER_WIDTH_AND_HEIGHT;

  }

  return map;
}


Glyph* BitMap::getGlyph(char key) const 
{
  Glyph* retval = static_cast<Glyph*>(ExceptionHandler::get(this->glyphs_, key));
  return retval;
}