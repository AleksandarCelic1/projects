#include "gameFunctions.hpp"

void controlFPS(Uint32& frame_start)
{
  Uint32 current_frame_time = SDL_GetTicks() - frame_start;
  if(current_frame_time < FRAME_DELAY)
  {
    SDL_Delay(FRAME_DELAY - current_frame_time);
  }
}

std::pair<std::vector<SDL_Texture*>, std::vector<SDL_Rect>> makeLoadingScreenText(Tools& tools) noexcept
{
  std::string label = "Unexcpected Journey";
  std::string any_key = "Press any key to continue!";

  SDL_Surface* label_surface = TTF_RenderText_Blended(tools.getMainFont(), label.c_str(), tools.getTextColour());
  SDL_Texture* label_texture = SDL_CreateTextureFromSurface(tools.getMainRenderer(), label_surface);
  SDL_FreeSurface(label_surface);

  SDL_Surface* any_key_surface = TTF_RenderText_Blended(tools.getMainFont(), any_key.c_str(), tools.getTextColour());
  SDL_Texture* any_key_texture = SDL_CreateTextureFromSurface(tools.getMainRenderer(), any_key_surface);
  SDL_FreeSurface(any_key_surface);


  int width_label = 0;
  int height_label = 0;
  int width_anykey = 0;
  int height_anykey = 0;

  SDL_QueryTexture(label_texture, nullptr, nullptr, &width_label, &height_label);
  SDL_QueryTexture(any_key_texture, nullptr, nullptr, &width_anykey, &height_anykey);

  SDL_Rect label_text_box;
  label_text_box.x = (tools.getScreenWidth() - width_label) / 2;
  label_text_box.y = tools.getScreenHeight() / 2;
  label_text_box.h = height_label;
  label_text_box.w = width_label;

  SDL_Rect anykey_box;
  anykey_box.x = (tools.getScreenWidth() - width_anykey) / 2;
  anykey_box.y = tools.getScreenHeight() - 50;
  anykey_box.w = width_anykey;
  anykey_box.h = height_anykey;

  std::vector<SDL_Texture*> textures;
  textures.push_back(label_texture);
  textures.push_back(any_key_texture);

  std::vector<SDL_Rect> boxes;
  boxes.push_back(label_text_box);
  boxes.push_back(anykey_box);

  return {textures, boxes};
}

