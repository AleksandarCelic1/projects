#include "../include_/elementUI.hpp"
#include "../include_/game.hpp"

ElementUI::ElementUI(const TextureAsset& asset, int scaling_factor)
{
  this->texture_ = asset.texture_; 
  this->dst_rect_.x = 0;
  this->dst_rect_.y = 0;
  this->dst_rect_.w = asset.width_ * scaling_factor;
  this->dst_rect_.h = asset.height_ * scaling_factor;

}

bool ElementUI::detectMouseClick(int mouse_x, int mouse_y) noexcept
{
  return (mouse_x >= this->dst_rect_.x && mouse_x <= this->dst_rect_.x + this->dst_rect_.w 
       && mouse_y >= this->dst_rect_.y && mouse_y <= this->dst_rect_.y + this->dst_rect_.h);
}


void ElementUI::render(Game& game) noexcept
{
  // This is the most basic Render for the most simple Widgets/UI Elements
  SDL_RenderCopy(game.getRenderer(), this->texture_, nullptr, &this->dst_rect_);
}