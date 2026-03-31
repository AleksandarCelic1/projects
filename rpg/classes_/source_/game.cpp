#include "../include_/game.hpp"

Game::Game()
{
  initializeResolution();
  initializeWindowAndRenderer();
}


void Game::initializeResolution()
{
  int mouse_x = 0;
  int mouse_y = 0;

  SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
  SDL_Point point{mouse_x, mouse_y};
  int display_index = SDL_GetPointDisplayIndex(&point);

  SDL_DisplayMode display_mode;

  if (SDL_GetDesktopDisplayMode(display_index, &display_mode) != 0)
  {
    std::cout << "[ERROR] SDL_GetDesktopDisplayMode Failed!" << std::endl;
    return;
  }

  int width = display_mode.w;
  int height = display_mode.h;

  if(width >= RESOLUTIONS[2].first && height >= RESOLUTIONS[2].second)
  {
    this->game_settings_.scaling_factor_ = SCALING_FACTOR_FOUR;
    this->game_settings_.screen_height_ = RESOLUTIONS[2].second;
    this->game_settings_.screen_width_ = RESOLUTIONS[2].first;
  }
  else if(width >= RESOLUTIONS[1].first && height >= RESOLUTIONS[1].second)
  {
    this->game_settings_.scaling_factor_ = SCALING_FACTOR_THREE;
    this->game_settings_.screen_height_ = RESOLUTIONS[1].second;
    this->game_settings_.screen_width_ = RESOLUTIONS[1].first;
  }
  else
  {
    this->game_settings_.scaling_factor_ = SCALING_FACTOR_TWO;
    this->game_settings_.screen_height_ = RESOLUTIONS[0].second;
    this->game_settings_.screen_width_ = RESOLUTIONS[0].first;
  }

  this->game_settings_.fullscreen_ = false;
   
  return;

}

void Game::initializeWindowAndRenderer()
{
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  window = SDL_CreateWindow("NO TITLE FOR GAME YET", SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED, this->getWindowWidth(), this->getWindowHeight(), SDL_WINDOW_SHOWN);

  if(window == nullptr)
  {
    std::cout << "Window Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(renderer == nullptr)
  {
    std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::exit(EXIT_FAILURE);
  }


  this->main_window_ = window;
  this->main_renderer_ = renderer;


}