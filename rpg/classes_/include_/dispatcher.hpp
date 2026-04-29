#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"

class ElementUI;

class Dispatcher
{
  private:
    SDL_Keycode key_code_;
    Uint8 mouse_button_;
    int mouse_x_;
    int mouse_y_;

    bool shift_held_;
    bool control_held_;

  
  public:
    // Constructor Destructor Copy Constructor
    Dispatcher() = default;
    Dispatcher(const Dispatcher& copy) = delete;
    ~Dispatcher() = default;

    // Getters
    const SDL_Keycode& getKeyCode() noexcept { return this->key_code_; }
    const Uint8& getMouseButton() noexcept { return this->mouse_button_; }
    const bool getShiftHeld() noexcept { return this->shift_held_; }
    const bool getControlHeld() noexcept { return this->control_held_; }
    const int getMouseX() noexcept { return this->mouse_x_; }
    const int getMouseY() noexcept { return this->mouse_y_; }


    // Setters
    void setKeyCode(SDL_Keycode new_key_code) noexcept { this->key_code_ = new_key_code; }
    void setShiftHeld(bool new_status) noexcept { this->shift_held_ = new_status; }
    void setControlHeld(bool new_status) noexcept { this->control_held_ = new_status; }
    void setMouseButton(Uint8 new_mouse_button) noexcept { this->mouse_button_ = new_mouse_button; }
    void setMouseX(int new_mouse_x ) noexcept { this->mouse_x_ = new_mouse_x; }
    void setMouseY(int new_mouse_y ) noexcept { this->mouse_y_ = new_mouse_y; }

    // Functions 
    bool detectingClick(int mouse_x, int mouse_y, ElementUI* element) noexcept;
};


#endif