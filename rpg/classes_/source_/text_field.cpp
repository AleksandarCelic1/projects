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
  this->max_length_ = 16;

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
  if(this->text_.size() >= this->max_length_)
  {
    return;
  }
  this->text_.push_back(character);
  this->text_changed_ = true;
}


void TextField::handleBackspace() noexcept
{
 if(this->text_.size() == 0)
  {
    return;
  }
  
  this->text_.pop_back();
  this->text_changed_ = true;

  /* Debug Logs */
  //std::cout << this->text_ << std::endl;
}


void TextField::render(Game& game) noexcept
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

  int size = this->text_.size();
  for(int index = 0; index < size; index++)
  {
    Glyph* glyph = static_cast<Glyph*>(ExceptionHandler::get(this->glyphs_, index));
    if(glyph == nullptr)
    {
      continue;
    }

   
    SDL_Rect placeholder;
    placeholder.x = position_x;
    placeholder.y = position_y;
    placeholder.w = width;
    placeholder.h = height;

    position_x += LETTER_WIDTH_AND_HEIGHT * (game.getScalingFactor() + 1);
    SDL_RenderCopy(main_renderer, bitmap_texture, &glyph->getRect(), &placeholder);
  }

  RectUtils::debugOutline(main_renderer, rect);
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
  std::string& text = this->text_;
  std::vector<Glyph*> glyphs;
  BitMap* bitmap = game.getFontManager()->getBitmap();
  

  int size = text.size();
  for(int index = 0; index < size; index++)
  {
    Glyph* placeholder = bitmap->getGlyph(text.at(index));
    if(placeholder == nullptr)
    {
      std::cout << "[ERROR] -> [TextField::rebuildText] -> glyph is nullptr <!> " << std::endl;
      text.erase(text.begin() + index);
      size = text.size();
      index--;
      continue;
    }

    glyphs.push_back(placeholder);
  }

  this->glyphs_.clear();
  this->glyphs_ = glyphs;
  this->text_changed_ = false;
}