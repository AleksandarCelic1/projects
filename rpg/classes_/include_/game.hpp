#ifndef GAME_HPP
#define GAME_HPP

#include "account.hpp"
#include "texture_manager.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "login.hpp"
#include "state.hpp"
#include "dispatcher.hpp"
#include "font_manager.hpp"
#include "character_overview.hpp"
#include "character_creation.hpp"
#include "transition_manager.hpp"

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
    Account* current_account_logged_in_;
    World world_;
    TextureManager* texture_manager_;
    FontManager* font_manager_;
    TransitionManager* transition_manager_;
    Camera camera_; // Probably should be in PlayingState <!>

    LoginState* login_;
    CharacterOverviewState* overview_;
    CharacterCreationState* char_creation_;
    State* current_state_;
    Dispatcher* dispatcher_;

    GameSettings game_settings_;
    GameState gamestate_;

    SDL_Window* main_window_;
    SDL_Renderer* main_renderer_;

    float delta_time_;
  
  public:

    Game();
    Game(const Game& copy) = delete;
    ~Game();

    // Getters 
    int getWindowHeight() const noexcept  { return this->game_settings_.screen_height_; }
    int getWindowWidth() const noexcept  { return this->game_settings_.screen_width_;  }
    int getFullscreenBoolean() const noexcept { return this->game_settings_.fullscreen_;}
    int getScalingFactor() const noexcept { return this->game_settings_.scaling_factor_;}
    float getDeltaTime() const noexcept { return this->delta_time_; }

    SDL_Window* getMainWindow() const noexcept { return this->main_window_;  }
    SDL_Renderer* getRenderer() const noexcept { return this->main_renderer_;}


    Account* getAccount() noexcept { return this->current_account_logged_in_; }
    World& getWorld() noexcept { return this->world_; }
    Camera& getCamera() noexcept { return this->camera_; }
    LoginState* getLogin() noexcept { return this->login_; }
    State* getCurrentState() noexcept { return this->current_state_; }
    TextureManager* getTextureManager() noexcept { return this->texture_manager_; }
    Dispatcher* getDispatcher() noexcept { return this->dispatcher_; }
    FontManager* getFontManager() noexcept { return this->font_manager_; }
    GameState getGameState() const noexcept { return this->gamestate_; }
    CharacterOverviewState* getCharOverview() const noexcept { return this->overview_; }
    CharacterCreationState* getCharCreation() const noexcept { return this->char_creation_; }
    




    // Setters
    void setSDLWindow(SDL_Window* new_window) noexcept{ this->main_window_ = new_window; }
    void setSDLRenderer(SDL_Renderer* new_renderer) noexcept { this->main_renderer_ = new_renderer; }
    void setCurrentAccountLoggedIn(Account* new_current_account)  noexcept { this->current_account_logged_in_ = new_current_account; }
    void setWorld(World& world) noexcept { this->world_ = world; }
    void setCamera(Camera& new_camera) noexcept { this->camera_ = new_camera; }
    void setLogin(LoginState* new_login) noexcept { this->login_ = new_login; }
    void setGameState(GameState new_state) noexcept { this->gamestate_ = new_state; }
    void setCurrentState(State* new_current_state) noexcept { this->current_state_ = new_current_state; }
    void setDeltaTime(float& new_delta_time) noexcept { this->delta_time_ = new_delta_time; }
    void setTextureManager(TextureManager* new_manager) noexcept { this->texture_manager_ = new_manager; }
    void setDispatcher(Dispatcher* new_dispatcher) noexcept { this->dispatcher_ = new_dispatcher; }
    void setFontManager(FontManager* new_font_manager) noexcept { this->font_manager_ = new_font_manager; }
    void setCharOverview(CharacterOverviewState* new_char_overview_state) noexcept { this->overview_ = new_char_overview_state; }
    void setCharCreation(CharacterCreationState* new_char_creation_state) noexcept { this->char_creation_ = new_char_creation_state; }
    


    // Functions 
    void initializeResolution() noexcept;
    void initializeWindowAndRenderer() noexcept;

    void run();
    void render();
    void update();
    void mainEventHandler(SDL_Event* event);
    void calculateDeltaTime(Uint32& last_frame) noexcept; 



};


#endif