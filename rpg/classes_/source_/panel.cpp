#include "../include_/panel.hpp"
#include "../include_/game.hpp"


Panel::Panel(const TextureAsset& asset, int scaling_factor, float time_passed, float panel_delay, float smooth_duration) 
 : ElementUI(asset, scaling_factor), 
   time_passed_(time_passed),
   panel_delay_(panel_delay),
   smooth_duration_(smooth_duration)
  
  {}

Panel::~Panel() {}

void Panel::renderPanel(Game& game) noexcept
{
  if(this->getTimePassed() < this->getPanelDelay())
  {
    // Print out a error message just so we know where we are currently << !  Consider Error Constant File with all messages
    return;
  }

  float time_passed = this->getTimePassed();
  float panel_delay = this->getPanelDelay();
  float smooth_duration = this->getSmoothDuration();

  float fade_time = time_passed - panel_delay;

  if(fade_time > smooth_duration)
  {
    fade_time = smooth_duration;
  }

  float progress = fade_time / smooth_duration; 
  // This goes "slowly" from 0 to 1 

  Uint8 alpha = progress * 255.0f; // SDL_SetTextureAlphaMode specifically wants Uint8

  SDL_SetTextureAlphaMod(this->getTexture(), alpha);

  
  SDL_RenderCopy(game.getRenderer(), this->getTexture(), nullptr, &this->getDstRect());
}