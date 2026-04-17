#include "../include_/game.hpp"

Game::Game()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  initializeResolution();
  initializeWindowAndRenderer();

  
  this->delta_time_ = 0.0f;

  this->gamestate_ = GameState::LOG_IN_SCREEN;
  this->texture_manager_ = new TextureManager(this->main_renderer_);

  this->login_ = new LoginState(*this);
  this->current_state_ = (this->login_);

  
}

Game::~Game()
{
   if(this->main_renderer_)
  {
    SDL_DestroyRenderer(this->main_renderer_);
    this->main_renderer_ = nullptr;
  }

  if(this->main_window_)
  {
    SDL_DestroyWindow(this->main_window_);
    this->main_window_ = nullptr;
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}


void Game::initializeResolution() noexcept
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

  std::cout << width << " " << height;

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
  // There are different ways to check for resolutions < ! > look into this 
  
   
  return;

}

void Game::initializeWindowAndRenderer() noexcept
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

void Game::run()
{
  SDL_Event event;
  Uint32 last_frame = SDL_GetTicks();

  while(this->gamestate_ != GameState::EXIT)
  {
    this->calculateDeltaTime(last_frame);
    this->mainEventHandler(&event);
    this->update();
    this->render();
  }

  // When finished, make a SAVE to the SQL so 
  // on next load we can continue from where we stopped
}



void Game::render()
{
  SDL_RenderClear(this->main_renderer_);
  this->current_state_->render(*this);
  SDL_RenderPresent(this->main_renderer_);
}

void Game::update()
{
  this->current_state_->update(*this);
}

void Game::mainEventHandler(SDL_Event* event)
{
  // SDL_PollEvent is basically a queue and we ask each frame if there is a new event if no he returns 0 if yes we handle it < !
  while(SDL_PollEvent(event))
  {
    switch(event->key.keysym.sym)
    {
      case SDLK_ESCAPE:
        this->setGameState(GameState::EXIT);
        break;
      case SDL_KEYDOWN:
        break;
      case SDL_KEYUP:
        break;
      case SDL_MOUSEBUTTONDOWN:
        if(event->button.button == SDL_BUTTON_LEFT) { } // this is left click 
        break;
      case SDL_MOUSEBUTTONUP:
        break;
      default:
        break;
    }
  } 



}

void Game::calculateDeltaTime(Uint32& last_frame) noexcept
{
  Uint32 current_frame = SDL_GetTicks();
  this->delta_time_ = (current_frame - last_frame) / ONE_SECOND;
  last_frame = current_frame;
}
