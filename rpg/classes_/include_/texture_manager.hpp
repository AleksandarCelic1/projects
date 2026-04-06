#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"

class TextureManager
{
  private:
    SDL_Renderer* main_renderer_;

    std::unordered_map<CharacterAnimationState, SDL_Texture*> char_animations_;
    std::unordered_map<VisualEffects, SDL_Texture*> visual_effects_;
    std::unordered_map<UI, SDL_Texture*> ui_textures_;

  public:

    // Constructor Destructor Copy Constructor
    TextureManager(SDL_Renderer* new_renderer);
    TextureManager(const TextureManager& copy) = delete;
    ~TextureManager(); // Implement clearing out each map << !

    // Getters
    SDL_Texture* getCharAnimation(CharacterAnimationState& placeholder) noexcept { return this->char_animations_[placeholder]; }
    SDL_Texture* getVisualEffect(VisualEffects& placeholder) noexcept { return this->visual_effects_[placeholder]; }
    SDL_Texture* getUITexture(UI& placeholder) noexcept { return this->ui_textures_[placeholder]; }
    


    // Functions 
    SDL_Texture* loadTexture(const std::string& path) noexcept; 
    void loadCharAnimations() noexcept;
    void loadVisualEffects() noexcept;
    void loadUITextures() noexcept;
    void clear() noexcept;

};


#endif
