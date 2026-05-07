#include "../include_/login_validator.hpp"

bool LoginValidator::validate(Game& game, const std::string& username, const std::string& password)
{ 
  UsernamePasswordConstraints constraints;
  UsernamePasswordSizes sizes;

  bool result = false;

  result = (this->validateUsername(username, constraints, sizes) && this->validatePassword(password, constraints, sizes));

  return result;

}

bool LoginValidator::validateRegistration(Game& game, const std::string& username, const std::string& password, const std::string& confirmation_password) noexcept
{
  if(!validate(game, username, password))
  {
    return false;
  }

  if(!validatePasswordConfirmation(password, confirmation_password))
  {
    return false;
  }

  return true;
}


bool LoginValidator::validateUsername(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  // make error printfs << ! >> 
  if(!this->validateUsernameSize(username, constraints, sizes))
  {
    return false;
  }

  if(!this->validateUsernameSpecialChars(username, constraints, sizes))
  {
    return false;
  }

  if(!this->validateUsernameSpaces(username, constraints, sizes))
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePassword(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  if(!this->validatePasswordSize(password, constraints, sizes))
  {
    return false;
  }

  if(!this->validatePasswordLowerCase(password, constraints, sizes))
  {
    return false;
  }

  if(!this->validatePasswordNumber(password, constraints, sizes))
  {
    return false;
  }

  if(!this->validatePasswordUpperCase(password, constraints, sizes))
  {
    return false;
  }

  if(!this->validatePasswordSpaces(password, constraints, sizes))
  {
    return false;
  }

  if(!this->validatePasswordSpecialCharacter(password, constraints, sizes))
  {
    return false;
  }
  
  return true;

}


bool LoginValidator::validateUsernameSize(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  if(username.size() < sizes.username_min_)
  {
    return false;
  }

  if(username.size() > sizes.username_max_)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validateUsernameSpecialChars(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  int count = 0; 
  for(int index = 0; username.size(); index++)
  {
    if(ispunct(username.at(index)))
    {
      count++;
    }

    if(count > constraints.user_special_char)
    {
      return false;
    }
  }

  return true;
}

bool LoginValidator::validateUsernameSpaces(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  if(username.find(' ') != std::string::npos)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePasswordLowerCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  int count = 0; 
  for(int index = 0; index < password.size(); index++)
  {
    if(islower(password.at(index)))
    {
      count++;
    }

    if(count >= constraints.pass_lowercase_letter_)
    {
      return true;
    }
  }

  return false;
}

bool LoginValidator::validatePasswordUpperCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  int count = 0; 
  for(int index = 0; index < password.size(); index++)
  {
    if(isupper(password.at(index)))
    {
      count++;
    }

    if(count >= constraints.pass_uppercase_letter_)
    {
      return true;
    }
  }

  return false; 
}

bool LoginValidator::validatePasswordNumber(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  int count = 0; 
  for(int index = 0; index < password.size(); index++)
  {
    if(isnumber(password.at(index)))
    {
      count++;
    }

    if(count >= constraints.pass_number_)
    {
      return true;
    }
  }

  return false;
}

bool LoginValidator::validatePasswordSpecialCharacter(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  int count = 0; 
  for(int index = 0; index < password.size(); index++)
  {
    if(ispunct(password.at(index))) // ISPUNCT - - > [!"#$%&'()*+,-./, :;<=>?@, [\]^_`, {|}~]
    {
      count++;
    }

    if(count >= constraints.pass_special_char_)
    {
      return true;
    }
  }

  return false;
}

bool LoginValidator::validatePasswordSpaces(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  if(password.find(' ') != std::string::npos)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePasswordSize(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept
{
  if(password.size() < sizes.password_min_)
  {
    return false;
  }

  if(password.size() > sizes.password_max_)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePasswordConfirmation(const std::string& password, const std::string& confirmation_password) noexcept
{
  int password_size = password.size();
  int password_confirmation_size = confirmation_password.size();

  if(password_size != password_confirmation_size)
  {
    return false;
  }

  for(int index = 0; index < password_size; index++)
  {
    if(password.at(index) != confirmation_password.at(index))
    {
      return false;
    }
  }


  return true;
}