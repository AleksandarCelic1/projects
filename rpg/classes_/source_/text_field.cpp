#include "../include_/text_field.hpp"
#include "../include_/game.hpp"

TextField::TextField(std::pair<int, int> coords, std::pair<int,int> offsets, int scaling_factor)
{

  SDL_Rect placeholder;
  placeholder.x = coords.first + offsets.first;
  placeholder.y = coords.second + offsets.second;
  placeholder.w = LOGIN_TEXT_PLACEHOLDER_WIDTH * scaling_factor;
  placeholder.h = LOGIN_TEXT_PLACEHOLDER_HEIGHT * scaling_factor;

  this->active_ = false;
  this->text_changed_ = false;
  this->text_ = "";
  this->max_length_ = 16; // Not concluded yet

  this->setDstRect(placeholder);

}

/* 
  [TextField::handleNewLetter] -> think about setting a max limit here,
  because a user theorethically can input so much chars that may lead 
  to insufficient virutal memory, as the input lenght is checked
  in LoginValidator <!>
*/
void TextField::handleNewLetter(char character) noexcept
{
  
  this->text_.push_back(character);
  this->text_changed_ = true;
}


void TextField::handleBackspace() noexcept
{
  if(this->text_.size() == 0)
  {
    // Nothing to "erase"
    return;
  }
  
  this->text_.pop_back();
  this->text_changed_ = true;

}


void TextField::render(Game& game) noexcept
{
  
  RectUtils::debugOutline(game.getRenderer(), this->getDstRect());
}

void TextField::update(Game& game) noexcept
{
  if(this->active_ && this->text_changed_)
  {
    /*
      When the text changes we are not going to remake SDL_Texture* for every letter
      as that would be too expensive on runtime, instead of that we are going to take
      certain parts of a big texture thats called a bitmap, which is essentailly a container
      for letters/special chars etc. and then we would take certain letters (so called glyphs)
      and with that we are going to construct a new Word without recompiling the texture
    */

    this->rebuildText(game);
  }
}

/* 
  Function rebuildText, should rebuild the text each time the text is updated with new
  characters, or when some are removed, the rebuild is done with glyphs being taken out of
  bitmap
*/
void TextField::rebuildText(Game& game) noexcept
{
  return;
}