#include "../include_/dispatcher.hpp"
#include "../include_/elementUI.hpp"

bool Dispatcher::detectingClick(int mouse_x, int mouse_y, ElementUI* element) noexcept
{
  return RectUtils::detectMouseClick(element->getDstRect(), mouse_x, mouse_y);
}

