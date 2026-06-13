#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"
#include "../../namespaces_/namespaces.hpp"

class TextureManager
{
  private:
    SDL_Renderer* main_renderer_;

    std::unordered_map<CharacterAnimationState, TextureAsset> char_animations_;
    std::unordered_map<VisualEffects, TextureAsset> visual_effects_;
    std::unordered_map<UI, TextureAsset> ui_textures_;
    std::unordered_map<FloorType, TextureAsset> floor_textures_;

  public:

    // Constructor Destructor Copy Constructor
    TextureManager() = default;
    TextureManager(SDL_Renderer* new_renderer);
    TextureManager(const TextureManager& copy) = delete;
    ~TextureManager(); // Implement clearing out each map << !

    // Getters
    const TextureAsset& getCharAnimation(CharacterAnimationState placeholder) noexcept { return this->char_animations_.at(placeholder); }
    const TextureAsset& getVisualEffect(VisualEffects placeholder) noexcept { return this->visual_effects_.at(placeholder); }
    const TextureAsset& getUITexture(UI placeholder) noexcept { return this->ui_textures_.at(placeholder); }
    const TextureAsset& getFloorTexture(FloorType placeholder) noexcept { return this->floor_textures_.at(placeholder); }
    


    // Functions 
    SDL_Texture* loadTexture(const std::string& path) noexcept; 
    TextureAsset makeTextureAsset(const std::string& path) noexcept; // This is returned copied << !
    void enableBlendMode(const TextureAsset& asset) noexcept;
    
    

    // Loading PNGs
    void loadCharAnimations() noexcept;
    void loadVisualEffects() noexcept;
    void loadUITextures() noexcept;
    void loadFloorTextures() noexcept;

    // Making Certain PNG's BlendMode on
    void enableBlendModeUI() noexcept;

    void clear() noexcept;

};


#endif
