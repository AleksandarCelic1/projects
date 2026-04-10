#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(SDL_Renderer* main_renderer) : State(main_renderer)
{

}


void LoginState::render(Game& game)
{
  SDL_RenderClear(game.getRenderer());
  this->renderBackground(game);
}

void LoginState::update(Game& game)
{

}

void LoginState::renderBackground(Game& game)
{
  TextureAsset placeholder = game.getTextureManager().getUITexture(UI::LOGIN_BACKGROUND);

  SDL_Rect rect;
  rect.h = placeholder.height_ * game.getScalingFactor();
  rect.w = placeholder.width_ * game.getScalingFactor();
  rect.x = 0;
  rect.y = 0;

  SDL_RenderCopy(game.getRenderer(), placeholder.texture_, nullptr, &rect);

  // nullprt for SRC rect means -> that we take a specific part of the texture and then render 
  // it with DST rect and DST holds x,y,w,h if we do nullprt for SRC we just use the entire Texture

}

