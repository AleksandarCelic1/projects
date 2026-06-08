#ifndef LOGIN_PANEL_HPP
#define LOGIN_PANEL_HPP

#include "../../include_/panel.hpp"
#include "../../include_/text_field.hpp"
#include "../../include_/password_field.hpp"

class Game;


class LoginPanel : public Panel
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
    LoginPanel(std::unordered_map<Offsets, std::pair<int,int>>& map, const TextureAsset& asset, int scaling_factor);
    LoginPanel(const LoginPanel& copy ) = delete;
    ~LoginPanel();

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

    // Functions 
    void render(Game& game) noexcept override;
    void update(Game& game) noexcept override;
    void renderPanel(Game& game) noexcept override;   

  
};


#endif