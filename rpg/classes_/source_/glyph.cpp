#include "../include_/glyph.hpp"

Glyph::Glyph(SDL_Rect& src_rect)
{
  this->src_rect_ = src_rect;
  this->scaled_height_ = 0;
  this->scaled_width_ = 0;
}