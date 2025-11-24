#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "item.hpp"

class Button
{

  private:
    int x_;
    int y_;
    int h_;
    int w_;
    Item* item_;
  public:
    Button();
    Button(const Button& copy);
    ~Button();

    // Getters 

    int getX() const { return this->x_;}
    int getY() const { return this->y_;}
    int getH() const { return this->h_;}
    int getW() const { return this->w_;}
    Item* getItem() const { return this->item_;}

    // Setters

    void setX(int x) { this->x_ = x;}
    void setY(int y) { this->y_ = y;}
    void setH(int h) { this->h_ = h;}
    void setW(int w) { this->w_ = w;}
    void setItem(Item* new_item) {this->item_ = new_item;}




};


#endif