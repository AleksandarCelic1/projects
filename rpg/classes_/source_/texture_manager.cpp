#include "../include_/texture_manager.hpp"

void TextureManager::clear()
{
  for(auto& [id, texture] : this->char_animations_)
  {
    if(texture != nullptr)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }

  for(auto& [id, texture] : this->ui_textures_)
  {
    if(texture != nullptr)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }

  for(auto& [id, texture] : this->visual_effects_)
  {
    if(texture != nullptr)
    {
      SDL_DestroyTexture(texture);
      texture = nullptr;
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


}
TextureManager::~TextureManager() { this->clear(); }

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

// #include "../../photos_/player_classes_/"
void TextureManager::loadCharAnimations()
{
  this->char_animations_[CharacterAnimationState::TEMPLAR_IDLE] = loadTexture("../../photos_/player_classes_/templar_/templar_idle_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_ONE] = loadTexture("../../photos_/player_classes_/templar_/templar_attack_one_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_TWO] = loadTexture("../../photos_/player_classes_/templar_/templar_attack_two_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_ATTACK_THREE] = loadTexture("../../photos_/player_classes_/templar_/templar_attack_three_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_BLOCK] = loadTexture("../../photos_/player_classes_/templar_/templar_block_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_HURT] = loadTexture("../../photos_/player_classes_/templar_/templar_hurt_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_DEATH] = loadTexture("../../photos_/player_classes_/templar_/templar_death_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_WALK_ONE] = loadTexture("../../photos_/player_classes_/templar_/templar_walk_one_.png");
  this->char_animations_[CharacterAnimationState::TEMPLAR_WALK_TWO] = loadTexture("../../photos_/player_classes_/templar_/templar_walk_two_.png");

  this->char_animations_[CharacterAnimationState::WIZARD_IDLE] = loadTexture("../../photos_/player_classes_/wizard_/wizard_idle_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_HURT] = loadTexture("../../photos_/player_classes_/wizard_/wizard_hurt_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_ICICLE_ATTACK] = loadTexture("../../photos_/player_classes_/wizard_/wizard_attack_one_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_FIREBALL_ATTACK] = loadTexture("../../photos_/player_classes_/wizard_/wizard_attack_two_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_DEATH] = loadTexture("../../photos_/player_classes_/wizard_/wizard_death_.png");
  this->char_animations_[CharacterAnimationState::WIZARD_WALK] = loadTexture("../../photos_/player_classes_/wizard_/wizard_walk_.png");

  this->char_animations_[CharacterAnimationState::PRIEST_IDLE] = loadTexture("../../photos_/player_classes_/priest_/priest_idle_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_DEATH] = loadTexture("../../photos_/player_classes_/priest_/priest_death_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_HURT] = loadTexture("../../photos_/player_classes_/priest_/priest_hurt_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_WALK] = loadTexture("../../photos_/player_classes_/priest_/priest_walk_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_SMITE] = loadTexture("../../photos_/player_classes_/priest_/priest_attack_.png");
  this->char_animations_[CharacterAnimationState::PRIEST_BASIC_HEAL] = loadTexture("../../photos_/player_classes_/priest_/priest_heal_.png");

  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_ONE] = loadTexture("../../photos_/player_classes_/knight_/knight_attack_one_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_TWO] = loadTexture("../../photos_/player_classes_/knight_/knight_attack_two_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_ATTACK_THREE] = loadTexture("../../photos_/player_classes_/knight_/knight_attack_three_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_IDLE] = loadTexture("../../photos_/player_classes_/knight_/knight_idle_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_HURT] = loadTexture("../../photos_/player_classes_/knight_/knight_hurt_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_DEATH] = loadTexture("../../photos_/player_classes_/knight_/knight_death_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_WALK] = loadTexture("../../photos_/player_classes_/knight_/knight_walk_.png");
  this->char_animations_[CharacterAnimationState::KNIGHT_BLOCK] = loadTexture("../../photos_/player_classes_/knight_/knight_block_.png");
}

void TextureManager::loadUITextures()
{
  // Currently no UI 
  return;
}

void TextureManager::loadVisualEffects()
{
  this->visual_effects_[VisualEffects::WIZARD_FIREBALL_EFFECT] = loadTexture("../../photos_/player_classes_/wizard_/wizard_attack_two_effect_.png");
  this->visual_effects_[VisualEffects::WIZARD_ICICLE_EFFECT] = loadTexture("../../photos_/player_classes_/wizard_/wizard_attack_one_effect_.png");

  this->visual_effects_[VisualEffects::PRIEST_SMITE] = loadTexture("../../photos_/player_classes_/priest_/priest_attack_effect_.png");
  this->visual_effects_[VisualEffects::PRIEST_BASIC_HEAL] = loadTexture("../../photos_/player_classes_/priest_/priest_heal_effect_.png");
}

void TextureManager::loadFloorTextures()
{
  this->floor_textures_[FloorType::PLAINS_GRASS] = loadTexture("../../photos_/floors_/PlainsGrass.png");
  this->floor_textures_[FloorType::PLAINS_GRASS_WITH_LEAVES_ONE] = loadTexture("../../photos_/floors_/PlainsGrassLeavesOne.png");
  
}