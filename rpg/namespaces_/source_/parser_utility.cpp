#include "../include_/parser_utility.hpp"

bool ParserUtility::isShiftPressed(SDL_Keycode key_code) noexcept
{
  if(key_code == SDLK_LSHIFT || key_code == SDLK_RSHIFT)
  {
    return true;
  }

  return false;
}

bool ParserUtility::isControlPressed(SDL_Keycode key_code) noexcept
{
  if(key_code == SDLK_LCTRL || key_code == SDLK_RCTRL)
  {
    return true;
  }

  return false;
}

void ParserUtility::flushQueue(std::queue<KeyboardInput*>& queue) noexcept
{
  while(!queue.empty())
  {
    KeyboardInput* placeholder = queue.front();
    
    if(placeholder->key_pressed_ == SDLK_BACKSPACE)
    {
      queue.pop();
      delete placeholder;
      continue;
    }

    break;
  }
}