void moveChar(Tools& main_tools, Movement direction, float delta_time) noexcept
{
  int level = main_tools.getGame()->getSoldier()->getCurrentLevel();

  //Starting to use sensor of each enemy on this level!
  Map* current_level_map = main_tools.getGame()->getMaps()[level - 1];
  Soldier* player = dynamic_cast<Soldier*>(main_tools.getGame()->getSoldier());
  std::vector<Character*>& current_level_enemies = main_tools.getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];
 
  if(player->getAnimationState() == AnimationState::SOLDIER_IDLE)
  {
    player->setAnimationState(AnimationState::SOLDIER_WALKING);
  }
  else
  {
    return;
  }

  if(!player->canMove()) { return; } else {player->setMovingStatus(false);}

  int x_of_player = player->getXcoordinate();
  int y_of_player = player->getYcoordinate();
  
  

  switch (direction)
  {
    case Movement::UPWARDS:
      if(checkCollisions(current_level_map, player, direction) && resolvingBuggyCollisionWithEntities(current_level_enemies, x_of_player, y_of_player - 1))
      {
        if(player->getCurrentTileTag() != 0 && 
        (player->getCurrentTileTag() < static_cast<int>(Grid::FLOOR_NEW_ONE) 
        || player->getCurrentTileTag() > static_cast<int>(Grid::FLOOR_NEW_THREE)))
        {
  
          player->setCurrentTileTag(static_cast<int>(Grid::FLOOR));
        }

        current_level_map->getGrid()[y_of_player][x_of_player] = player->getCurrentTileTag();
        player->setPreviousTileTag(player->getCurrentTileTag());
        player->setCurrentTileTag(current_level_map->getGrid()[y_of_player - 1][x_of_player]);
        player->calculateTargetCoordsForLerp( &main_tools, Movement::UPWARDS, delta_time);
      }

      player->setLookingDirection(direction); // <---- This is on purpose so we dont have to rotate 
      // in order to attack something if we get into a collision with them, meaning 
      // if someone comes from behind and we press command for left he will just turn around and face the enemy 
      // and will be able to attack instead of making a circle so he can get a right direction in order to hit!
      break;
    case Movement::DOWNWARDS:
      if(checkCollisions(current_level_map, player, direction)  && resolvingBuggyCollisionWithEntities(current_level_enemies, x_of_player, y_of_player + 1))
      {

        if(player->getCurrentTileTag() != 0 && 
        (player->getCurrentTileTag() < static_cast<int>(Grid::FLOOR_NEW_ONE) 
        || player->getCurrentTileTag() > static_cast<int>(Grid::FLOOR_NEW_THREE)))
        {
          player->setCurrentTileTag(static_cast<int>(Grid::FLOOR));
        }

        current_level_map->getGrid()[y_of_player][x_of_player] = player->getCurrentTileTag();
        player->setPreviousTileTag(player->getCurrentTileTag());
        player->setCurrentTileTag(current_level_map->getGrid()[y_of_player + 1][x_of_player]);
        player->calculateTargetCoordsForLerp( &main_tools, Movement::DOWNWARDS, delta_time);
      }
      player->setLookingDirection(direction);
      break;
    case Movement::LEFT:
      if(checkCollisions(current_level_map, player, direction)  && resolvingBuggyCollisionWithEntities(current_level_enemies, x_of_player - 1, y_of_player))
      {

        if(player->getCurrentTileTag() != 0 && 
        (player->getCurrentTileTag() < static_cast<int>(Grid::FLOOR_NEW_ONE) 
        || player->getCurrentTileTag() > static_cast<int>(Grid::FLOOR_NEW_THREE)))
        {
          player->setCurrentTileTag(static_cast<int>(Grid::FLOOR));
        }

        current_level_map->getGrid()[y_of_player][x_of_player] = player->getCurrentTileTag();
        player->setPreviousTileTag(player->getCurrentTileTag());
        player->setCurrentTileTag(current_level_map->getGrid()[y_of_player][x_of_player - 1]);
        player->calculateTargetCoordsForLerp( &main_tools, Movement::LEFT, delta_time);
      }
      player->setLookingDirection(direction);
      break;
    case Movement::RIGHT:
      if(checkCollisions(current_level_map, player, direction)  && resolvingBuggyCollisionWithEntities(current_level_enemies, x_of_player + 1, y_of_player))
      {

        if(player->getCurrentTileTag() != 0 && 
        (player->getCurrentTileTag() < static_cast<int>(Grid::FLOOR_NEW_ONE) 
        || player->getCurrentTileTag() > static_cast<int>(Grid::FLOOR_NEW_THREE)))
        {
          player->setCurrentTileTag(static_cast<int>(Grid::FLOOR));
        }

        current_level_map->getGrid()[y_of_player][x_of_player] = player->getCurrentTileTag();
        player->setPreviousTileTag(player->getCurrentTileTag());
        player->setCurrentTileTag(current_level_map->getGrid()[y_of_player][x_of_player + 1]);
        player->calculateTargetCoordsForLerp( &main_tools, Movement::RIGHT, delta_time);
      }
      player->setLookingDirection(direction);
      break;
    default:
      break;
  }

  //enemySensorChecker(current_level_map, current_level_enemies); // za sad ostavi bez
}


bool resolvingBuggyCollisionWithEntities(std::vector<Character*>& current_level_enemies, int x, int y)
{
  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr || placeholder->isDead())
    {
      continue;
    }


    if(x == placeholder->getTargetXGridCoord() && y == placeholder->getTargetYGridCoord())
    {
      return false;
    }
  }


  return true;
}


