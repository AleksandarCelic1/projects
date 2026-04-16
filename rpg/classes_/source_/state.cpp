#include "../include_/state.hpp"

State::State(SDL_Renderer* main_renderer)
{
  this->renderer_ = main_renderer;
}

int State::centerX(int x, int screen_width, int object_width)
{
  return (x + ((screen_width / 2) - (object_width / 2)));
}

int State::centerY(int y, int screen_height, int object_height)
{
  return (y + ((screen_height / 2) - (object_height / 2)));
}
