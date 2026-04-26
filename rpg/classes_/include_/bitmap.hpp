#ifndef BITMAP_HPP
#define BITMAP_HPP

#include "glyph.hpp"

class BitMap
{
  private:
    std::unordered_map<char, Glyph*> glyphs_;
  
  public:
    // Constructor Destructor Copy Constructor
    BitMap() = default;
    BitMap(SDL_Texture* bitmap);
    BitMap(const BitMap& copy) = delete;
    ~BitMap();

    // Getters
    Glyph* getGlyph(char placeholder) const { return this->glyphs_.at(placeholder); }

    // Setters
    void setGlyph(char key, Glyph* value) noexcept { this->glyphs_.insert({key, value}); }

    // Functions

};



#endif