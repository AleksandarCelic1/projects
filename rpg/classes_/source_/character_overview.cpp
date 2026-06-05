#include "../include_/character_overview.hpp"
#include "../include_/game.hpp"

CharacterOverviewState::CharacterOverviewState(Game& game)
{
  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();

  // Scale
  this->ui_elements_[CharacterOverviewUI::OVERVIEW_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::CHARACTER_OVERVIEW_BACKGROUND), game.getScalingFactor());



};



CharacterOverviewState::~CharacterOverviewState()
{
  /* clearing */
  std::vector<ElementUI*> placeholder(this->characters_.size());
  for(auto iterator : this->characters_)
  {
    placeholder.push_back(iterator.first);
  }

  MemoryFreeingUtils::clearMap(this->characters_);
  MemoryFreeingUtils::clearMap(this->ui_elements_);
  MemoryFreeingUtils::clearVector(placeholder);
  
}

Character* CharacterOverviewState::getCharacter(ElementUI* key) noexcept
{
  Character* retval = static_cast<Character*>(ExceptionHandler::get(this->characters_, key));
  return retval;
}