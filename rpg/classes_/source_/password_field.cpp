#include "../include_/password_field.hpp"
#include "../include_/game.hpp"

PasswordField::PasswordField(std::pair<int, int> coords, std::pair<int,int> offsets, int scaling_factor) : TextField(coords, offsets, scaling_factor) {}

void PasswordField::render(Game& game) noexcept
{
  SDL_Renderer* main_renderer = game.getRenderer();
  SDL_Texture* bitmap_texture = game.getFontManager()->getBitmap()->getTexture();
  const SDL_Rect& rect = this->getDstRect();

  int x = rect.x;
  int y = rect.y;

  int position_x = x;
  int position_y = y;
  int width = 0;
  int height = 0;

  int reference = 0;
  Glyph* star = ExceptionHandler::get(this->getGlyphsConst(), reference);
  if(star == nullptr)
  {
    return;
  }

  int size = this->getTextConst().size();
  for(int index = 0; index < size; index++)
  {
    SDL_Rect placeholder;
    placeholder.x = position_x;
    placeholder.y = position_y;
    placeholder.w = width;
    placeholder.h = height;
    
    SDL_RenderCopy(main_renderer, bitmap_texture, &star->getRect(), &placeholder);
  }

  RectUtils::debugOutline(main_renderer, rect);
}


void PasswordField::update(Game& game) noexcept
{
  if(this->getActive() && this->getTextChanged())
  {
    this->rebuildText(game);
  }
}

/*
  This function is not useful for rebuilding text thats consisted purely of 
  '*' characters, we would simply set our text changed to false, as the function 
  render only takes the first glyph and repeats it "max_length" times.
  No need to rebuild text thats always the same
*/
void PasswordField::rebuildText(Game& game) noexcept
{
  this->setTextChanged(false);
}