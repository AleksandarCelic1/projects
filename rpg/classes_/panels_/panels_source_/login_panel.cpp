#include "../panels_include_/login_panel.hpp"
#include "../../include_/game.hpp"

LoginPanel::LoginPanel(std::unordered_map<Offsets, std::pair<int,int>>& map, const TextureAsset& asset, int scaling_factor)
 : Panel(asset, scaling_factor, 0.0f, 3.0f, 1.0f) 
{
  const SDL_Rect& dst_rect = this->getDstRect();

  this->username_login_ = new TextField( { dst_rect.x, dst_rect.y }, map.at(Offsets::LOGIN_USERNAME), scaling_factor, TextPlaceholderType::LOGIN_PLACEHOLDER);
  this->username_registration_ = new TextField( {dst_rect.x , dst_rect.y }, map.at(Offsets::REGISTRATION_USERNAME), scaling_factor, TextPlaceholderType::LOGIN_PLACEHOLDER);
  this->password_login_ = new PasswordField( { dst_rect.x, dst_rect.y }, map.at(Offsets::LOGIN_PASSWORD), scaling_factor, TextPlaceholderType::LOGIN_PLACEHOLDER);
  this->password_registration_ = new PasswordField( { dst_rect.x, dst_rect.y }, map.at(Offsets::REGISTRATION_PASSWORD), scaling_factor, TextPlaceholderType::LOGIN_PLACEHOLDER);
  this->password_confirmation_ = new PasswordField( { dst_rect.x, dst_rect.y }, map.at(Offsets::REGISTRATION_PASSWORD_CONFIRMATION), scaling_factor, TextPlaceholderType::LOGIN_PLACEHOLDER);
  this->currently_selected_ = nullptr;

};

LoginPanel::~LoginPanel()
{  
  MemoryFreeingUtils::clearPointer(this->username_login_);
  MemoryFreeingUtils::clearPointer(this->username_registration_);
  MemoryFreeingUtils::clearPointer(this->password_login_);
  MemoryFreeingUtils::clearPointer(this->password_confirmation_);
  MemoryFreeingUtils::clearPointer(this->password_registration_);
}

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
  /* Handle Panel rendering */
  this->renderPanel(game);

  /* Handle Kids rendering */
  
  if(this->username_login_->getActive()) { this->username_login_->render(game); }
  if(this->username_registration_->getActive()) { this->username_registration_->render(game); }
  if(this->password_login_->getActive()) { this->password_login_->render(game); }
  if(this->password_registration_->getActive()) { this->password_registration_->render(game); }
  if(this->password_confirmation_->getActive()) { this->password_confirmation_->render(game); }
  

}

void LoginPanel::update(Game& game) noexcept
{
  /* Handle Panel update timers */
  this->setTimePassed(this->getTimePassed() + game.getDeltaTime());

  /* Handle Kids update timers */
  this->username_login_->update(game);
  this->password_login_->update(game);
  this->username_registration_->update(game);
  this->password_registration_->update(game);
  this->password_confirmation_->update(game);
}


void LoginPanel::setActiveField(TextField* new_active_field) noexcept
{
  if(this->currently_selected_ == new_active_field)
  {
    return;
  }

  
  this->currently_selected_ = new_active_field;
  if(this->currently_selected_ != nullptr)
  {
    this->currently_selected_->setActive(true);
  }
}

