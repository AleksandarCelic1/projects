#include "gameLoop.hpp"

Errors game_loop(Tools& main_tool)
{
  bool programm_running = true;
  bool pump_events = false;
  SDL_Event main_event;
  Game* game = main_tool.getGame();
  Soldier* player = dynamic_cast<Soldier*>(game->getSoldier());
  std::vector<Character*>& current_level_enemies = main_tool.getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];
  std::vector<MapObjects*>& map_objects = game->getMaps()[player->getCurrentLevel() - 1]->getMapObjects();
  

  Uint32 last_frame = SDL_GetTicks();
  float delta_time = 0.0f;


  while(programm_running)
  {
    
    Uint32 frame_start = SDL_GetTicks();

    // Delta time Handling
    calculateDeltaTime(delta_time, frame_start, last_frame);
    
    
    

    last_frame = frame_start;


    while(SDL_PollEvent(&main_event))
    {

      SDL_Keycode pressed = main_event.key.keysym.sym;

      if(game->getCurrState() == GameState::PLAYING || game->getCurrState() == GameState::IDLE)
      {
        if(main_event.type == SDL_KEYDOWN && main_event.key.repeat == 0)
        {
          switch (pressed)
          {
            case SDLK_ESCAPE:
              programm_running = false;
              break;
            case SDLK_w:
            case SDLK_UP:
              moveChar(main_tool, Movement::UPWARDS, delta_time);
              break;
            case SDLK_a:
            case SDLK_LEFT:
              moveChar(main_tool, Movement::LEFT, delta_time);
              break;
            case SDLK_s:
            case SDLK_DOWN:
              moveChar(main_tool, Movement::DOWNWARDS, delta_time);
              break;
            case SDLK_d:
            case SDLK_RIGHT:
              moveChar(main_tool, Movement::RIGHT, delta_time);
              break;
            case SDLK_SPACE:
              attack(main_tool);
              break;
            case SDLK_e:
              player->getInventory()->renderInventory(main_tool);
              pump_events = true;
              // call to inventory
              break;
            case SDLK_TAB:
              tabControlMenu(main_tool);
              pump_events = true;
              break;
            case SDLK_k:
              player->ability(game);
              break;
            case SDLK_RETURN:
              handleEnterInput(main_tool, game, pump_events);
              break;
            default:
              break;
          }
        }
        // commands
      }

      if(pump_events) 
      {
        last_frame = SDL_GetTicks(); 
        SDL_PumpEvents();
        SDL_Event dump_events;
        while (SDL_PollEvent(&dump_events)) { };
        pump_events = false;
      }

      if(game->getCurrState() == GameState::LOADING)
      {
        if(main_event.type == SDL_KEYDOWN)
        {
          player->findCoordsLevelStart(game); // probably should add into ladder also
          game->setFadeAlpha(0.0f);
          game->setFadingOutStatus(true);
          game->setGameState(GameState::FADING_OUT); // < -- za sad
          game->setPreviousGameState(GameState::LOADING);
          game->setTargetState(GameState::PLAYING);
        }
      }

      if(game->getCurrState() == GameState::PLAYER_DIED || game->getCurrState() == GameState::PLAYER_WON) 
      {
        programm_running = false;
      }
    }

    // always clear the brush before using it! :)
    SDL_RenderClear(main_tool.getMainRenderer());

    handlingStates(main_tool, delta_time);


  




    // Present all you painted on your canvas
    SDL_RenderPresent(main_tool.getMainRenderer());

    // FPS handling =========================================
    controlFPS(frame_start);
    // to prevent screen tearing, physics logic and CPU overheating
    // we calculate how much time will CPU basically do nothing
  }

  return Errors::SUCCESS;
}

void calculateDeltaTime(float& delta_time, Uint32 current_frame, Uint32 last_frame)
{
  delta_time = (current_frame - last_frame) / ONE_SECOND;
}

void updateDeltaTimesForEntities(std::vector<Character*>& current_level_enemies, Soldier* player, float& delta_time)
{
  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr) { continue; }
    placeholder->updateAnimation(delta_time);

    if(!placeholder->canAttack())
    {
      placeholder->updateAttackCooldown(delta_time);
    }

    if(placeholder->isDead() && !placeholder->isFullyDead())
    {
      placeholder->updateDeathTimerCooldown(delta_time);
    }

    if(!placeholder->canCallBFS() && placeholder->isTargetLocked())
    {
      placeholder->updateBFSCooldown(delta_time);
    }
  }

  if(player->isDead() && !player->isFullyDead())
  {
    player->updateDeathTimerCooldown(delta_time);
  }
}

