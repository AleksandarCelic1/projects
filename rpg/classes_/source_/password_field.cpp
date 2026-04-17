#include "../include_/password_field.hpp"

std::string PasswordField::getPasswordForRendering() noexcept
{
  return std::string(this->password_.size(), '*');
}