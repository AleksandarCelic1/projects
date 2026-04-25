#include "../include_/text_field.hpp"

void TextField::handleNewLetter(char character) noexcept
{
  this->text_.push_back(character);
}

void TextField::handleBackspace() noexcept
{
  if(this->text_.size() == 0)
  {
    // Nothing to "erase"
    return;
  }
  
  this->text_.pop_back();

}