void updateDeltaTimesForMapObjects(Game* game, Soldier* player, float& delta_time)
{
  std::vector<MapObjects*>& current_map_object = game->getMaps()[player->getCurrentLevel() -1]->getMapObjects();
  Map* current_level = game->getMaps()[player->getCurrentLevel() - 1];
  std::vector<std::size_t> to_remove_indices;
  
  for(int index = 0; index < current_map_object.size(); index++)
  {
    if(Candlestick* placeholder = dynamic_cast<Candlestick*>(current_map_object[index]))
    {
      placeholder->updateAnimation(delta_time);
    }

    if(Needles* placeholder = dynamic_cast<Needles*>(current_map_object[index]))
    {
      placeholder->handleNeedlesLogic(player);
      placeholder->updateAnimation(delta_time);
    }

    if(Torch* placeholder = dynamic_cast<Torch*>(current_map_object[index]))
    {
      placeholder->updateAnimation(delta_time);
    }

    if(Shopkeeper* placeholder = dynamic_cast<Shopkeeper*>(current_map_object[index]))
    {
      placeholder->updateAnimation(delta_time);
    }

    if(Banner* placeholder = dynamic_cast<Banner*>(current_map_object[index]))
    {
      placeholder->updateAnimation(delta_time);
    }

    if(Chest* placeholder = dynamic_cast<Chest*>(current_map_object[index]))
    {
      if(placeholder->isChestOpened())
      {
        placeholder->dropLoot(current_level);
        to_remove_indices.push_back(index);
      }
      else
      {
        placeholder->updateAnimation(delta_time);
      }
      
    }

    if(Box* placeholder = dynamic_cast<Box*>(current_map_object[index]))
    {
      if(placeholder->getOpenedStatus())
      {
        to_remove_indices.push_back(index);
      }
      else
      {
        placeholder->updateAnimation(delta_time);
      }
    }

    if(Key* placeholder = dynamic_cast<Key*>(current_map_object[index]))
    {
      placeholder->updateAnimation(delta_time);
    }

    if(Flamethrower* placeholder = dynamic_cast<Flamethrower*>(current_map_object[index]))
    {
      placeholder->handleFlameThrowerLogic(player);
      placeholder->updateAnimation(delta_time);
    }

    if(ArrowTrap* placeholder = dynamic_cast<ArrowTrap*>(current_map_object[index]))
    {
      placeholder->handleArrowTrapLogic(player);
      placeholder->updateAnimation(delta_time);
    }
  }

  for(int ind = 0; ind < to_remove_indices.size(); ind++)
  {
    int key = to_remove_indices[ind];

    delete current_map_object[key];
    current_map_object.erase(current_map_object.begin() + key);
  }
}

void handleTransitioning(Tools* main_tools, float& delta_time) noexcept
{
  Game* game = main_tools->getGame();
  Soldier* player = dynamic_cast<Soldier*>(main_tools->getGame()->getSoldier());

  float fade_alpha = game->getFadeAlpha();
  float fade_speed = game->getFadeSpeed();

  if(game->isFadingOut())
  {
    fade_alpha += fade_speed * delta_time;

    game->setFadeAlpha(fade_alpha);

    if(fade_alpha >= 255.0f)
    {
      fade_alpha = 255.0f;
      game->setFadeAlpha(255.0f);
      game->setFadingOutStatus(false);
      game->setFadingInStatus(true);

      if(game->getTargetState() == GameState::IDLE) 
      {
        player->setCurrentLevel(player->getIdleZoneIndex() + 1); 
        player->findCoordsLevelStart(game);
      }
      else if(game->getTargetState() == GameState::PLAYING && game->getPreviousState() == GameState::IDLE)
      {
        player->setCurrentLevel(player->getLastLevelVisited() + 1);
        player->findCoordsLevelStart(game); 
      }
      else if(game->getTargetState() == GameState::PLAYING && game->getPreviousState() == GameState::LOADING)
      {
        // Nothing Happens
      }

      game->setGameState(GameState::FADING_IN);
    }

    SDL_SetRenderDrawColor(main_tools->getMainRenderer(), 0, 0, 0, static_cast<Uint8>(fade_alpha));
    SDL_RenderFillRect(main_tools->getMainRenderer(), nullptr);
  }
  else if(game->isFadingIn()) // cant separate those if blocks !
  {
    fade_alpha -= fade_speed * delta_time;

    game->setFadeAlpha(fade_alpha);

    if(fade_alpha <= 0.0f)
    {
      fade_alpha = 0.0f;
      game->setFadeAlpha(0.0f);
      game->setFadingInStatus(false);
      if(game->getTargetState() == GameState::IDLE) 
      {
        game->setGameState(GameState::IDLE); 
      }
      else if(game->getTargetState() == GameState::PLAYING)
      {
        game->setGameState(GameState::PLAYING);
      }
      else if(game->getTargetState() == GameState::PLAYER_DIED)
      {
        game->setGameState(GameState::PLAYER_DIED);
      }
      else if(game->getTargetState() == GameState::PLAYER_WON)
      {
        game->setGameState(GameState::PLAYER_WON);
      }
    }

    SDL_SetRenderDrawColor(main_tools->getMainRenderer(), 0, 0, 0, static_cast<Uint8>(fade_alpha));
    SDL_RenderFillRect(main_tools->getMainRenderer(), nullptr);
  }
}

