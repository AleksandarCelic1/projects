#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "../enums.hpp"



class Tools;
class Map;
class Character;
class Soldier;
class Orc;
class Inventory;

enum class GameState
{
  LOADING,
  PLAYING,
  FADING_OUT,
  FADING_IN,
  TRANSITIONING,
  INVENTORY,
  IDLE,
  EXIT,
  PLAYER_DIED,
  PLAYER_WON
};

class Game
{
  private:
    std::vector<Map*> maps_;
    Map* idle_zone_;
    Character* soldier_;
    GameState current_state_;
    GameState previous_state_; // used for Transitioning!
    GameState target_state_;
    std::vector<std::vector<Character*>> enemies_on_level_; 

    // Transitioning Variables
    float fade_alpha_;
    bool fading_in_;
    bool fading_out_;
    float fade_speed_;
  public:

    Game();
    Game(const Game& copy) = delete;
    ~Game(); // look into this

    std::vector<Map*>& getMaps() {return this->maps_;}
    Character* getSoldier() {return this->soldier_;}
    GameState getCurrState() const {return this->current_state_;}
    GameState getPreviousState() const { return this->previous_state_;}
    GameState getTargetState() const { return this->target_state_;}
    std::vector<std::vector<Character*>>& getEnemiesOnLevel() {return this->enemies_on_level_;}


    float getFadeAlpha() const { return this->fade_alpha_;}
    float getFadeSpeed() const { return this->fade_speed_;}
    bool isFadingOut() const { return this->fading_out_;}
    bool isFadingIn() const { return this->fading_in_;}

    void setGameState(GameState x);
    void setPreviousGameState(GameState x) { this->previous_state_ = x;}
    void setTargetState(GameState x) { this->target_state_ = x;}
    void makeMaps(Tools* main_tools) noexcept;
    void loadTextures(Tools* main_tools) noexcept;
    void findingOrcs(int current_level) noexcept;
    void findMapObjects(int current_level) noexcept;
    void checkingOrcsTargetLocked(Tools* main_tools, float delta_time) noexcept;

    void setFadeAlpha(float new_fade_alpha)  { this->fade_alpha_ = new_fade_alpha; }
    void setFadeSpeed(float new_fade_speed)  { this->fade_speed_ = new_fade_speed; }
    void setFadingInStatus( bool x) { this->fading_in_ = x;}
    void setFadingOutStatus ( bool x) { this->fading_out_ = x;}


    

};

#endif