void enemySensorChecker(Soldier* player ,Map* current_level_map, std::vector<Character*>& current_level_enemies)
{
  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder != nullptr && !placeholder->isDead())
    {
      placeholder->detectEnemies(current_level_map);

      if(placeholder->isTargetLocked() && placeholder->getActualPath().empty() && player->canMove())
      {
        breadthFirstSearch(current_level_map, placeholder);
      }
    }
  }
}

void helperFunctionForCheckingCollisions(bool& placeholder, Map* current_level, int x, int y) noexcept
{
  placeholder = true;



  switch (current_level->getGrid()[y][x])
  {
    case static_cast<int>(Grid::LADDERS):
    case static_cast<int>(Grid::CANDLESTICK):
    case static_cast<int>(Grid::WALL_HORIZONTAL):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_DOWNSIDE):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_THREE):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_TWO):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_ONE):
    case static_cast<int>(Grid::WALL_VERTICAL_NEW):
    case static_cast<int>(Grid::WALL_VERTICAL_EDGE_DOWNSIDE):
    case static_cast<int>(Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING):
    case static_cast<int>(Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING):
    case static_cast<int>(Grid::WALL_VERTICAL_NEW_WITH_PADDING):
    case static_cast<int>(Grid::WALL_VERTICAL):
    case static_cast<int>(Grid::WALL_CORNER_TOP_LEFT):
    case static_cast<int>(Grid::WALL_CORNER_TOP_RIGHT):
    case static_cast<int>(Grid::DOORS_VERTICAL):
    case static_cast<int>(Grid::TORCH_HORIZONTAL_WALL):
    case static_cast<int>(Grid::SKELETON_BONES):
    case static_cast<int>(Grid::SKELETON_HEAD):
    case static_cast<int>(Grid::SHOPKEEPER):
    case static_cast<int>(Grid::BANNER):
    case static_cast<int>(Grid::SMALL_COBWEB):
    case static_cast<int>(Grid::BIG_COBWEB):
    case static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING):
    case static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING):
    case static_cast<int>(Grid::CHEST):
    case static_cast<int>(Grid::CHEST_MINI):
    case static_cast<int>(Grid::BOX_IRON_BIG):
    case static_cast<int>(Grid::BOX_IRON_SMALL):
    case static_cast<int>(Grid::BOX_WOOD_BIG):
    case static_cast<int>(Grid::BOX_WOOD_SMALL):
    case static_cast<int>(Grid::CHARACTER_ORC):
    case static_cast<int>(Grid::ARROW_TRAP):
    case static_cast<int>(Grid::FLAMETHROWER_VERTICAL):
    case static_cast<int>(Grid::CHAIN_ONE):
    case static_cast<int>(Grid::CHAIN_TWO):

      placeholder = false;
    

      break;
    default:

      break;
  }
}

bool checkCollisions(Map* current_level, Soldier* player, Movement direction) noexcept
{
  bool holder = true;
  

  switch (direction)
  {
    case Movement::UPWARDS: // Here, this part is used for player not to ram into walls and other chars*
      helperFunctionForCheckingCollisions(holder, current_level, player->getXcoordinate(), player->getYcoordinate() - 1);
      checkCollisionsWithItems(current_level, player, player->getXcoordinate(), player->getYcoordinate() - 1);
      break;
    case Movement::DOWNWARDS:
      helperFunctionForCheckingCollisions(holder, current_level, player->getXcoordinate(), player->getYcoordinate() + 1);
      checkCollisionsWithItems(current_level, player, player->getXcoordinate(), player->getYcoordinate() + 1);
      break;
    case Movement::LEFT:
      helperFunctionForCheckingCollisions(holder, current_level, player->getXcoordinate() - 1, player->getYcoordinate());
      checkCollisionsWithItems(current_level, player, player->getXcoordinate() - 1, player->getYcoordinate());
      break;
    case Movement::RIGHT:
      helperFunctionForCheckingCollisions(holder, current_level, player->getXcoordinate() + 1, player->getYcoordinate());
      checkCollisionsWithItems(current_level, player, player->getXcoordinate() + 1, player->getYcoordinate());
      break;
    default:
      break;
  }
  return holder;
}

