#include "button.hpp"

Button::Button()
{
  this->x_ = 0;
  this->y_ = 0;
  this->w_ = 0;
  this->h_ = 0;
  this->item_ = nullptr;
}

Button::Button(const Button& copy) 
{
  this->x_ = copy.x_;
  this->y_ = copy.y_;
  this->h_ = copy.h_;
  this->w_ = copy.w_;

  this->item_ = copy.item_; // Shallow Copy! destructor checks if its a nullptr before deleting it
}

Button::~Button()
{
  if(this->item_ != nullptr)
  {
    delete this->item_;
    this->item_ = nullptr;
  }
}