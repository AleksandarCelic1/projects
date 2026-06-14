#include "../panels_include_/character_overview_panel.hpp"
#include "../../include_/text_field.hpp"
#include "../../include_/game.hpp"

CharacterOverviewPanel::CharacterOverviewPanel(std::unordered_map<Offsets, std::pair<int,int>>& map, const TextureAsset& asset, int scaling_factor) 
  : Panel(asset, scaling_factor, 0.0f, 3.0f, 1.0f)
{
  const SDL_Rect& dst_rect = this->getDstRect();

  for(int index = 5; index < 12; index++)
  {
    Offsets key = static_cast<Offsets>(index);
    ElementUI* placeholder = new TextField({dst_rect.x, dst_rect.y}, map.at(key), scaling_factor, TextPlaceholderType::CHAR_OVERVIEW_PLACEHOLDER);
    characters_.insert({placeholder, nullptr});
  }
}

CharacterOverviewPanel::~CharacterOverviewPanel()
{
  std::vector<ElementUI*> placeholder(this->characters_.size());
  for(auto iterator : this->characters_)
  {
    placeholder.push_back(iterator.first);
  }

  MemoryFreeingUtils::clearMap(this->characters_);
  MemoryFreeingUtils::clearVector(placeholder);
}

Character* CharacterOverviewPanel::getCharacter(ElementUI* key) noexcept
{
  Character* retval = static_cast<Character*>(ExceptionHandler::get(this->characters_, key));
  return retval;
}

void CharacterOverviewPanel::render(Game& game) noexcept
{
  this->renderPanel(game);
  this->renderCharacter(game);

  for(auto& iterator : this->characters_)
  {
    TextField* tmp = dynamic_cast<TextField*>(iterator.first);

    if(tmp->getActive())
    {
      tmp->render(game);
    }
  }
}

void CharacterOverviewPanel::update(Game& game) noexcept
{
  this->setTimePassed(this->getTimePassed() + game.getDeltaTime());

  for(auto& iterator : this->characters_)
  {
    iterator.first->update(game);
  }
}

void CharacterOverviewPanel::addCharacter(ElementUI* key, Character* new_char) noexcept
{
  if(new_char == nullptr)
  {
    std::cout << "[ERROR] -> [CharacterOverviewPanel::addCharacter] -> Character* sent is nullptr <!> " << std::endl;
    return;
  }

  if(this->getCharacter(key) != nullptr)
  {
    std::cout << "[ERROR] -> [CharacterOverviewPanel::addCharacter] -> A character on this key already exists <!> " << std::endl;
    return;
  }

  this->characters_[key] = new_char;
}

void CharacterOverviewPanel::setCurrentlySelectedElement(ElementUI* new_curr_selec) noexcept
{
  if(this->currently_selected_ == new_curr_selec)
  {
    std::cout << "[ERROR] -> [CharacterOverviewState::setCurrentlySelectedElement] -> ElementUI* sent is already currently selected <!> " << std::endl;
    return;
  }

  this->currently_selected_ = new_curr_selec;
}

void CharacterOverviewPanel::renderCharacter(Game& game) noexcept
{
  Character* placeholder = static_cast<Character*>(ExceptionHandler::get(this->characters_, this->currently_selected_));
  if(placeholder == nullptr)
  {
    /* User selected a valid element on our UI but it contains no Character */
    return;
  }


  ClassType type = placeholder->getClassType();

  /*
    I will figure out the dimensions of the character that needs to printed, 
    will most probably use pictures and animations to represent the Character
    selected on right side of the CharOverviewPanel <!>
  */

  return;
}
