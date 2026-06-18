#ifndef RECT_UTILS_HPP
#define RECT_UTILS_HPP

#include "../../constants_/constants.hpp"

namespace RectUtils
{
  /* Quick debug output to check rect's x,y,w,h attributes <!> */
  void info(const SDL_Rect& rect) noexcept;

  /* Implement a functions that renders a outline for provided rect -> used for debugging purposeses <!> */
  void debugOutline(SDL_Renderer* main_renderer, const SDL_Rect& rect) noexcept;

  /* IntersectDetections -> checks if the provided "rect" is intersecting with "source" */
  bool intersectDetection(const SDL_Rect& source, const SDL_Rect& rect) noexcept;

  /* detectMouseClick -> check if the provided (x,y) is within the provided destination rect "source" */
  bool detectMouseClick(const SDL_Rect& source, int mouse_x, int mouse_y) noexcept;


  /* centerX/Y -> centering the X,Y of new element using the provided parameters */
  int centerX(int x, int screen_width, int object_width);
  int centerY(int y, int screen_height, int object_height);


}


#endif