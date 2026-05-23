#include "../include_/parser_utility.hpp"

#include "../../classes_/include_/text_field.hpp"

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

bool ParserUtility::isNumberPressed(SDL_Keycode key_code) noexcept
{
  switch(key_code)
  {
    case SDLK_0:
    case SDLK_1:
    case SDLK_2:
    case SDLK_3:
    case SDLK_4:
    case SDLK_5:
    case SDLK_6:
    case SDLK_7:
    case SDLK_8:
    case SDLK_9:
      return true;
    default:
      std::cout << "[CAUGHT] -> [ParserUtility::isNumberPressed] -> number wasnt pressed but caps lock is on <!> " << std::endl;
  }

  return false;
}

std::tuple<bool, bool, bool> ParserUtility::handleKeyMod(SDL_Keycode key_code) noexcept
{
  SDL_Keymod modifier = SDL_GetModState();
  bool shift = false;
  bool control = false;
  bool valid = true;

  if(modifier & KMOD_SHIFT)
  {
    shift = true;
  }

  if(modifier & KMOD_CTRL)
  {
    control = true;
  }

  if(ParserUtility::isShiftPressed(key_code) || ParserUtility::isControlPressed(key_code))
  {
    valid = false;
  }

  if(modifier & KMOD_CAPS)
  {
    if(!ParserUtility::isNumberPressed(key_code))
    {
      shift = true;
    }
  }


  return {valid, shift, control};
}

void ParserUtility::flushBackspacesQueue(std::queue<KeyboardInput*>& queue) noexcept
{
  while(!queue.empty())
  {
    KeyboardInput* placeholder = queue.front();
    
    if(placeholder->key_pressed_ == SDLK_BACKSPACE)
    {
      queue.pop();
      delete placeholder;
      std::cout << "[CAUGHT] -> [ParserUtility::flushQueue] -> backspace caught <!> " << std::endl;
      continue;
    }

    break;
  }
}

void ParserUtility::flushQueue(std::queue<KeyboardInput*>& queue) noexcept
{
  while(!queue.empty())
  {
    KeyboardInput* placeholder = queue.front();
    delete placeholder;
    queue.pop();
  }
}

KeyboardInput* ParserUtility::getKeyboardInput(TextField* text, std::queue<KeyboardInput*>& queue) noexcept
{
  if(text->getTextConst().size() == 0)
  {
    ParserUtility::flushBackspacesQueue(queue);
  }

  if(queue.empty())
  {
    return nullptr;
  }

  KeyboardInput* new_input = queue.front();
  queue.pop();

  return new_input;
}