void updateLerpForEnemiesOnCurrentLevel(Tools* main_tools, Map* current_level_map ,std::vector<Character*>& current_level_enemies, float& delta_time)
{
  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr) { continue; }
    
    if(!placeholder->canMove())
    {
      placeholder->updateLerp(main_tools, current_level_map, delta_time);
    }
  }
}

void handlingStates(Tools& main_tool, float& delta_time ) noexcept
{
  Game* game = main_tool.getGame();
  Soldier* player = dynamic_cast<Soldier*>(game->getSoldier());
  std::vector<Character*>& current_level_enemies = main_tool.getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];
  
  std::vector<MapObjects*>& map_objects = game->getMaps()[player->getCurrentLevel() - 1]->getMapObjects();

  player->updateAnimation(delta_time);
  updateDeltaTimesForEntities(current_level_enemies, player, delta_time);
  updateDeltaTimesForMapObjects(game, player, delta_time);
  updateDeltaTimeForHourglass(player->getHourglass(), delta_time);
  


  if (game->getCurrState() == GameState::FADING_OUT)
  {
    if(game->getPreviousState() == GameState::LOADING)
    {
      SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getIntroScreenInterface(), nullptr, nullptr);
      auto [textures, boxes] = makeLoadingScreenText(main_tool);
      SDL_RenderCopy(main_tool.getMainRenderer(), textures.at(1), nullptr, &(boxes.at(1))); 
    }
    else if(game->getPreviousState() == GameState::PLAYING)
    {
      SDL_SetRenderDrawColor(main_tool.getMainRenderer(), 37, 19, 26, 255);
      SDL_RenderClear(main_tool.getMainRenderer());
      player->updateLerp(&main_tool, game->getMaps()[player->getCurrentLevel() - 1], delta_time);
      updateLerpForEnemiesOnCurrentLevel(&main_tool, game->getMaps()[player->getCurrentLevel() - 1] , current_level_enemies, delta_time);
      game->getMaps()[player->getCurrentLevel() - 1]->renderMap(&main_tool);
      game->getMaps()[player->getCurrentLevel() - 1]->renderMapObjects(&main_tool);
      game->getMaps()[player->getCurrentLevel() - 1]->renderPlayer(&main_tool);
      game->getMaps()[player->getCurrentLevel() - 1]->renderOrcs(&main_tool);
      game->checkingOrcsTargetLocked(&main_tool, delta_time);
      handleDeathOfOrcs(game->getMaps()[player->getCurrentLevel() - 1], current_level_enemies);
      player->getHourglass()->renderHourglass(&main_tool);
      main_tool.renderUI();
    }
    else if(game->getPreviousState() == GameState::IDLE)
    {
      SDL_SetRenderDrawColor(main_tool.getMainRenderer(), 37, 19, 26, 255);
      SDL_RenderClear(main_tool.getMainRenderer());
      //std::cout << "[GameLoop] Inside GameState Idle Block! ";
      game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderMap(&main_tool);
      game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderMapObjects(&main_tool);
      game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderPlayer(&main_tool);
      player->getHourglass()->renderHourglass(&main_tool);
      main_tool.renderUI();
    }
  }
  else if (game->getCurrState() == GameState::FADING_IN && game->getTargetState() == GameState::PLAYER_DIED)
  {
    SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getDeathScreen(), nullptr, nullptr);
  }
  else if(game->getCurrState() == GameState::FADING_IN && game->getTargetState() == GameState::PLAYER_WON)
  {
    SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getWonScreen(), nullptr, nullptr);
  }
  else if (game->getCurrState() == GameState::FADING_IN || game->getCurrState() == GameState::PLAYING)
  {
    SDL_SetRenderDrawColor(main_tool.getMainRenderer(), 37, 19, 26, 255);
    SDL_RenderClear(main_tool.getMainRenderer());
    player->updateLerp(&main_tool, game->getMaps()[player->getCurrentLevel() - 1], delta_time);
    updateLerpForEnemiesOnCurrentLevel(&main_tool, game->getMaps()[player->getCurrentLevel() - 1] , current_level_enemies, delta_time);
    game->getMaps()[player->getCurrentLevel() - 1]->renderMap(&main_tool);
    game->getMaps()[player->getCurrentLevel() - 1]->renderMapObjects(&main_tool);
    game->getMaps()[player->getCurrentLevel() - 1]->renderPlayer(&main_tool);
    game->getMaps()[player->getCurrentLevel() - 1]->renderOrcs(&main_tool);
    game->checkingOrcsTargetLocked(&main_tool, delta_time);
    handleDeathOfOrcs(game->getMaps()[player->getCurrentLevel() - 1], current_level_enemies);
    player->getHourglass()->renderHourglass(&main_tool);
    main_tool.renderUI();
  }

  if(game->getCurrState() == GameState::LOADING)
  {
    SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getIntroScreenInterface(), nullptr, nullptr);
    //Text Handling
    auto [textures, boxes] = makeLoadingScreenText(main_tool);
    //SDL_RenderCopy(main_tools.getMainRenderer(), textures.at(0), nullptr, &(boxes.at(0)));
    SDL_RenderCopy(main_tool.getMainRenderer(), textures.at(1), nullptr, &(boxes.at(1)));
  }

  if(game->getCurrState() == GameState::IDLE)
  {
    SDL_SetRenderDrawColor(main_tool.getMainRenderer(), 37, 19, 26, 255);
    SDL_RenderClear(main_tool.getMainRenderer());
    player->updateLerp(&main_tool, game->getMaps()[player->getCurrentLevel() - 1], delta_time);
    updateLerpForEnemiesOnCurrentLevel(&main_tool, game->getMaps()[player->getCurrentLevel() - 1] , current_level_enemies, delta_time);
    game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderMap(&main_tool);
    game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderMapObjects(&main_tool);
    game->getMaps()[static_cast<int>(Ranges::LEVELS)]->renderPlayer(&main_tool);
    player->getHourglass()->renderHourglass(&main_tool);
    main_tool.renderUI();
  }

  if(game->getCurrState() == GameState::PLAYER_DIED)
  {
    SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getDeathScreen(), nullptr, nullptr);
  }

  if(game->getCurrState() == GameState::PLAYER_WON)
  {
    SDL_RenderCopy(main_tool.getMainRenderer(), main_tool.getWonScreen(), nullptr, nullptr);
  }

  if(game->isFadingIn() || game->isFadingOut()) { handleTransitioning(&main_tool, delta_time); }

  if(player->isFullyDead() && game->getCurrState() == GameState::PLAYING) 
  {
    game->setTargetState(GameState::PLAYER_DIED);
    game->setFadingOutStatus(true); 
    game->setPreviousGameState(GameState::PLAYING);
    game->setGameState(GameState::FADING_OUT);
  }

  doubleCheckingBFScallsWhileNotMoving(current_level_enemies, player, game->getMaps()[player->getCurrentLevel() - 1]); 
  // NAVODNO JE POPRAVLJENO DONESI IDIOTA NEKOG DA TESTIRA!

}

void updateDeltaTimeForHourglass(Hourglass* hourglass, float delta_time) noexcept
{
  if(hourglass->isRotating())
  {
    hourglass->updateAnimation(delta_time);
  }
  else
  {
    return;
  }
  
}






