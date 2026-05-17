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

  int position_x = x + TEXT_X_OFFSET * game.getScalingFactor(); 
  int position_y = y + rect.h / 2;
  int width = LETTER_WIDTH_AND_HEIGHT * (game.getScalingFactor() + 1);
  int height = LETTER_WIDTH_AND_HEIGHT * (game.getScalingFactor() + 1);

  int reference = 0;
  Glyph* star = static_cast<Glyph*>(ExceptionHandler::get(this->getGlyphsConst(), reference));
  /*if(star == nullptr)
  {
    std::cout << "[ERROR] -> [PasswordField::render] -> glyph star is nullptr <!> " << std::endl;
    return;
  }*/

  int size = this->getTextConst().size();

  /* Debug Printfs */
  std::cout << "Current text size: " << size << std::endl;
  std::cout << "Current text: " << this->getTextConst() << std::endl;

  for(int index = 0; index < size; index++)
  {
    SDL_Rect placeholder;
    placeholder.x = position_x;
    placeholder.y = position_y;
    placeholder.w = width;
    placeholder.h = height;
    
    SDL_RenderCopy(main_renderer, bitmap_texture, &star->getRect(), &placeholder);

    position_x += LETTER_WIDTH_AND_HEIGHT * (game.getScalingFactor() + 0.5);
  }

  RectUtils::debugOutline(game.getRenderer(), this->getDstRect());
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
  BitMap* bitmap = game.getFontManager()->getBitmap();
  if(bitmap == nullptr)
  {
    std::cout << "[ERROR] -> [PasswordField::rebuildText] -> bitmap is nullptr <!> " << std::endl;
    return;
  }

  if(this->getGlyphsConst().size() == 0)
  {
    std::vector<Glyph*>& vector = this->getGlyphsModifiable();

    Glyph* star = bitmap->getGlyph('*');
    if(star == nullptr)
    {
      std::cout << "[ERROR] -> [PasswordField::rebuildText] -> glyph star is nullptr <!> " << std::endl;
      return;
    }

    vector.push_back(star);
  }

  this->setTextChanged(false);
}