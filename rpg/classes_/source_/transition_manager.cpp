#include "../../include_/transition_manager.hpp"
#include "../../include_/game.hpp"



void TransitionManager::transition(Game& game) noexcept
{
  if(this->fading_out_)
  {
    this->fade_alpha_ += this->fade_speed_ * game.getDeltaTime();

    if(this->fade_alpha_ >= 255.0f)
    {
      this->fade_alpha_ = 255.0f;

      this->changeStates(game);

      


    }

    SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, static_cast<Uint8>(this->fade_alpha_));
    SDL_RenderFillRect(game.getRenderer(), nullptr);
  }
  else if(this->fading_in_)
  {
    this->fade_alpha_ -= this->fade_speed_ * game.getDeltaTime();

    if(this->fade_alpha_ <= 0)
    {
      this->fade_alpha_ = 0.0f;

      /*
        We dont take input during transitioning, but we flush the input queue 
        regardless, since there could be some stale events that were not handled
      */
      ParserUtility::flushQueue(game.getDispatcher()->getInputQueue());

    }

    SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, static_cast<Uint8>(this->fade_alpha_));
    SDL_RenderFillRect(game.getRenderer(), nullptr);    
  }
}



void TransitionManager::changeStates(Game& game) noexcept
{
  switch (this->target_state_)
  {
    case GameState::LOG_IN_SCREEN:
      game.setGameState(GameState::LOG_IN_SCREEN);
      game.setCurrentState(game.getLogin());
      break;
    case GameState::CHARACTER_OVERVIEW:
      game.setGameState(GameState::CHARACTER_OVERVIEW);
      game.setCurrentState(game.getCharOverview());
      break;
    case GameState::CHARACTER_MAKING:
      game.setGameState(GameState::CHARACTER_MAKING);
      game.setCurrentState(game.getCharCreation());
      break;
    case GameState::PLAYING:
      game.setGameState(GameState::PLAYING);
      std::cout << "[ERROR] -> [TransitionManager::changeStates] -> Playing State still not implemented <!> " << std::endl;
      break;
    case GameState::EXIT:
      game.setGameState(GameState::EXIT);
      break;
    
    default:
      std::cout << "[ERROR] -> [TransitionManager::changeStates] -> Target State does not match any existing states <!> " << std::endl;
      break;
  }

  return;
}




