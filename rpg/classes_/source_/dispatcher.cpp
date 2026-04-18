#include "../include_/dispatcher.hpp"
#include "../include_/elementUI.hpp"

bool Dispatcher::detectingClick(int mouse_x, int mouse_y, ElementUI* element)
{
  const SDL_Rect& placeholder = element->getRect();

  int x = placeholder.x;
  int y = placeholder.y;
  int w = placeholder.w; 
  int h = placeholder.h;

  if(mouse_x >= x && mouse_x <= x + w
  && mouse_y >= y && mouse_y <= y + h)
  {
    return true;
  }

  return false;
}

