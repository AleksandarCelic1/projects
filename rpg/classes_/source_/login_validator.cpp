#include "../include_/login_validator.hpp"


void LoginValidator::validate(Game& game, const std::string& username, const std::string& password)
{ 
  UsernamePasswordConstraints constraints;
  UsernamePasswordSizes sizes;

  if(this->validateUsername(username, constraints, sizes) && this->validatePassword(password, constraints, sizes))
  {
    // try to log in -- > auth via database
  }


}

bool LoginValidator::validateUsername(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validatePassword(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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


bool LoginValidator::validateUsernameSize(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validateUsernameSpecialChars(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validateUsernameSpaces(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  if(username.find(' ') != std::string::npos)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePasswordLowerCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validatePasswordUpperCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validatePasswordNumber(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validatePasswordSpecialCharacter(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

bool LoginValidator::validatePasswordSpaces(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  if(password.find(' ') != std::string::npos)
  {
    return false;
  }

  return true;
}

bool LoginValidator::validatePasswordSize(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
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

