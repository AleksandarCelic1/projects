#include "../include_/elementUI.hpp"
#include "../include_/game.hpp"

ElementUI::ElementUI(const TextureAsset& asset, int scaling_factor) 
  : texture_(asset.texture_),
    dst_rect_({0, 0, asset.width_ * scaling_factor, asset.height_ * scaling_factor})
  {}

bool ElementUI::detectMouseClick(int mouse_x, int mouse_y) noexcept
{
  return RectUtils::detectMouseClick(this->getDstRect(), mouse_x, mouse_y);
}


void ElementUI::render(Game& game) noexcept
{
  // This is the most basic Render for the most simple Widgets/UI Elements
  SDL_RenderCopy(game.getRenderer(), this->texture_, nullptr, &this->dst_rect_);
}

/*
  ElementUI class gets a upgrade with update function as certain widgets
  will have animations <!>
*/
void ElementUI::update(Game& game) noexcept
{
  return;
}