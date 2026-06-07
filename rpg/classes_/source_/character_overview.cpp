#include "../include_/character_overview.hpp"
#include "../include_/game.hpp"

CharacterOverviewState::CharacterOverviewState(Game& game)
{
  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();

  initializeUIOffsets(game);

  // Scale
  this->ui_elements_[CharacterOverviewUI::OVERVIEW_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::CHARACTER_OVERVIEW_BACKGROUND), game.getScalingFactor());


  // Panel
  this->panel_ = new CharacterOverviewPanel(this->getOffsetMap(), game.getTextureManager()->getUITexture(UI::CHARACTER_OVERVIEW_PANEL), game.getScalingFactor());
  panel_->setX(this->centerX(0, screen_width, panel_->getW()));
  panel_->setY(this->centerY(0, screen_height, panel_->getH()));


  QuadTree* quad_tree = this->getQuadTree();
  std::unordered_map<ElementUI*, Character*> chars = panel_->getCharacterMappings();

  for(auto& iterator : chars)
  {
    quad_tree->insert(iterator.first);
  }
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
  this->renderBackground(game);
  this->panel_->render(game);
}

void CharacterOverviewState::update(Game& game) 
{

}

void CharacterOverviewState::initializeUIOffsets(Game& game)
{
  int scaling_factor = game.getScalingFactor();

  std::unordered_map<Offsets, std::pair<int, int>>& map = this->getOffsetMap();

  int char_placeholder_x = 241 * scaling_factor;
  int char_placeholder_y = 69 * scaling_factor;
  int y_offset = 30 * scaling_factor;

  /* If curious about 5 and 12 see Offsets enum class <!> */
  for(int index = 5; index < 12; index++) 
  {
    Offsets placeholder = static_cast<Offsets>(index);

    map.insert({placeholder, {char_placeholder_x, char_placeholder_y}});

    char_placeholder_y += y_offset;
  } 
}


void CharacterOverviewState::handleEnter(Game& game)
{

}

void CharacterOverviewState::renderBackground(Game& game) noexcept
{
  ElementUI* placeholder = this->ui_elements_[CharacterOverviewUI::OVERVIEW_BACKGROUND];
  placeholder->render(game); 
}