int validOrc(std::vector<Character*>& enemies, int x, int y) noexcept
{
  for(int index = 0; index < enemies.size(); index++)
  {
    if(enemies[index] != nullptr && enemies[index]->getXcoordinate() == x && enemies[index]->getYcoordinate() == y)
    {
      return index;
    }
  }

  return -1;
}

bool validCoordsForLocatingOrc(Map* current_map, int x, int y)
{
  try
  {
    if(current_map->getGrid()[y][x] == 4) // Fixed! coords were switched!
    {
      return true;
    }
  }
  catch(...)
  {
    return false;
  }

  return true;
}

void attack(Tools& main_tools)
{
  Soldier* player = dynamic_cast<Soldier*>(main_tools.getGame()->getSoldier());
  if(player->getAnimationState() == AnimationState::SOLDIER_IDLE)
  {
    player->setAnimationState(AnimationState::SOLDIER_ATTACK);
  }
  else
  {
    return;
  }

  Map* current_level_map = main_tools.getGame()->getMaps()[player->getCurrentLevel() - 1];
  if(!player->canAttack()) { return; } else { player->setAttackingStatus(false);}
  // Construction < ! =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  int x = 0;
  int y = 0;


  if(player->isLookingDown())
  {
    x = player->getXcoordinate();
    y = player->getYcoordinate() + 1;
  }
  else if(player->isLookingLeft())
  {
    x = player->getXcoordinate() - 1;
    y = player->getYcoordinate();
  }
  else if(player->isLookingUp())
  {
    x = player->getXcoordinate();
    y = player->getYcoordinate() - 1;
  }
  else if(player->isLookingRight())
  {
    x = player->getXcoordinate() + 1;
    y = player->getYcoordinate();
  }

  std::vector<Character*>& current_level_enemies = main_tools.getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];

  int index = 0;
  if(validCoordsForLocatingOrc(current_level_map, x, y))
  {
    int index = 0;
    index = validOrc(current_level_enemies, x, y);
    //std::cout << index;

    if(index != -1)
    {
      if(!current_level_enemies[index]->isDead())
      {
        Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);

        if(placeholder->getOrcType() == OrcType::CLASSIC) { placeholder->setAnimationState(AnimationState::ORC_HURT); }
        else if(placeholder->getOrcType() == OrcType::PLATED) { placeholder->setAnimationState(AnimationState::ORC_PLATED_HURT);}
        else if(placeholder->getOrcType() == OrcType::ELITE) { placeholder->setAnimationState(AnimationState::ORC_ELITE_HURT);}

        current_level_enemies[index]->setCurrentHealth(current_level_enemies[index]->getCurrentHealth() - player->getCurrentDamage());
        
        if(current_level_enemies[index]->getCurrentHealth() <= 0) // here for death
        {
          current_level_enemies[index]->setDead();
          if(placeholder->getOrcType() == OrcType::CLASSIC) { placeholder->setAnimationState(AnimationState::ORC_DEATH);}
          else if(placeholder->getOrcType() == OrcType::PLATED ) { placeholder->setAnimationState(AnimationState::ORC_PLATED_DEATH);}
          else if(placeholder->getOrcType() == OrcType::ELITE ) { placeholder->setAnimationState(AnimationState::ORC_ELITE_DEATH);}
        }
      }
    }
  }

  int ind = findTargetOfMapObjects(current_level_map->getMapObjects(), x , y);
  if( ind != -1) 
  {
    if(Box* placeholder = dynamic_cast<Box*>(current_level_map->getMapObjects()[ind]))
    {
      placeholder->dropLoot(current_level_map);
      placeholder->setOpenStatus(true);
    }
    
    if(Chest* placeholder = dynamic_cast<Chest*>(current_level_map->getMapObjects()[ind]))
    {
      if(placeholder->getType() == ChestType::BIG_CHEST)
      {
        placeholder->setType(ChestType::BIG_CHEST_OPENING);
        placeholder->setAnimationState(AnimationState::CHEST_BIG_OPENINIG);
      }
      else if(placeholder->getType() == ChestType::MINI_CHEST)
      {
        placeholder->setType(ChestType::MINI_CHEST_OPENING);
        placeholder->setAnimationState(AnimationState::CHEST_MINI_OPENING);
      }
    }
  }
}


