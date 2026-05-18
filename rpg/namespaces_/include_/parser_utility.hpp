#ifndef PARSER_UTILITY_HPP
#define PARSER_UTILITY_HPP


#include "../../constants_/constants.hpp"
#include "../../structs_/structs.hpp"

namespace ParserUtility
{
  bool isShiftPressed(SDL_Keycode key_code) noexcept;
  bool isControlPressed(SDL_Keycode key_code) noexcept;
  bool isNumberPressed(SDL_Keycode key_code) noexcept;
  void flushBackspacesQueue(std::queue<KeyboardInput*>& queue) noexcept;
  void flushQueue(std::queue<KeyboardInput*>& queue) noexcept;
  std::tuple<bool, bool, bool> handleKeyMod(SDL_Keycode key_code) noexcept;

};


#endif