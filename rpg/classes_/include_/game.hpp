#ifndef GAME_HPP
#define GAME_HPP

#include "account.hpp"
#include "texture_manager.hpp"

typedef struct
{
  int screen_height_;
  int screen_width_;
  bool fullscreen_;
  int scaling_factor_;
} GameSettings;


class Game
{
  private:
    Account current_account_logged_in_;
    TextureManager texture_manager_;

    GameSettings game_settings_;
    SDL_Window* main_window_;
    SDL_Renderer* main_renderer_;
  
  public:

    Game();
    Game(const Game& copy) = delete;
    ~Game() = default; // Should this be virtual ? 

    // Getters 
    int getWindowHeight() const noexcept  { return this->game_settings_.screen_height_; }
    int getWindowWidth() const noexcept  { return this->game_settings_.screen_width_;  }
    int getFullscreenBoolean() const noexcept { return this->game_settings_.fullscreen_;}
    int getScalingFactor() const noexcept { return this->game_settings_.scaling_factor_;}

    SDL_Window* getMainWindow() const noexcept { return this->main_window_;  }
    SDL_Renderer* getRenderer() const noexcept { return this->main_renderer_;}


    // Setters
    void setSDLWindow(SDL_Window* new_window) noexcept{ this->main_window_ = new_window; }
    void setSDLRenderer(SDL_Renderer* new_renderer) noexcept { this->main_renderer_ = new_renderer; }
    void setCurrentAccountLoggedIn(Account& new_current_account)  noexcept { this->current_account_logged_in_ = new_current_account; }


    // Functions 
    void initializeResolution() noexcept;
    void initializeWindowAndRenderer() noexcept;



};


#endif