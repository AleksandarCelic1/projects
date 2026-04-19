#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(Game& game) : State(game.getRenderer())
{
  this->validator_ = new LoginValidator();

  
  this->time_passed_ = 0.0f;
  this->panel_delay_ = 3.0f;
  this->smooth_duration_ = 1.0f;

  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();


  // Scale
  this->ui_elements_[LoginUI::LOGIN_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::LOGIN_BACKGROUND), game.getScalingFactor());
  this->ui_elements_[LoginUI::LOGIN_PANEL] = new ElementUI(game.getTextureManager()->getUITexture(UI::LOGIN_PANEL), game.getScalingFactor());



  // Assign Correct (X,Y)
  ElementUI* panel = this->ui_elements_[LoginUI::LOGIN_PANEL];  
  
  panel->setX(this->centerX(0, screen_width, panel->getW()));
  panel->setY(this->centerY(0, screen_height, panel->getH()));

  



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

void LoginState::renderBackground(Game& game) noexcept
{
  ElementUI* placeholder = this->ui_elements_[LoginUI::LOGIN_BACKGROUND];
  SDL_Rect copy = placeholder->getRect();
  SDL_RenderCopy(game.getRenderer(), placeholder->getTexture(), nullptr, &copy);

  // nullprt for SRC rect means -> that we take a specific part of the texture and then render 
  // it with DST rect and DST holds x,y,w,h if we do nullprt for SRC we just use the entire Texture
}

void LoginState::updateTimePassed(Game& game) noexcept
{
  this->time_passed_ += game.getDeltaTime();
}

void LoginState::renderLoginPanel(Game& game) noexcept
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

  ElementUI* placeholder = this->ui_elements_[LoginUI::LOGIN_PANEL];
  SDL_SetTextureAlphaMod(placeholder->getTexture(), alpha);
  SDL_RenderCopy(game.getRenderer(), placeholder->getTexture(), nullptr, &placeholder->getRect());

}

void LoginState::dispatch(Game& game) 
{
  const SDL_Keycode& keycode = game.getDispatcher()->getKeyCode();


  // press K -> goes here -> sees whats selected/which one is active 
  // -> goes to update username or password!


}

void LoginState::setPassword(PasswordField* new_password) noexcept
{
  if(new_password == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setPassword] -> new_password object is null < ! >" << std::endl;
    return;
  }

  if(this->password_ != nullptr)
  {
    delete this->password_;
    this->password_ = nullptr;
  }

  this->password_ = new_password;
}

void LoginState::setUsername(TextField* new_username) noexcept
{
  if(new_username == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setUsername] -> new_username object is null < ! >" << std::endl;
    return;
  }

  if(this->username_ != nullptr)
  {
    delete this->username_;
    this->username_ = nullptr;
  }

  this->username_= new_username;

}

