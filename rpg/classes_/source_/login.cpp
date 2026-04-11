#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(SDL_Renderer* main_renderer) : State(main_renderer)
{
  this->time_passed_ = 0.0f;
  this->panel_delay_ = 3.0f;
  this->smooth_duration_ = 1.0f;


}


void LoginState::render(Game& game)
{
  this->renderBackground(game);
  this->renderLoginPanel(game);
}

void LoginState::update(Game& game)
{
  this->updateTimePassed(game);
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

void LoginState::updateTimePassed(Game& game)
{
  this->time_passed_ += game.getDeltaTime();
}

void LoginState::renderLoginPanel(Game& game)
{
  if(this->time_passed_ < this->panel_delay_)
  {
    // Print out a error message just so we know where we are currently << !  Consider Error Constant File with all messages
    return;
  }

  float fade_time = this->time_passed_ - this->panel_delay_;

  if(fade_time > this->smooth_duration_)
  {
    fade_time = this->smooth_duration_;
  }

  float progress = fade_time / this->smooth_duration_; 
  // This goes "slowly" from 0 to 1 

  Uint8 alpha = progress * 255.0f; // SDL_SetTextureAlphaMode specifically wants Uint8

  TextureAsset login_panel = game.getTextureManager().getUITexture(UI::LOGIN_PANEL);
  SDL_SetTextureAlphaMod(login_panel.texture_, alpha);

  SDL_Rect rect;
  rect.w = login_panel.width_ * game.getScalingFactor();
  rect.h = login_panel.height_ * game.getScalingFactor();
  rect.x = (game.getWindowWidth() / 2) - (rect.w / 2);
  rect.y = (game.getWindowHeight() / 2) - (rect.h / 2);

  SDL_RenderCopy(game.getRenderer(), login_panel.texture_, nullptr, &rect);

}
