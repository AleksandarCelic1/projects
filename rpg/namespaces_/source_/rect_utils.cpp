#include "../include_/rect_utils.hpp"

bool RectUtils::intersectDetection(const SDL_Rect& source, const SDL_Rect& new_elem) noexcept
{
  int x = new_elem.x;
  int y = new_elem.y;
  int w = new_elem.w;
  int h = new_elem.h;

  if((x <= source.x + source.w)
  && (x + w >= source.x)
  && (y <= source.y + source.h)
  && (y + h >= source.y))
  {
    return true;
  }

  return false;
}

bool RectUtils::detectMouseClick(const SDL_Rect& source, int mouse_x, int mouse_y) noexcept
{
  int x = source.x;
  int y = source.y;
  int w = source.w; 
  int h = source.h;

  if(mouse_x >= x && mouse_x <= x + w
  && mouse_y >= y && mouse_y <= y + h)
  {
    return true;
  }

  return false;
}