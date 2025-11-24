#include "tabcontrolmenu.hpp"


void tabControlMenu(Tools& main_tools) noexcept
{
  bool programm_running = true;
  SDL_Event idle_zone_event;

  while (programm_running)
  {

    Uint32 frame_start = SDL_GetTicks();

    while(SDL_PollEvent(&idle_zone_event))
    {
      SDL_Keycode pressed = idle_zone_event.key.keysym.sym;

      if(idle_zone_event.type == SDL_KEYDOWN && idle_zone_event.key.repeat == 0)
      {
        if(pressed == SDLK_TAB)
        {
          programm_running = false;
        }
      }

    }

    SDL_RenderClear(main_tools.getMainRenderer());

    SDL_RenderCopy(main_tools.getMainRenderer(), main_tools.getTabTexture(), nullptr, nullptr);
    SDL_RenderPresent(main_tools.getMainRenderer());


    controlFPS(frame_start);
  }
  
}