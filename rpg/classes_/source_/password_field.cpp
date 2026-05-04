#include "../include_/password_field.hpp"
#include "../include_/game.hpp"

PasswordField::PasswordField(std::pair<int, int> coords, std::pair<int,int> offsets, int scaling_factor) : TextField(coords, offsets, scaling_factor) {}

void PasswordField::render(Game& game) noexcept
{
 // still not implemented
  RectUtils::debugOutline(game.getRenderer(), this->getDstRect());
}


void PasswordField::update(Game& game) noexcept
{
  if(this->getActive() && this->getTextChanged())
  {
    this->rebuildText(game);
  }
}

void PasswordField::rebuildText(Game& game) noexcept
{
  return;
}