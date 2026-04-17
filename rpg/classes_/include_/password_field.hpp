#ifndef PASSWORD_FIELD_HPP
#define PASSWORD_FIELD_HPP

#include "text_field.hpp"

class PasswordField : virtual public TextField
{
  private:
    std::string password_;

  public:
    // Constructor Destructor Copy Constructor
    PasswordField() = default;
    PasswordField(const PasswordField& copy ) = delete;
    ~PasswordField() = default;

    // Getters
    std::string getPasswordConst() const noexcept { return this->password_; }
    std::string& getPasswordModifiable() noexcept { return this->password_; }

    // Setter
    void setPassword(std::string& new_string) noexcept { this->password_ = new_string; }

    // Functions
    std::string getPasswordForRendering() noexcept;
};


#endif