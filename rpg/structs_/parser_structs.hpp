#ifndef PARSER_STRUCTS_HPP
#define PARSER_STRUCTS_HPP

#include "../constants_/constants.hpp"

typedef struct KeyboardInput
{
  SDL_Keycode key_pressed_;
  bool shift_held_;
  bool control_held_;

} KeyboardInput ;

#endif

