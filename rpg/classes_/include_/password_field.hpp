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
    PasswordField(std::pair<int, int> coords, std::pair<int,int> offsets, int scaling_factor);
    PasswordField(const PasswordField& copy ) = delete;
    ~PasswordField() = default;

    // Getters
    std::string getPasswordConst() const noexcept { return this->password_; }
    std::string& getPasswordModifiable() noexcept { return this->password_; }

    // Setter
    void setPassword(std::string& new_string) noexcept { this->password_ = new_string; }

    // Functions
    void render(Game& game) noexcept override;
    void update(Game& game) noexcept override;
    void rebuildText(Game& game) noexcept override;

};


#endif