void handleDeathOfOrcs(Map* current_level, std::vector<Character*>& current_level_enemies) noexcept
{
  for(int index = 0; index < current_level_enemies.size();)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr) { index++; continue; }

    if(placeholder->isFullyDead() && placeholder->isDeathAnimationFinished())
    {
      dropLoot(current_level, current_level_enemies[index]);
      current_level_enemies.erase(current_level_enemies.begin() + index); // Here its not "deleted"!
    }
    else
    {
      index++;
    }
  }
}

int getIndexFromOrc(Tools& main_tools, Detection orc_detected, int x, int y)
{
  Soldier* player = dynamic_cast<Soldier*>(main_tools.getGame()->getSoldier());
  std::vector<Character*>& array_of_enemies = main_tools.getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];
  int index = 0;
  switch (orc_detected)
  {
    case Detection::DETECTED_UP:
      index = validOrc(array_of_enemies, x, y - 1);
      break;
    case Detection::DETECTED_DOWN:
      index = validOrc(array_of_enemies, x, y + 1);
      break;
    case Detection::DETECTED_RIGHT:
      index = validOrc(array_of_enemies, x + 1, y);
      break;
    case Detection::DETECTED_LEFT:
      index = validOrc(array_of_enemies, x - 1, y);
      break;
    default:
      break;
  }

  return index;
}

void dropLoot(Map* current_level_map, Character* enemy) noexcept
{
  Orc* casting_orc = dynamic_cast<Orc*>(enemy);

  int result = 0;
  result = rand() % static_cast<int>(Ranges::DROP_RATE);
  if(casting_orc != nullptr)
  {
    switch (result)
    {
      case 1:
        result = static_cast<int>(Grid::HEALTH_POT);
        break;
      case 2:
        result = static_cast<int>(Grid::MUSHROOM);
        break;
      case 3:
        result = static_cast<int>(Grid::COIN);
        break;
      case 4:
        result = static_cast<int>(Grid::RING_RUBY);
        break;
      default:
      break;
    }

    current_level_map->getGrid()[casting_orc->getYcoordinate()][casting_orc->getXcoordinate()] = result;
  }
  

}

void checkCollisionsWithItems(Map* current_level_map, Soldier* player, int x, int y) noexcept
{
  int tile_tag = current_level_map->getGrid()[y][x];

  bool object_to_remove = false;

  switch (tile_tag)
  {
  case static_cast<int>(Grid::COIN):
    player->setMoney(player->getMoney() + 1);
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::MUSHROOM):
    player->getInventory()->addItem(new Mushroom());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::RING_RUBY):
    player->getInventory()->addItem(new RubyRing());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::HEALTH_POT):
    player->getInventory()->addItem(new Potion());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::STONE_SWORD):
    player->getInventory()->addItem(new StoneSword());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::GOLD_SWORD):
    player->getInventory()->addItem(new GoldSword());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::BIG_GOLD_SWORD):
    player->getInventory()->addItem(new BigGoldSword());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::RING_SAPPHIRE):
    player->getInventory()->addItem(new SapphireRing());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::RING_SAPPHIRE_GOLD):
    player->getInventory()->addItem(new GoldSapphireRing());
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::TRINKET_RUBY):
    player->getInventory()->addItem(new Trinket(TrinketType::RUBY));
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::TRINKET_RUBY_GOLD):
    player->getInventory()->addItem(new Trinket(TrinketType::GOLDRUBY));
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::TRINKET_SAPPHIRE):
    player->getInventory()->addItem(new Trinket(TrinketType::SAPPHIRE));
    current_level_map->getGrid()[y][x] = 0;
    break;
  case static_cast<int>(Grid::SILVER_KEY):
    player->setAmountOfSilverKeys(player->getAmountOfSilverKeys() + 1);
    object_to_remove = true;

    break;
  case static_cast<int>(Grid::GOLD_KEY):
    player->setAmountOfGoldKeys(player->getAmountOfGoldKeys() + 1);
    object_to_remove = true;
    break;
  default:
    break;
  }

  if(object_to_remove)
  {
    int index = -1;
    index = findTargetOfMapObjects(current_level_map->getMapObjects(), x, y);
    if( index != -1) 
    {
      current_level_map->getMapObjects().erase(current_level_map->getMapObjects().begin() + index);
    }
  }
}



