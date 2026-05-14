#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"
#include "../../namespaces_/namespaces.hpp"

class ElementUI;

class Dispatcher
{
  private:
    std::queue<KeyboardInput*> input_queue_;
    Uint8 mouse_button_;
    int mouse_x_;
    int mouse_y_;


  
  public:
    // Constructor Destructor Copy Constructor
    Dispatcher() = default;
    Dispatcher(const Dispatcher& copy) = delete;
    ~Dispatcher() = default;

    // Getters
    const Uint8& getMouseButton() noexcept { return this->mouse_button_; }
    const int getMouseX() noexcept { return this->mouse_x_; }
    const int getMouseY() noexcept { return this->mouse_y_; }
    std::queue<KeyboardInput*>& getInputQueue() noexcept { return this->input_queue_; }



    // Setters
    void setMouseButton(Uint8 new_mouse_button) noexcept { this->mouse_button_ = new_mouse_button; }
    void setMouseX(int new_mouse_x ) noexcept { this->mouse_x_ = new_mouse_x; }
    void setMouseY(int new_mouse_y ) noexcept { this->mouse_y_ = new_mouse_y; }
    void setInputQueue(std::queue<KeyboardInput*> new_queue) noexcept { this->input_queue_ = new_queue; }


    // Functions 
    bool detectingClick(int mouse_x, int mouse_y, ElementUI* element) noexcept;
};


#endif