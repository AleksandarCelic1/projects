#include "../include_/login_validator.hpp"


void LoginValidator::validate(Game& game, const std::string& username, const std::string& password)
{ 
  UsernamePasswordConstraints constraints;
  UsernamePasswordSizes sizes;



}

bool LoginValidator::validateUsername(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  // if into if and to see which one specifically fails dont run them all << ! >> 
}

bool LoginValidator::validatePassword(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{

}

bool LoginValidator::validateUsernameSize(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{

}

bool LoginValidator::validateUsernameSpecialChars(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{

}

bool LoginValidator::validatePasswordLowerCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{

}

bool LoginValidator::validatePasswordUpperCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  
}

bool LoginValidator::validatePasswordNumber(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  
}

bool LoginValidator::validatePasswordSpecialCharacter(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes)
{
  
}

