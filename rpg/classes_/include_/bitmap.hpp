#ifndef BITMAP_HPP
#define BITMAP_HPP

#include "glyph.hpp"
#include "../../namespaces_/namespaces.hpp"

class BitMap
{
  private:
    SDL_Texture* bitmap_;
    std::unordered_map<char, Glyph*> glyphs_;
  
  public:
    // Constructor Destructor Copy Constructor
    BitMap() = default;
    BitMap(SDL_Texture* bitmap);
    BitMap(const BitMap& copy) = delete;
    ~BitMap();

    // Getters
    SDL_Texture* getTexture() const noexcept { return this->bitmap_; }
    Glyph* getGlyph(char placeholder) const;

    // Setters
    void setGlyph(char key, Glyph* value) noexcept { this->glyphs_.insert({key, value}); }
    void setTexture(SDL_Texture* new_texture) noexcept { this->bitmap_ = new_texture; }

    // Functions

};



#endif