void breadthFirstSearch(Map* current_level_map, Orc* enemy) noexcept
{
  std::map<std::pair<int,int>, std::pair<int,int>>& path = enemy->getPath(); 
  std::set<std::pair<int,int>>& visited = enemy->getVisitedPaths();
  std::vector<std::pair<int,int>>& actual_path = enemy->getActualPath();
  std::queue<std::pair<int,int>>& queue = enemy->getQueue();

  std::pair<int,int> source = {enemy->getXcoordinate(), enemy->getYcoordinate()};
  std::pair<int,int>& goal = enemy->getPlayersCordsFromOrc();

  path.clear();
  visited.clear();
  actual_path.clear();
  queue = std::queue<std::pair<int,int>>();
  bool placeholder = false;

  if(source == goal) { return;}

  
  const int number_of_neighbours = 4;
  queue.push(source);
  visited.insert(source);

  while(!queue.empty())
  {
    std::pair<int,int> current_coords = queue.front();
    queue.pop();

    std::vector<std::pair<int,int>> current_coords_neighbours(4);
    current_coords_neighbours[0] = {current_coords.first + 1, current_coords.second};
    current_coords_neighbours[1] = {current_coords.first - 1, current_coords.second};
    current_coords_neighbours[2] = {current_coords.first, current_coords.second + 1};
    current_coords_neighbours[3] = {current_coords.first, current_coords.second - 1};

    for(int index = 0; index < number_of_neighbours; index++)
    {
      
      if(validateCoordsBounds(current_level_map, current_coords_neighbours[index].first, current_coords_neighbours[index].second))
      {

        helperFunctionForCheckingCollisions(placeholder, current_level_map, current_coords_neighbours[index].first, current_coords_neighbours[index].second);
        if(!placeholder) { continue;} else {placeholder = false;}

        if(!visited.count(current_coords_neighbours[index]))
        {
          queue.push(current_coords_neighbours[index]);
          visited.insert(current_coords_neighbours[index]);
          path[current_coords_neighbours[index]] = current_coords;
        }
      }
    }
  }


  //Reconstruct The Path
  
  std::vector<std::pair<int,int>> actual_path_new;
  std::pair<int,int> current = goal;

  while(current != source)
  {
    actual_path_new.push_back(current);
    if(path.find({current.first, current.second}) == path.end())
    {
      return; // no path found!
    }

    std::pair<int,int> path_to_source_partial = path[{current.first, current.second}];
    current = path_to_source_partial;
  }

  std::reverse(actual_path_new.begin(), actual_path_new.end());
  if (!actual_path_new.empty()) 
  {
    actual_path_new.pop_back();
  }

  actual_path = actual_path_new;


  return;

}


void doubleCheckingBFScallsWhileNotMoving(std::vector<Character*>& current_level_enemies, Soldier* player, Map* current_level)
{
  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr || placeholder->isDead()) { continue; }


    if(placeholder->isTargetLocked() && placeholder->getActualPath().empty() && player->canMove() && placeholder->canCallBFS())
    {
      breadthFirstSearch(current_level, placeholder);
      placeholder->setCooldownForBFS();
    }
  }
} 

bool validateCoordsBounds(Map* current_level_map , int x, int y)
{
  try
  {
    int tile = current_level_map->getGrid().at(y).at(x);
    return true;
  }
  catch(std::out_of_range exception) { return false; }

  return false;
}

