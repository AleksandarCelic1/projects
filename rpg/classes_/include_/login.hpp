#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "state.hpp"
#include "login_validator.hpp"
#include "elementUI.hpp"
#include "login_panel.hpp"

#include "../../constants_/constants.hpp"

class LoginState : virtual public State
{
  private:
    LoginValidator* validator_;
    LoginPanel* panel_;

  
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
    LoginPanel* getPanel() noexcept { return this->panel_; }
    
    // Setters
    void setValidator(LoginValidator* new_validator) noexcept { this->validator_ = new_validator; }
    void setPanel(LoginPanel* new_panel) noexcept { this->panel_ = new_panel; }
    
    // Functions
    void dispatchKeyboardInput(Game& game) override;
    void dispatchMouseInput(Game& game) override;
    void render(Game& game) override;
    void update(Game& game) override;

    // Mini Update Functions
    void updatePanelTimePassed(Game& game) noexcept;

    // Mini Render Functions
    void renderBackground(Game& game) noexcept;
    

};

#endif