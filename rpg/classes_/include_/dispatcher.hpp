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

  
  public:
    // Constructor Destructor Copy Constructor
    Dispatcher() = default;
    Dispatcher(const Dispatcher& copy) = delete;
    ~Dispatcher() = default;

    // Getters
    const SDL_Keycode& getKeyCode() noexcept { return this->key_code_; }

    // Setters
    void setKeyCode(SDL_Keycode new_key_code) noexcept { this->key_code_ = new_key_code; }

    // Functions 
    bool detectingClick(int mouse_x, int mouse_y, ElementUI* element) noexcept;
};


#endif