int findTargetOfMapObjects(std::vector<MapObjects*>& iterate_over, int x, int y) noexcept
{
  for(int index = 0; index < iterate_over.size(); index++)
  {
    if(x == iterate_over[index]->getXCoord() && y == iterate_over[index]->getYCoord())
    {
      return index;
    }
  }

  return -1;
}

void handleEnterInput(Tools& main_tool, Game* game, bool& pump_events) noexcept
{

  Soldier* player = dynamic_cast<Soldier*>(game->getSoldier());
  Map* current_level_map = game->getMaps()[player->getCurrentLevel() - 1];
  std::vector<MapObjects*>& map_objcts = current_level_map->getMapObjects();

  std::pair<int,int> coords = {-1, -1};

  Detection direction_where_detected = Detection::NOTHING_DETECTED;
  direction_where_detected = player->getLookingDireciton();

  

  
  //Moram ovo promjeniti 
  coords = player->checkMapObjNearby(current_level_map, direction_where_detected);
  //std::cout << "[GameFunctions.cpp] At handle enter input checking coords " << coords.first << coords.second << std::endl;
  if(coords.first != -1 && coords.second != -1)
  {
    int index = 0;
    index = findTargetOfMapObjects(map_objcts, coords.first, coords.second);

    if(index == -1)
    {
      return;
    }

    if(Doors* placeholder = dynamic_cast<Doors*>(map_objcts[index]))
    {
      placeholder->useDoors(current_level_map, player);
    }

    if(Ladder* placeholder = dynamic_cast<Ladder*>(map_objcts[index]))
    {
      placeholder->use(game);
    }

    if(Shopkeeper* placeholder = dynamic_cast<Shopkeeper*>(map_objcts[index]))
    {
      player->setShopStatus(true);
      placeholder->use(main_tool);
      pump_events = true;
    }
    
  }

  
}

