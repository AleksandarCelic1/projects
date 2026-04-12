#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "state.hpp"

class LoginState : virtual public State
{
  private:
    
    // Login Panel Delay < ! > 
    float time_passed_;
    float panel_delay_;
    float smooth_duration_;

    // Local map to known UI elements
    std::unordered_map<LoginUI, ElementUI> ui_elements_;

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


    // Functions
    void render(Game& game) override;
    void update(Game& game) override;

    // Mini Update Functions
    void updateTimePassed(Game& game) noexcept;

    // Mini Render Functions
    void renderBackground(Game& game) noexcept;
    void renderLoginPanel(Game& game) noexcept;

};

#endif