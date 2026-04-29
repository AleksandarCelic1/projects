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
  if(this->active_)
  {
    if(this->text_changed_)
    {
      /*
        When the text changes we are not going to remake SDL_Texture* for every letter
        as that would be too expensive on runtime, instead of that we are going to take
        certain parts of a big texture thats called a bitmap, which is essentailly a container
        for letters/special chars etc. and then we would take certain letters (so called glyphs)
        and with that we are going to construct a new Word without recompiling the texture
      */
    }

    // Else render it 
  }
}