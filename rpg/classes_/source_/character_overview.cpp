#include "../include_/character_overview.hpp"
#include "../include_/game.hpp"

CharacterOverviewState::CharacterOverviewState(Game& game)
{
  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();

  // Scale
  this->ui_elements_[CharacterOverviewUI::OVERVIEW_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::CHARACTER_OVERVIEW_BACKGROUND), game.getScalingFactor());


  // Panel
  this->panel_ = new CharacterOverviewPanel(this->getOffsetMap(), game.getTextureManager()->getUITexture(UI::CHARACTER_OVERVIEW_PANEL), game.getScalingFactor());
  panel_->setX(this->centerX(0, screen_width, panel_->getW()));
  panel_->setY(this->centerY(0, screen_height, panel_->getH()));


};

CharacterOverviewState::~CharacterOverviewState()
{
  /* clearing */
  MemoryFreeingUtils::clearPointer(this->panel_);
  MemoryFreeingUtils::clearMap(this->ui_elements_);
}


void CharacterOverviewState::dispatchKeyboardInput(Game& game)
{

}


void CharacterOverviewState::dispatchMouseInput(Game& game) 
{

}

void CharacterOverviewState::render(Game& game) 
{

}

void CharacterOverviewState::update(Game& game) 
{

}

void CharacterOverviewState::initializeUIOffsets(Game& game)
{
  int scaling_factor = game.getScalingFactor();

  
  std::unordered_map<Offsets, std::pair<int, int>>& map = this->getOffsetMap();

  /* Offset 141, 117 is NOT correct, find out which offset is for those 7 text placeholders <!> */

  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_ONE, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_TWO, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_THREE, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_FOUR, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_FIVE, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_SIX, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::CHAROVERVIEW_PLACEHOLDER_SEVEN, { 141 * scaling_factor, 117 * scaling_factor }});


}


void CharacterOverviewState::handleEnter(Game& game)
{

}

