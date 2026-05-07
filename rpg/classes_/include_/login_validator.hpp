#ifndef LOGIN_VALIDATOR_HPP
#define LOGIN_VALIDATOR_HPP

#include "input_validator.hpp"


class LoginValidator : virtual public InputValidator
{
  private:


  public:
    // Constructor Copy Constructor Destructor
    LoginValidator() = default; // check
    LoginValidator(const LoginValidator& copy) = delete;
    ~LoginValidator() = default; //check

    // Functions
    bool validate(Game& game, const std::string& username, const std::string& password) override;
    bool validateRegistration(Game& game, const std::string& username, const std::string& password, const std::string& confirmation_password) noexcept;

    
    bool validateUsername(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePassword(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;

    // Username
    bool validateUsernameSize(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validateUsernameSpecialChars(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validateUsernameSpaces(const std::string& username, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;

    // Password
    bool validatePasswordSize(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordLowerCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordUpperCase(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordNumber(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordSpecialCharacter(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordSpaces(const std::string& password, UsernamePasswordConstraints& constraints, UsernamePasswordSizes& sizes) noexcept;
    bool validatePasswordConfirmation(const std::string& password, const std::string& confirmation_password) noexcept;



  
};

#endif