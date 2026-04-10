#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "state.hpp"

class LoginState : virtual public State
{
  private:
  // Maybe connection to Account 
  // should parse the username and password 
  // then probably go to accountVERIFICATIOR and whatnot 
  // if succeeeds open account from sql if not retry 
  // figure out some mecanisum if somoene tries password multiple times and it doesnt work
    


  public:
    // Constructor Destructor Copy Constructor
    LoginState() = default;
    LoginState(SDL_Renderer* main_renderer);      
    LoginState(const LoginState& copy) = delete;
    ~LoginState() = default;


    // Functions
    void render(Game& game) override;
    void update(Game& game) override;

    // Mini Render Functions
    void renderBackground(Game& game) noexcept;

};

#endif