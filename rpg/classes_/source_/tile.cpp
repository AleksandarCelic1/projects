#include "../include_/tile.hpp"

Tile::Tile(FloorType new_type, int world_x, int world_y)
{
  this->type_ = new_type;
  this->world_x_ = world_x;
  this->world_y_ = world_y;
}


// Not Implemented
void Tile::render(SDL_Renderer* renderer)
{
  return;
}