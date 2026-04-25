#ifndef LOGIN_PANEL_HPP
#define LOGIN_PANEL_HPP


#include "elementUI.hpp"
#include "text_field.hpp"
#include "password_field.hpp"

class Game;


class LoginPanel : virtual public ElementUI
{
  private:
    TextField* username_login_;
    TextField* username_registration_;
    PasswordField* password_login_;
    PasswordField* password_registration_;
    PasswordField* password_confirmation_;

    TextField* currently_selected_;


    // Login Panel Delay < ! > 
    float time_passed_;
    float panel_delay_;
    float smooth_duration_;

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

    float getTimePassed() const noexcept { return this->time_passed_; }
    float getPanelDelay() const noexcept { return this->panel_delay_; }
    float getSmoothDuration() const noexcept { return this->smooth_duration_; }

    // Setters
    void setTimePassed(float new_time_passed) noexcept { this->time_passed_ = new_time_passed; } 
    void setPanelDelay(float new_panel_delay)  noexcept { this->panel_delay_ = new_panel_delay; }
    void setSmoothDuration(float new_smooth_duration) noexcept { this->smooth_duration_ = new_smooth_duration; }

    void setUsernameLogin(TextField* new_username_login ) noexcept;
    void setUsernameRegistration(TextField* new_username_registartion) noexcept;
    void setPasswordLogin(PasswordField* new_password) noexcept;
    void setPasswordRegistration(PasswordField* new_password_registration) noexcept;
    void setPasswordConfirmation(PasswordField* new_password_confirmation) noexcept;
    void setActiveField(TextField* new_selected_field) noexcept;

    // Functions 
    void render(Game& game) noexcept override;
    void renderPanel(Game& game) noexcept;    

  
};


#endif