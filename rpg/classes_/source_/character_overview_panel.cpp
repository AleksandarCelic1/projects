#include "../include_/character_overview_panel.hpp"
#include "../include_/text_field.hpp"

CharacterOverviewPanel::CharacterOverviewPanel(std::unordered_map<Offsets, std::pair<int,int>>& map, const TextureAsset& asset, int scaling_factor)
{
  const SDL_Rect& dst_rect = this->getDstRect();

  for(int index = 5; index < 12; index++)
  {
    Offsets key = static_cast<Offsets>(index);
    ElementUI* placeholder = new TextField({dst_rect.x, dst_rect.y}, map.at(key), scaling_factor);
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



