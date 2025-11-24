#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h> // check out what those last 2 libraries do i think i need them 

#include "gameLoop.hpp"


int main(void)
{
  std::srand(std::time(nullptr));
  Tools main_tool;
  main_tool.initializeTheWindowRendererFontImageColor();
  Game main_game;
  main_tool.setGame(&main_game);
  main_game.makeMaps(&main_tool);

  SDL_SetRenderDrawBlendMode(main_tool.getMainRenderer(), SDL_BLENDMODE_BLEND);

  // Opening of the APP
  game_loop(main_tool);



  // Game Loop


  // Game Over

  destroyAllTextures();
  return static_cast<int>(Errors::SUCCESS);
}