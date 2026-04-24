#include "../include_/login_panel.hpp"



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

