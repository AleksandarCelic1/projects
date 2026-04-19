#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "state.hpp"
#include "login_validator.hpp"
#include "elementUI.hpp"
#include "text_field.hpp"
#include "password_field.hpp"

class LoginState : virtual public State
{
  private:
    LoginValidator* validator_;
    TextField* username_;
    PasswordField* password_;



    
    
    // Login Panel Delay < ! > 
    float time_passed_;
    float panel_delay_;
    float smooth_duration_;

    // Local map to known UI elements
    std::unordered_map<LoginUI, ElementUI*> ui_elements_;

  // Maybe connection to Account 
  // should parse the username and password 
  // then probably go to accountVERIFICATIOR and whatnot 
  // if succeeeds open account from sql if not retry 
  // figure out some mecanisum if somoene tries password multiple times and it doesnt work
    


  public:
    // Constructor Destructor Copy Constructor
    LoginState() = default;
    LoginState(Game& game);      
    LoginState(const LoginState& copy) = delete;
    ~LoginState() = default;

    // Getters
    LoginValidator* getValidator() noexcept { return this->validator_; }
    TextField* getUsername() noexcept { return this->username_; }
    PasswordField* getPassword() noexcept { return this->password_; }

    // Setters
    void setValidator(LoginValidator* new_validator) noexcept { this->validator_ = new_validator; }
    void setUsername(TextField* new_username ) noexcept;
    void setPassword(PasswordField* new_password) noexcept;


    // Functions
    void dispatch(Game& game) override;
    void render(Game& game) override;
    void update(Game& game) override;

    // Mini Update Functions
    void updateTimePassed(Game& game) noexcept;

    // Mini Render Functions
    void renderBackground(Game& game) noexcept;
    void renderLoginPanel(Game& game) noexcept;

};

#endif