void destroyAllTextures() noexcept
{
  for(int index = 0; index < textures_for_animations.size(); index++)
  {
    AnimationState key = static_cast<AnimationState>(index);

    if(!textures_for_animations[key].empty())
    {
      for(auto& each : textures_for_animations[key])
      {
        SDL_DestroyTexture(each);
        each = nullptr;
      }
    }
  }


  for(int index = 0; index < textures_for_UI.size(); index++)
  {
    UI key = static_cast<UI>(index);

    if(textures_for_UI[key] != nullptr)
    {
      SDL_DestroyTexture(textures_for_UI[key]);
      textures_for_UI[key] = nullptr;
    }
  }



  // Grid keys are not in ascending order!

  // assuming: extern std::unordered_map<Grid, SDL_Texture*> textures_for_map;

  SDL_DestroyTexture(textures_for_map[Grid::FLOOR_NEW_ONE]);
  SDL_DestroyTexture(textures_for_map[Grid::FLOOR_NEW_TWO]);
  SDL_DestroyTexture(textures_for_map[Grid::FLOOR_NEW_THREE]);
  SDL_DestroyTexture(textures_for_map[Grid::FLOOR]);

  SDL_DestroyTexture(textures_for_map[Grid::WALL_HORIZONTAL_NEW_ONE]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_HORIZONTAL_NEW_TWO]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_HORIZONTAL_NEW_THREE]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_HORIZONTAL_NEW_DOWNSIDE]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_HORIZONTAL]);

  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL_NEW]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL_EDGE_DOWNSIDE]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL_NEW_WITH_PADDING]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_VERTICAL]);

  SDL_DestroyTexture(textures_for_map[Grid::WALL_CORNER_TOP_LEFT]);
  SDL_DestroyTexture(textures_for_map[Grid::WALL_CORNER_TOP_RIGHT]);

  SDL_DestroyTexture(textures_for_map[Grid::CHARACTER_SOLD]);
  SDL_DestroyTexture(textures_for_map[Grid::CHARACTER_ORC]);
  SDL_DestroyTexture(textures_for_map[Grid::TRASURE]);
  SDL_DestroyTexture(textures_for_map[Grid::HEARTH_FULL]);
  SDL_DestroyTexture(textures_for_map[Grid::HEARTH_HALF]);
  SDL_DestroyTexture(textures_for_map[Grid::HEARTH_EMPTY]);

  SDL_DestroyTexture(textures_for_map[Grid::COIN]);
  SDL_DestroyTexture(textures_for_map[Grid::MUSHROOM]);
  SDL_DestroyTexture(textures_for_map[Grid::RING_SAPPHIRE_GOLD]);
  SDL_DestroyTexture(textures_for_map[Grid::HEALTH_POT]);
  SDL_DestroyTexture(textures_for_map[Grid::RING_RUBY]);
  SDL_DestroyTexture(textures_for_map[Grid::RING_SAPPHIRE]);
  SDL_DestroyTexture(textures_for_map[Grid::STONE_SWORD]);
  SDL_DestroyTexture(textures_for_map[Grid::GOLD_SWORD]);
  SDL_DestroyTexture(textures_for_map[Grid::BIG_GOLD_SWORD]);
  SDL_DestroyTexture(textures_for_map[Grid::TRINKET_RUBY]);
  SDL_DestroyTexture(textures_for_map[Grid::TRINKET_RUBY_GOLD]);
  SDL_DestroyTexture(textures_for_map[Grid::TRINKET_SAPPHIRE]);

  SDL_DestroyTexture(textures_for_map[Grid::DOORS_VERTICAL]);
  SDL_DestroyTexture(textures_for_map[Grid::CANDLESTICK]);
  SDL_DestroyTexture(textures_for_map[Grid::NEEDLES]);
  SDL_DestroyTexture(textures_for_map[Grid::LADDERS]);
  SDL_DestroyTexture(textures_for_map[Grid::TORCH_HORIZONTAL_WALL]);
  SDL_DestroyTexture(textures_for_map[Grid::SKELETON_HEAD]);
  SDL_DestroyTexture(textures_for_map[Grid::SKELETON_BONES]);
  SDL_DestroyTexture(textures_for_map[Grid::SHOPKEEPER]);
  SDL_DestroyTexture(textures_for_map[Grid::BANNER]);
  SDL_DestroyTexture(textures_for_map[Grid::SMALL_COBWEB]);
  SDL_DestroyTexture(textures_for_map[Grid::BIG_COBWEB]);
  SDL_DestroyTexture(textures_for_map[Grid::DOORS_HORIZONTAL_LEFT_WING]);
  SDL_DestroyTexture(textures_for_map[Grid::DOORS_HORIZONTAL_RIGHT_WING]);
  SDL_DestroyTexture(textures_for_map[Grid::TORCH_VERTICAL_LEFT_SIDE]);
  SDL_DestroyTexture(textures_for_map[Grid::TORCH_VERTICAL_RIGHT_SIDE]);

  SDL_DestroyTexture(textures_for_map[Grid::CHEST]);
  SDL_DestroyTexture(textures_for_map[Grid::CHEST_MINI]);
  SDL_DestroyTexture(textures_for_map[Grid::BOX_IRON_SMALL]);
  SDL_DestroyTexture(textures_for_map[Grid::BOX_IRON_BIG]);
  SDL_DestroyTexture(textures_for_map[Grid::BOX_WOOD_SMALL]);
  SDL_DestroyTexture(textures_for_map[Grid::BOX_WOOD_BIG]);

  SDL_DestroyTexture(textures_for_map[Grid::SILVER_KEY]);
  SDL_DestroyTexture(textures_for_map[Grid::GOLD_KEY]);
  SDL_DestroyTexture(textures_for_map[Grid::FLAMETHROWER_VERTICAL]);
  SDL_DestroyTexture(textures_for_map[Grid::FLAMETHROWER_HORIZONTAL]);
  SDL_DestroyTexture(textures_for_map[Grid::ARROW_TRAP]);
  SDL_DestroyTexture(textures_for_map[Grid::CHAIN_ONE]);
  SDL_DestroyTexture(textures_for_map[Grid::CHAIN_TWO]);

}

