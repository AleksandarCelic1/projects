#include "../include_/login_panel.hpp"
#include "../include_/game.hpp"

LoginPanel::LoginPanel(const TextureAsset& asset, int scaling_factor) : ElementUI(asset, scaling_factor) 
{
  this->time_passed_ = 0.0f;
  this->panel_delay_ = 3.0f;
  this->smooth_duration_ = 1.0f;

};

void LoginPanel::setUsernameLogin(TextField* new_username) noexcept
{
  if(new_username == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setUsernameLogin] -> new_username object is null < ! >" << std::endl;
    return;
  }

  if(this->username_login_ != nullptr)
  {
    delete this->username_login_;
    this->username_login_= nullptr;
  }

  this->username_login_= new_username;

}

void LoginPanel::setUsernameRegistration(TextField* new_username) noexcept
{
  if(new_username == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setUsernameRegistration] -> new_username object is null < ! >" << std::endl;
    return;
  }

  if(this->username_registration_ != nullptr)
  {
    delete this->username_registration_;
    this->username_registration_= nullptr;
  }

  this->username_registration_= new_username;

}


void LoginPanel::setPasswordLogin(PasswordField* new_password) noexcept
{
  if(new_password == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setPasswordLogin] -> new_password object is null < ! >" << std::endl;
    return;
  }

  if(this->password_login_ != nullptr)
  {
    delete this->password_login_;
    this->password_login_ = nullptr;
  }

  this->password_login_ = new_password;
}


void LoginPanel::setPasswordRegistration(PasswordField* new_password) noexcept
{
  if(new_password == nullptr)
  {
    std::cout << "[FAIL] -> [LoginState::setPasswordRegistration] -> new_password object is null < ! >" << std::endl;
    return;
  }

  if(this->password_registration_ != nullptr)
  {
    delete this->password_registration_;
    this->password_registration_ = nullptr;
  }

  this->password_registration_ = new_password;
}

void LoginPanel::setPasswordConfirmation(PasswordField* new_password) noexcept
{
  if(new_password == nullptr)
  {
    std::cout << "[FAIL] -> [LoginPanel::setPasswordConfirmation] -> new_password object is null < ! >" << std::endl;
    return;
  }

  if(this->password_confirmation_ != nullptr)
  {
    delete this->password_confirmation_;
    this->password_confirmation_ = nullptr;
  }

  this->password_confirmation_ = new_password;
}

void LoginPanel::render(Game& game) noexcept
{
  this->renderPanel(game);
  // Render the five  
}


void LoginPanel::renderPanel(Game& game) noexcept
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

  SDL_SetTextureAlphaMod(this->getTexture(), alpha);
  SDL_RenderCopy(game.getRenderer(), this->getTexture(), nullptr, &this->getRect());
}