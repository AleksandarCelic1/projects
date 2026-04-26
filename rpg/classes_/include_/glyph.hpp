#ifndef GLYPH_HPP
#define GLYPH_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"

class Glyph
{
  private:
    SDL_Rect src_rect_;
    int scaled_width_;
    int scaled_height_;

  public:
    // Constructor Destructor Copy Constructor
    Glyph() = default;
    Glyph(const Glyph& copy) = delete;
    ~Glyph() = default;


    // Getters
    const SDL_Rect& getRect()  noexcept { return this->src_rect_; }
    int getWidth() const noexcept { return this->scaled_width_; }
    int getHeight() const noexcept { return this->scaled_height_; }

    // Setters
    void setRect(SDL_Rect& new_rect) noexcept { this->src_rect_ = new_rect; }
    void setWidth(int new_width) noexcept { this->scaled_width_ = new_width; }
    void setHeight(int new_height) noexcept { this->scaled_height_ = new_height; }

    // Functions
    
};



#endif