#ifndef ELEMENT_UI_HPP
#define ELEMENT_UI_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"


class ElementUI
{
  private:
    SDL_Texture* texture_; // Cant modify the values, meaning we dont have to destroy it << ! >> 
    SDL_Rect dst_rect_;

  public:
    ElementUI() = default; 
    ElementUI(const TextureAsset& asset, int scaling_factor);
    ElementUI(const ElementUI& copy) = delete;
    ~ElementUI() = default; 

    // Getters
    SDL_Texture* getTexture() const { return this->texture_; }
    int getX() const { return this->dst_rect_.x; }
    int getY() const { return this->dst_rect_.y; }
    int getW() const { return this->dst_rect_.w; }
    int getH() const { return this->dst_rect_.h; }

    const SDL_Rect& getRect() { return this->dst_rect_; }

    // Setters
    void setTexture(SDL_Texture* ptr) noexcept { this->texture_ = ptr; }
    void setX(int new_x) noexcept { this->dst_rect_.x = new_x; }
    void setY(int new_y) noexcept { this->dst_rect_.y = new_y; }
    void setW(int new_w) noexcept { this->dst_rect_.w = new_w; }
    void setH(int new_h) noexcept { this->dst_rect_.h = new_h; }
    void setRect(SDL_Rect& new_rect) noexcept { this->dst_rect_ = new_rect; }
    
    // Functions
    bool detectMouseClick(int mouse_x, int mouse_y) noexcept;
  
  
};

#endif