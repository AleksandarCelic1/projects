#ifndef GAME_HPP
#define GAME_HPP

#include "account.hpp"
#include "texture_manager.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "login.hpp"

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
    World world_;
    TextureManager texture_manager_;
    Camera camera_;
    Login login_;

    GameSettings game_settings_;
    GameState gamestate_;

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

    Account& getAccount() noexcept { return this->current_account_logged_in_; }
    World& getWorld() noexcept { return this->world_; }
    Camera& getCamera() noexcept { return this->camera_; }
    Login& getLogin() noexcept { return this->login_; }
    GameState& getGameState() noexcept { return this->gamestate_; }


    // Setters
    void setSDLWindow(SDL_Window* new_window) noexcept{ this->main_window_ = new_window; }
    void setSDLRenderer(SDL_Renderer* new_renderer) noexcept { this->main_renderer_ = new_renderer; }
    void setCurrentAccountLoggedIn(Account& new_current_account)  noexcept { this->current_account_logged_in_ = new_current_account; }
    void setWorld(World& world) noexcept { this->world_ = world; }
    void setCamera(Camera& new_camera) noexcept { this->camera_ = new_camera; }
    void setLogin(Login& new_login) noexcept { this->login_ = new_login; }
    void setGameState(GameState& new_state) noexcept { this->gamestate_ = new_state; }
    


    // Functions 
    void initializeResolution() noexcept;
    void initializeWindowAndRenderer() noexcept;



};


#endif