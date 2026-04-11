#include "../include_/texture_manager.hpp"

void TextureManager::clear()
{
  for(auto& [id, texture_asset] : this->char_animations_)
  {
    if(texture_asset.texture_ != nullptr)
    {
      SDL_DestroyTexture(texture_asset.texture_);
      texture_asset.texture_ = nullptr;
    }
  }

  for(auto& [id, texture_asset] : this->ui_textures_)
  {
    if(texture_asset.texture_ != nullptr)
    {
      SDL_DestroyTexture(texture_asset.texture_);
      texture_asset.texture_ = nullptr;
    }
  }

  for(auto& [id, texture_asset] : this->visual_effects_)
  {
    if(texture_asset.texture_ != nullptr)
    {
      SDL_DestroyTexture(texture_asset.texture_);
      texture_asset.texture_ = nullptr;
    }
  }
}

TextureManager::TextureManager(SDL_Renderer* new_renderer) 
{ 
  this->main_renderer_ = new_renderer;
  loadCharAnimations();
  loadUITextures();
  loadVisualEffects();
  loadFloorTextures();
  enableBlendModeUI();


}
TextureManager::~TextureManager() { this->clear(); }

void TextureManager::enableBlendMode(const TextureAsset& asset)
{
  SDL_SetTextureBlendMode(asset.texture_, SDL_BLENDMODE_BLEND);
}

SDL_Texture* TextureManager::loadTexture(const std::string& path)
{
  SDL_Surface* surface = IMG_Load(path.c_str());
  if(surface == nullptr)
  {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->main_renderer_, surface);
  return texture;
}

TextureAsset TextureManager::makeTextureAsset(const std::string& path)
{
  SDL_Texture* texture = loadTexture(path);
  if(texture == nullptr)
  {
    std::cout << " texture failed !\n";
    return {};
  }

  TextureAsset placeholder;
  placeholder.height_ = 0;
  placeholder.width_ = 0;
  placeholder.texture_ = texture;

  SDL_QueryTexture(placeholder.texture_, nullptr, nullptr, &placeholder.width_, &placeholder.height_);

  return placeholder;

}
// #include "../../photos_/player_classes_/"
void TextureManager::loadCharAnimations()
{
  this->char_animations_[CharacterAnimationState::TEMPLAR_IDLE] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_idle_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_ONE] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_attack_one_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_TWO] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_attack_two_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_THREE] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_attack_three_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_BLOCK] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_block_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_HURT] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_hurt_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_DEATH] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_death_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_WALK_ONE] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_walk_one_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_WALK_TWO] = makeTextureAsset("../../photos_/player_classes_/templar_/templar_walk_two_.png");

  this->char_animations_[CharacterAnimationState::WIZARD_IDLE] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_idle_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_HURT] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_hurt_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_ICICLE_ATTACK] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_attack_one_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_FIREBALL_ATTACK] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_attack_two_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_DEATH] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_death_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_WALK] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_walk_.png");

  this->char_animations_[CharacterAnimationState::PRIEST_IDLE] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_idle_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_DEATH] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_death_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_HURT] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_hurt_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_WALK] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_walk_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_SMITE] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_attack_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_BASIC_HEAL] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_heal_.png");

  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_ONE] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_attack_one_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_TWO] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_attack_two_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_THREE] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_attack_three_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_IDLE] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_idle_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_HURT] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_hurt_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_DEATH] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_death_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_WALK] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_walk_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_BLOCK] = makeTextureAsset("../../photos_/player_classes_/knight_/knight_block_.png");
}

void TextureManager::loadUITextures()
{
  this->ui_textures_[UI::LOGIN_BACKGROUND] = makeTextureAsset("../../photos_/UI_/login_/background_for_login.png");
  this->ui_textures_[UI::LOGIN_PANEL] = makeTextureAsset("../../photos_/UI_/login_/login_panel_not_finished.png");
}

void TextureManager::loadVisualEffects()
{
  this->visual_effects_[VisualEffects::WIZARD_FIREBALL_EFFECT] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_attack_two_effect_.png");
  this->visual_effects_[VisualEffects::WIZARD_ICICLE_EFFECT] = makeTextureAsset("../../photos_/player_classes_/wizard_/wizard_attack_one_effect_.png");

  this->visual_effects_[VisualEffects::PRIEST_SMITE] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_attack_effect_.png");
  this->visual_effects_[VisualEffects::PRIEST_BASIC_HEAL] = makeTextureAsset("../../photos_/player_classes_/priest_/priest_heal_effect_.png");
}

void TextureManager::loadFloorTextures()
{
  this->floor_textures_[FloorType::PLAINS_GRASS] = makeTextureAsset("../../photos_/floors_/PlainsGrass.png");
  this->floor_textures_[FloorType::PLAINS_GRASS_WITH_LEAVES_ONE] = makeTextureAsset("../../photos_/floors_/PlainsGrassLeavesOne.png");

}


void TextureManager::enableBlendModeUI()
{
  enableBlendMode(this->ui_textures_[UI::LOGIN_PANEL]);
}