#include "../include_/state.hpp"

State::State(SDL_Renderer* main_renderer, int window_width, int window_height)
{
  SDL_Rect placeholder;
  placeholder.x = 0;
  placeholder.y = 0;
  placeholder.w = window_width;
  placeholder.h = window_height;

  this->quad_tree_ = new QuadTree(placeholder);
  this->renderer_ = main_renderer;

}

State::~State()
{
  if(this->quad_tree_ != nullptr)
  {
    delete this->quad_tree_;
    this->quad_tree_ = nullptr;
  }
}

int State::centerX(int x, int screen_width, int object_width)
{
  return (x + ((screen_width / 2) - (object_width / 2)));
}

int State::centerY(int y, int screen_height, int object_height)
{
  return (y + ((screen_height / 2) - (object_height / 2)));
}
