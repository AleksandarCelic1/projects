#include "../include_/character_overview.hpp"

CharacterOverviewState::~CharacterOverviewState()
{
  /* clearing */
  for(auto iterator : this->ui_elements_)
  {
    if(iterator != nullptr)
    {
      free(iterator);
      iterator = nullptr;
    }
  }

  std::vector<ElementUI*> placeholder(this->characters_.size());
  for(auto iterator : this->characters_)
  {
    if(iterator.second != nullptr)
    {
      free(iterator.second);
      iterator.second = nullptr;
    }

    placeholder.push_back(iterator.first);
  }


  for(int index = 0; index < placeholder.size(); index++)
  {
    if(placeholder.at(index) != nullptr)
    {
      free(placeholder[index]);
      placeholder[index] = nullptr;
    }
  }

  
}

Character* CharacterOverviewState::getCharacter(ElementUI* key) noexcept
{
  Character* retval = static_cast<Character*>(ExceptionHandler::get(this->characters_, key));
  return retval;
}