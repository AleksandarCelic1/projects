#include "../include_/character_overview.hpp"

CharacterOverviewState::~CharacterOverviewState()
{
  /* clearing */
  std::vector<ElementUI*> placeholder(this->characters_.size());
  for(auto iterator : this->characters_)
  {
    placeholder.push_back(iterator.first);
  }

  MemoryFreeingUtils::clearMap(this->characters_);
  MemoryFreeingUtils::clearVector(placeholder);
  MemoryFreeingUtils::clearVector(this->ui_elements_);

}

Character* CharacterOverviewState::getCharacter(ElementUI* key) noexcept
{
  Character* retval = static_cast<Character*>(ExceptionHandler::get(this->characters_, key));
  return retval;
}