#include "ladders.hpp"
#include "game.hpp"
#include "soldier.hpp"
#include "map.hpp"

void Ladder::updateAnimation(float delta_time)
{
  // Ladders contain no animation currently! // Gotta Find the Arrow
}

void Ladder::use(Game* game) noexcept
{
  Soldier* player = dynamic_cast<Soldier*>(game->getSoldier());
  
  if(game->getCurrState() != GameState::IDLE)
  {
    if(game->getEnemiesOnLevel()[player->getCurrentLevel() - 1].size() != 10) // 10 reserved places msm popravi ovo 
    {
      return;
    }
    else if(player->getCurrentLevel() == static_cast<int>(Ranges::LEVELS))
    {
      game->setGameState(GameState::FADING_OUT);
      game->setFadingOutStatus(true);
      game->setPreviousGameState(GameState::PLAYING);
      game->setTargetState(GameState::PLAYER_WON);
    }
    else
    {
      game->setTargetState(GameState::IDLE);
      game->setFadingOutStatus(true); 
      game->setPreviousGameState(GameState::PLAYING);
      game->setGameState(GameState::FADING_OUT);
    }


    
  }
  else if(game->getCurrState() == GameState::IDLE)
  {
    game->setTargetState(GameState::PLAYING);
    game->setGameState(GameState::FADING_OUT);
    game->setPreviousGameState(GameState::IDLE);
    game->setFadingOutStatus(true);
  }
}
