#ifndef LOGIN_PANEL_HPP
#define LOGIN_PANEL_HPP


#include "elementUI.hpp"
#include "text_field.hpp"
#include "password_field.hpp"


class LoginPanel : virtual public ElementUI
{
  private:
    TextField* username_login_;
    TextField* username_registration_;
    PasswordField* password_login_;
    PasswordField* password_registration_;
    PasswordField* password_confirmation_;

    TextField* currently_selected_;
  public:

    // Constructor Copy Constructor Destructor
    LoginPanel() = default;
    LoginPanel(const TextureAsset& asset, int scaling_factor);
    LoginPanel(const LoginPanel& copy ) = delete;
    ~LoginPanel() = default;

    // Getters
    TextField* getUsernameLogin() noexcept { return this->username_login_; }
    TextField* getUsernameRegistration() noexcept { return this->username_registration_; }
    PasswordField* getPasswordLogin() noexcept { return this->password_login_; }
    PasswordField* getPasswordRegistration() noexcept { return this->password_registration_; }
    PasswordField* getPasswordConfirmation() noexcept { return this->password_confirmation_; }
    TextField* getActiveField() noexcept { return this->currently_selected_; }

    // Setters
    void setUsernameLogin(TextField* new_username_login ) noexcept;
    void setUsernameRegistration(TextField* new_username_registartion) noexcept;
    void setPasswordLogin(PasswordField* new_password) noexcept;
    void setPasswordRegistration(PasswordField* new_password_registration) noexcept;
    void setPasswordConfirmation(PasswordField* new_password_confirmation) noexcept;
    void setActiveField(TextField* new_selected_field) noexcept;

  
};


#endif