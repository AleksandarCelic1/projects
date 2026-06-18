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


void RectUtils::debugOutline(SDL_Renderer* main_renderer, const SDL_Rect& rect) noexcept
{
  Uint8 old_r;
  Uint8 old_g;
  Uint8 old_b;
  Uint8 old_a;

  SDL_GetRenderDrawColor(main_renderer, &old_r, &old_g, &old_b, &old_a);

  SDL_SetRenderDrawColor(main_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawRect(main_renderer, &rect);

  SDL_SetRenderDrawColor(main_renderer, old_r, old_g, old_b, old_a);

  return;
}

void RectUtils::info(const SDL_Rect& rect) noexcept
{
  std::cout << "[INFORMATION] -> [RectUtils::info] -> " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << std::endl;
  return;
}

int RectUtils::centerX(int x, int screen_width, int object_width)
{
  return (x + ((screen_width / 2) - (object_width / 2)));
}

int RectUtils::centerY(int y, int screen_height, int object_height)
{
  return (y + ((screen_height / 2) - (object_height / 2)));
}

