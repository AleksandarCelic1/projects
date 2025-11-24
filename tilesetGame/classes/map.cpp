#include "map.hpp"
#include "../celaUtility.hpp"
#include "mapObjects.hpp"
#include "candlestick.hpp"

Map::Map()
{
  // vector of 2d array?
}

Map::~Map()
{
  // Have to check
}


Map::Map(std::vector<std::vector<int>> new_grid) 
{
  this->grid_ = new_grid;
}

void Map::renderMap(Tools* main_tools) noexcept
{
  int map_height = grid_.size() * static_cast<int>(Grid::TILE_SIZE);
  int map_width = grid_[0].size()  * static_cast<int>(Grid::TILE_SIZE);

  int x_offSet = (main_tools->getScreenWidth() - map_width) / 2;
  int y_offSet = (main_tools->getScreenHeight() - map_height) / 2;

  Soldier* player = dynamic_cast<Soldier*>(main_tools->getGame()->getSoldier());
  std::vector<Character*>& current_level_enemies = main_tools->getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];




  for(int index = 0; index < grid_.size(); index++)
  {
    for(int inner = 0; inner < grid_[index].size(); inner++)
    {
      int tag = grid_[index][inner];
      if(tag == static_cast<int>(Grid::NO_TERRAIN)) { continue; }

      int x_axis = inner * static_cast<int>(Grid::TILE_SIZE) + x_offSet;
      int y_axis = index * static_cast<int>(Grid::TILE_SIZE) + y_offSet;

      bool hasChar = (tag == static_cast<int>(Grid::CHARACTER_SOLD));
      bool hasOrc = (tag == static_cast<int>(Grid::CHARACTER_ORC));
      bool hasMushroom = (tag == static_cast<int>(Grid::MUSHROOM));
      bool hasCoin = (tag == static_cast<int>(Grid::COIN));
      bool hasPotion = (tag == static_cast<int>(Grid::HEALTH_POT));
      bool hasRingRuby = (tag == static_cast<int>(Grid::RING_RUBY));
      bool hasRingSapphire = (tag == static_cast<int>(Grid::RING_SAPPHIRE));
      bool hasRingGoldSapphire = (tag == static_cast<int>(Grid::RING_SAPPHIRE_GOLD));
      bool hasStoneSword = (tag == static_cast<int>(Grid::STONE_SWORD));
      bool hasGoldSword = (tag == static_cast<int>(Grid::GOLD_SWORD));
      bool hasBigGoldSword = (tag == static_cast<int>(Grid::BIG_GOLD_SWORD));
      bool hasDoors = ( tag == static_cast<int>(Grid::DOORS_VERTICAL));
      bool hasCandlestick = ( tag == static_cast<int>(Grid::CANDLESTICK));
      bool hasNeedles = ( tag == static_cast<int>(Grid::NEEDLES));
      bool hasLadder = ( tag == static_cast<int>(Grid::LADDERS));
      bool hasTorchHorizontal = ( tag == static_cast<int>(Grid::TORCH_HORIZONTAL_WALL));
      bool hasSkeletonHead = ( tag == static_cast<int>(Grid::SKELETON_HEAD));
      bool hasSkeletonBones = ( tag == static_cast<int>(Grid::SKELETON_BONES));
      bool hasShopKeeper = ( tag == static_cast<int>(Grid::SHOPKEEPER));
      bool hasHorzTorch = ( tag == static_cast<int>(Grid::TORCH_HORIZONTAL_WALL));
      bool hasVerticalTorchLeft = ( tag == static_cast<int>(Grid::TORCH_VERTICAL_LEFT_SIDE));
      bool hasVerticalTorchRight = ( tag == static_cast<int>(Grid::TORCH_VERTICAL_RIGHT_SIDE));
      bool hasBanner = ( tag == static_cast<int>(Grid::BANNER));
      bool hasSmallCobweb = ( tag == static_cast<int>(Grid::SMALL_COBWEB));
      bool hasBigCobweb = ( tag == static_cast<int>(Grid::BIG_COBWEB));
      bool hasRightWingHorDoors = ( tag == static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING));
      bool hasLeftWingHorDoors = ( tag == static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING));
      bool hasMiniChest = ( tag == static_cast<int>(Grid::CHEST_MINI));
      bool hasBigChest = ( tag == static_cast<int>(Grid::CHEST));
      bool hasIronBigBox = ( tag == static_cast<int>(Grid::BOX_IRON_BIG));
      bool hasIronSmallBox = ( tag == static_cast<int>(Grid::BOX_IRON_SMALL));
      bool hasWoodBigBox = ( tag == static_cast<int>(Grid::BOX_WOOD_BIG));
      bool hasWoodSmallBox = ( tag == static_cast<int>(Grid::BOX_WOOD_SMALL));
      bool hasSilverKey = ( tag == static_cast<int>(Grid::SILVER_KEY));
      bool hasGoldKey = ( tag == static_cast<int>(Grid::GOLD_KEY));
      bool hasVerticalFlameThrower = ( tag == static_cast<int>(Grid::FLAMETHROWER_VERTICAL));
      bool hasHorizontalFlameThrower = ( tag == static_cast<int>(Grid::FLAMETHROWER_HORIZONTAL));
      bool hasArrowTrap = ( tag == static_cast<int>(Grid::ARROW_TRAP));
      bool hasChainOne = ( tag == static_cast<int>(Grid::CHAIN_ONE));
      bool hasChainTwo = ( tag == static_cast<int>(Grid::CHAIN_TWO));
      bool hasTrinketRuby = ( tag == static_cast<int>(Grid::TRINKET_RUBY));
      bool hasTrinketSapphire = ( tag == static_cast<int>(Grid::TRINKET_SAPPHIRE));
      bool hasTrinketGoldRuby = ( tag == static_cast<int>(Grid::TRINKET_RUBY_GOLD));





      int tileTag = tag;

      if(hasChar)
      {
        tileTag = player->getCurrentTileTag();
        if(tileTag != 0 && (tileTag < 66 || tileTag > 68)) { tileTag = 0; }
      }

      if(hasMushroom || hasCoin || hasPotion || hasRingRuby || hasRingGoldSapphire || hasRingSapphire
      || hasStoneSword || hasBigGoldSword || hasGoldSword || hasDoors || hasShopKeeper || hasTrinketGoldRuby || hasTrinketRuby || hasTrinketSapphire) // here reserved spot
      {
        tileTag = static_cast<int>(Grid::FLOOR_NEW_ONE);
        tag = static_cast<int>(Grid::FLOOR_NEW_ONE);
      }

      if(hasCandlestick ||  hasNeedles || hasLadder || hasSkeletonBones || hasSkeletonHead || hasBigCobweb || hasSmallCobweb
      || hasLeftWingHorDoors || hasRightWingHorDoors || hasSilverKey || hasGoldKey) 
      { 
        tag = static_cast<int>(Grid::FLOOR_NEW_TWO);
        tileTag = static_cast<int>(Grid::FLOOR_NEW_TWO);
      }
      else if(hasVerticalTorchLeft || hasVerticalTorchRight || hasBigChest || hasMiniChest
      || hasIronBigBox || hasIronSmallBox || hasWoodBigBox || hasWoodSmallBox || hasHorizontalFlameThrower)
      {
        tag = static_cast<int>(Grid::FLOOR_NEW_ONE);
        tileTag = static_cast<int>(Grid::FLOOR_NEW_ONE);
      }

      if(hasOrc)
      {
        int index_of_enemy = -1;
        index_of_enemy = validOrc(current_level_enemies, inner, index);

        if(index_of_enemy == -1)
        {
          continue;
        }

        Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index_of_enemy]);
        placeholder->setXcoordinate(inner);
        placeholder->setYcoordinate(index);
        //std::pair<int,int> player_last_seen_at = {player->getXcoordinate(), player->getYcoordinate()};
        //placeholder->setPlayerCoordsForOrc(player_last_seen_at);
        tileTag = placeholder->getCurrentTileTag(); // ovo treba promjeniti isto 
        if(tileTag != 0 && (tileTag < 66 || tileTag > 68)) { tileTag = 0; }
      }

      if(hasHorzTorch || hasBanner || hasVerticalFlameThrower || hasArrowTrap || hasChainOne || hasChainTwo)  
      { tileTag = static_cast<int>(Grid::WALL_HORIZONTAL_NEW_ONE); tag = static_cast<int>(Grid::WALL_HORIZONTAL_NEW_ONE);}


 


  

      auto[srcRect, dstRect] = getRightSrcAndDstRect(x_axis, y_axis, tileTag, x_offSet);
      
      switch (tag)
      {
        // Floor ===========================
        case static_cast<int>(Grid::CHARACTER_SOLD):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[static_cast<Grid>(tileTag)], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::CHARACTER_ORC):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[static_cast<Grid>(tileTag)], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::FLOOR):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::FLOOR], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::FLOOR_NEW_ONE):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::FLOOR_NEW_ONE], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::FLOOR_NEW_TWO):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::FLOOR_NEW_TWO], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::FLOOR_NEW_THREE):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::FLOOR_NEW_THREE], &srcRect, &dstRect);
          break;

        // Wall Horizontal ===========================
        case static_cast<int>(Grid::WALL_HORIZONTAL):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_HORIZONTAL], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_ONE):
        case static_cast<int>(Grid::TORCH_HORIZONTAL_WALL):
        case static_cast<int>(Grid::BANNER):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_HORIZONTAL_NEW_ONE], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_TWO):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_HORIZONTAL_NEW_TWO], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_THREE):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_HORIZONTAL_NEW_THREE], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_DOWNSIDE):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_HORIZONTAL_NEW_DOWNSIDE], &srcRect, &dstRect);
          break;
        // Wall Vertical =============================
        case static_cast<int>(Grid::WALL_VERTICAL):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_VERTICAL_NEW):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL_NEW], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_VERTICAL_EDGE_DOWNSIDE):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL_EDGE_DOWNSIDE], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_VERTICAL_NEW_WITH_PADDING):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL_NEW_WITH_PADDING], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING], &srcRect, &dstRect);
          break;
        // Wall Corner
        case static_cast<int>(Grid::WALL_CORNER_TOP_LEFT):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_CORNER_TOP_LEFT], &srcRect, &dstRect);
          break;
        case static_cast<int>(Grid::WALL_CORNER_TOP_RIGHT):
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::WALL_CORNER_TOP_RIGHT], &srcRect, &dstRect);
          break;
        default:
          SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::FLOOR], &srcRect, &dstRect);
          break;
      }

      if(hasMushroom)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::MUSHROOM), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::MUSHROOM], &srcRectChar, &dstRectChar); 
      }
      else if(hasCoin)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::COIN), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::COIN], &srcRectChar, &dstRectChar);
      }
      else if(hasPotion)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::HEALTH_POT), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::HEALTH_POT], &srcRectChar, &dstRectChar);
      }
      else if(hasRingGoldSapphire)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::RING_SAPPHIRE_GOLD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::RING_SAPPHIRE_GOLD], &srcRectChar, &dstRectChar);
      }
      else if(hasRingRuby)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::RING_RUBY), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::RING_RUBY], &srcRectChar, &dstRectChar);
      }
      else if(hasRingSapphire)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::RING_SAPPHIRE), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::RING_SAPPHIRE], &srcRectChar, &dstRectChar);
      }
      else if(hasStoneSword)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::STONE_SWORD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::STONE_SWORD], &srcRectChar, &dstRectChar);
      }
      else if(hasBigGoldSword)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::BIG_GOLD_SWORD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::BIG_GOLD_SWORD], &srcRectChar, &dstRectChar);
      }
      else if(hasGoldSword)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::GOLD_SWORD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::GOLD_SWORD], &srcRectChar, &dstRectChar);
      }
      else if(hasDoors)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::DOORS_VERTICAL), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::DOORS_VERTICAL], &srcRectChar, &dstRectChar);
      }
      else if(hasRightWingHorDoors)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::DOORS_HORIZONTAL_RIGHT_WING], &srcRectChar, &dstRectChar);
      }
      else if(hasLeftWingHorDoors)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::DOORS_HORIZONTAL_LEFT_WING], &srcRectChar, &dstRectChar);
      }
      else if(hasSkeletonBones)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::SKELETON_BONES), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::SKELETON_BONES], &srcRectChar, &dstRectChar);
      }
      else if(hasSkeletonHead)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::SKELETON_HEAD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::SKELETON_HEAD], &srcRectChar, &dstRectChar);
      }
      else if(hasBigCobweb)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::BIG_COBWEB), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::BIG_COBWEB], &srcRectChar, &dstRectChar);
      }
      else if(hasSmallCobweb)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::SMALL_COBWEB), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::SMALL_COBWEB], &srcRectChar, &dstRectChar);
      } 
      else if(hasChainOne)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::CHAIN_ONE), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::CHAIN_ONE], &srcRectChar, &dstRectChar);
      }
      else if(hasChainTwo)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::CHAIN_TWO), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::CHAIN_TWO], &srcRectChar, &dstRectChar);
      }
      else if(hasTrinketGoldRuby)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::TRINKET_RUBY_GOLD), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::TRINKET_RUBY_GOLD], &srcRectChar, &dstRectChar);
      }
      else if(hasTrinketRuby)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::TRINKET_RUBY), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::TRINKET_RUBY], &srcRectChar, &dstRectChar);
      } 
      else if(hasTrinketSapphire)
      {
        auto[srcRectChar, dstRectChar] = getRightSrcAndDstRect(x_axis, y_axis, static_cast<int>(Grid::TRINKET_SAPPHIRE), x_offSet);
        SDL_RenderCopy(main_tools->getMainRenderer(), textures_for_map[Grid::TRINKET_SAPPHIRE], &srcRectChar, &dstRectChar);
      }     
    }

  }
}


bool Map::checkLastRenderedPieceIfVerticalWall(int x, int y)
{
  try // Check if im using this at all!
  {
    int tag = grid_.at(y).at(x);

    if(tag == static_cast<int>(Grid::WALL_VERTICAL) ||
    tag == static_cast<int>(Grid::WALL_VERTICAL_EDGE_DOWNSIDE) ||
    tag == static_cast<int>(Grid::WALL_VERTICAL_NEW))
    {
      return true;
    }
  }
  catch(...) {}

  return false;
}

std::pair<SDL_Rect, SDL_Rect> Map::getRightSrcAndDstRect(int x_axis, int y_axis, int tag, int x_off_set) noexcept
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = 0;
  srcRect.y = 0;
  dstRect.x = x_axis;
  dstRect.y = y_axis;


  switch (tag)
  {
    case static_cast<int>(Grid::WALL_VERTICAL):
    case static_cast<int>(Grid::WALL_VERTICAL_NEW):
    case static_cast<int>(Grid::WALL_VERTICAL_EDGE_DOWNSIDE):
      srcRect.h = static_cast<int>(Grid::V_WALL_H);
      srcRect.w = static_cast<int>(Grid::V_WALL_W);

      dstRect.h = static_cast<int>(Grid::TILE_SIZE);
      dstRect.w = static_cast<int>(Grid::V_WALL_W) * 4; // 28 not 64

      if(x_axis == x_off_set)
      {
        dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - static_cast<int>(Grid::V_WALL_W) * 4);
      }
      else
      {
        dstRect.x = x_axis;
      }
      break;
    case static_cast<int>(Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING):
    case static_cast<int>(Grid::WALL_VERTICAL_NEW_WITH_PADDING): 
    case static_cast<int>(Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING):
      srcRect.h = static_cast<int>(Grid::V_WALL_H);
      srcRect.w = static_cast<int>(Grid::V_WALL_W_WITH_PADING);

      dstRect.h = static_cast<int>(Grid::TILE_SIZE);
      dstRect.w = static_cast<int>(Grid::TILE_SIZE); 

      break;
      
    case static_cast<int>(Grid::WALL_HORIZONTAL):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_ONE):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_TWO):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_THREE):
    case static_cast<int>(Grid::WALL_HORIZONTAL_NEW_DOWNSIDE):
    case static_cast<int>(Grid::WALL_CORNER_TOP_LEFT):
    case static_cast<int>(Grid::WALL_CORNER_TOP_RIGHT):
      srcRect.h = static_cast<int>(Grid::H_WALL_H);
      srcRect.w = static_cast<int>(Grid::H_WALL_W);

      dstRect.h = static_cast<int>(Grid::TILE_SIZE);
      dstRect.w = static_cast<int>(Grid::TILE_SIZE);
      break;
    case static_cast<int>(Grid::FLOOR):
    case static_cast<int>(Grid::FLOOR_NEW_ONE):
    case static_cast<int>(Grid::FLOOR_NEW_TWO):
    case static_cast<int>(Grid::FLOOR_NEW_THREE):
      srcRect.h = static_cast<int>(Grid::FLOOR_H);
      srcRect.w = static_cast<int>(Grid::FLOOR_W);

      dstRect.h = static_cast<int>(Grid::TILE_SIZE);
      dstRect.w = static_cast<int>(Grid::TILE_SIZE);
      break;
    case static_cast<int>(Grid::DOORS_VERTICAL):
      srcRect.h = static_cast<int>(Grid::DOORS_VERTICAL_H);
      srcRect.w = static_cast<int>(Grid::DOORS_VERTICAL_W);

      dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
      dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w);
      break;
    case static_cast<int>(Grid::CHAIN_ONE):
    case static_cast<int>(Grid::CHAIN_TWO):
      srcRect.h = static_cast<int>(Grid::CHAINS_BOTH);
      srcRect.w = static_cast<int>(Grid::CHAINS_BOTH);

      dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
      dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) / 2; 
      break;
    case 3:
      srcRect.h = static_cast<int>(Grid::SOLDIER_H);
      srcRect.w = static_cast<int>(Grid::SOLDIER_W);

      dstRect.h = static_cast<int>(Grid::SOLDIER_H) * 3;
      dstRect.w = static_cast<int>(Grid::SOLDIER_W) * 3;
      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h); 
      break;
    case 4:
      srcRect.h = static_cast<int>(Grid::ORC_H); // 15
      srcRect.w = static_cast<int>(Grid::ORC_W); // 22

      dstRect.h = static_cast<int>(Grid::ORC_H) * 3;
      dstRect.w = static_cast<int>(Grid::ORC_W) * 3; 
      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::MUSHROOM):
      srcRect.h = static_cast<int>(Grid::MUSHROOM_H);
      srcRect.w = static_cast<int>(Grid::MUSHROOM_W);

      dstRect.h = static_cast<int>(Grid::MUSHROOM_H) * 2;
      dstRect.w = static_cast<int>(Grid::MUSHROOM_W) * 2;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::COIN):
      srcRect.h = static_cast<int>(Grid::COIN_BOTH);
      srcRect.w = static_cast<int>(Grid::COIN_BOTH);

      dstRect.h = static_cast<int>(Grid::COIN_BOTH) * 2;
      dstRect.w = static_cast<int>(Grid::COIN_BOTH) * 2;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::HEALTH_POT):
      srcRect.h = static_cast<int>(Grid::HEALTH_POT_H);
      srcRect.w = static_cast<int>(Grid::HEALTH_POT_W);

      dstRect.h = static_cast<int>(Grid::HEALTH_POT) * 2;
      dstRect.w = static_cast<int>(Grid::HEALTH_POT_W) * 2;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::RING_SAPPHIRE_GOLD):
    case static_cast<int>(Grid::RING_RUBY):
    case static_cast<int>(Grid::RING_SAPPHIRE):
      srcRect.h = static_cast<int>(Grid::RING_SAPPHIRE_GOLD_BOTH);
      srcRect.w = static_cast<int>(Grid::RING_SAPPHIRE_GOLD_BOTH);

      dstRect.h = static_cast<int>(Grid::RING_SAPPHIRE_GOLD_BOTH) * SCALING_FACTOR_TWO;
      dstRect.w = static_cast<int>(Grid::RING_SAPPHIRE_GOLD_BOTH) * SCALING_FACTOR_TWO;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::TRINKET_RUBY):
    case static_cast<int>(Grid::TRINKET_RUBY_GOLD):
    case static_cast<int>(Grid::TRINKET_SAPPHIRE):
      srcRect.h = static_cast<int>(Grid::TRINKETS_BOTH);
      srcRect.w = static_cast<int>(Grid::TRINKETS_BOTH);

      dstRect.h = srcRect.h * SCALING_FACTOR_TWO;
      dstRect.w = srcRect.w * SCALING_FACTOR_TWO;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::STONE_SWORD):
    case static_cast<int>(Grid::GOLD_SWORD):
    case static_cast<int>(Grid::BIG_GOLD_SWORD):
      srcRect.h = static_cast<int>(Grid::SWORDS_ALL);
      srcRect.w = static_cast<int>(Grid::SWORDS_ALL);

      dstRect.h = static_cast<int>(Grid::SWORDS_ALL) * SCALING_FACTOR_TWO;
      dstRect.w = static_cast<int>(Grid::SWORDS_ALL) * SCALING_FACTOR_TWO;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) / 2) - dstRect.w;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::SKELETON_BONES):
    case static_cast<int>(Grid::SKELETON_HEAD):
      srcRect.h = static_cast<int>(Grid::BOTH_SKELLYS);
      srcRect.w = static_cast<int>(Grid::BOTH_SKELLYS);

      dstRect.h = static_cast<int>(Grid::BOTH_SKELLYS) * SCALING_FACTOR_THREE;
      dstRect.w = static_cast<int>(Grid::BOTH_SKELLYS) * SCALING_FACTOR_THREE;

      dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
      dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
      break;
    case static_cast<int>(Grid::BIG_COBWEB):
    case static_cast<int>(Grid::SMALL_COBWEB):
      srcRect.h = static_cast<int>(Grid::COBWEB_BOTH);
      srcRect.w = static_cast<int>(Grid::COBWEB_BOTH);

      dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
      dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;

      //if(tag == static_cast<int>(Grid::SMALL_COBWEB)) { dstRect.x = x_axis + static_cast<int>(Grid::TILE_SIZE) - dstRect.w}
      break;
    case static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING):
    case static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING):
      srcRect.h = static_cast<int>(Grid::DOORS_HORIZONTAL_BOTH);
      srcRect.w = static_cast<int>(Grid::DOORS_HORIZONTAL_BOTH);

      dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
      dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    default:
      break;
  }
  return {srcRect, dstRect};

}



std::pair<SDL_Rect, SDL_Rect> Map::getSrcAndDstRectForAnimations(int x_axis, int y_axis, 
SDL_Texture* current_frames_texture) noexcept
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = 0;
  srcRect.y = 0;
  dstRect.x = x_axis;
  dstRect.y = y_axis;

  if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_ATTACK][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_ONE_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_ONE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);

  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][0]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][1]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][4]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][5])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_IDLE_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);

  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][2]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_IDLE][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_IDLE_H_EXECEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if (current_frames_texture == textures_for_animations[AnimationState::SOLDIER_ATTACK][1])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_TWO_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_TWO_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_ATTACK][2] ||
  current_frames_texture == textures_for_animations[AnimationState::SOLDIER_ATTACK][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_THREE_AND_FOUR_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_THREE_AND_FOUR_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_ATTACK][4])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_FIVE_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_ATTACK_FIVE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  // Walking frames detection ! < ----- ======= -----
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][1])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][2])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H_EXCEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][4])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][5])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_WALKING][6])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_WALKING_H_EXCEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_WALKING_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][0]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][1]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][4]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][5])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_IDLE_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][2]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_IDLE][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_IDLE_H_EXCEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ATTACKING][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ATTACKING_ONE_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ATTACKING_ONE_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ATTACKING][1])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ATTACKING_TWO_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ATTACKING_TWO_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ATTACKING][2])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ATTACKING_THREE_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ATTACKING_THREE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) + ORC_ATTACKING_Y_OFFSET;
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ATTACKING][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ATTACKING_FOUR_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ATTACKING_FOUR_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) + ORC_ATTACKING_Y_OFFSET;
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ATTACKING][4])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ATTACKING_FIVE_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ATTACKING_FIVE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) + ORC_ATTACKING_Y_OFFSET;
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_FIRST_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][1])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_SECOND_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][2])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H_EXCEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_THIRD_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_FOURTH_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][4])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_FIFTH_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][5])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_SIXTH_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_WALKING][6])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_WALK_H_EXCEPTION);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_WALK_SEVENTH_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_HURT][0]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_HURT][1]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_HURT][2]
  || current_frames_texture == textures_for_animations[AnimationState::SOLDIER_HURT][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_HURT_ALL_H);
    srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_HURT_ALL_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_HURT][0]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_HURT][1]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_HURT][2]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_HURT][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_HURT_ALL_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_HURT_ALL_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_DEATH][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_DEAD_FIRST_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_DEAD_FIRST_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_DEATH][1])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_DEAD_SECOND_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_DEAD_SECOND_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_DEATH][2])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_DEAD_THIRD_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_DEAD_THIRD_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) + ORC_DEATH_Y_OFFSET;
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_DEATH][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_DEAD_FOURTH_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_DEAD_FOURTH_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][0]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][1]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][4]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][5])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_IDLE_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][2]
  || current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_IDLE][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_IDLE_EXCEPTION_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_IDLE_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][0]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_ONE_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_ONE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][1]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_TWO_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_TWO_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][2]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_THREE_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_THREE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][3]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_FOUR_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_FOUR_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][4]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_FIVE_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_FIVE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][5]) 
    { srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_SIX_H); srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_SPECIAL_ABILITY_SIX_W);}

    
    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h); // Check this out!
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_PLATED_WALK]))
  {
    
    if(current_frames_texture != textures_for_animations[AnimationState::ORC_PLATED_WALK][1] || 
    current_frames_texture != textures_for_animations[AnimationState::ORC_PLATED_WALK][2])
    {
      srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_WALK_W);
    }
    else
    {
      srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_WALK_EXCEPTION);
    }

    srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_WALK_H);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h); // Check this out!
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_PLATED_ATTACK]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][0]) 
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_ONE_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_ONE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][1])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_TWO_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_TWO_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][2])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_THREE_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_THREE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][3])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_FOUR_FIVE_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_FOUR_FIVE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][4])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_FOUR_FIVE_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_FOUR_FIVE_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][5])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_SIX_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_SIX_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][6])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_SEVEN_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_SEVEN_W);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_ATTACK][7])
    { srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_EIGHT_H); srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_ATTACK_EIGHT_H);}


    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_PLATED_HURT]))
  {
    srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_HURT_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_HURT_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_PLATED_DEATH]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_DEATH][0])
    { srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_ONE_W); srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_ONE_H);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_DEATH][1])
    { srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_TWO_W); srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_TWO_H);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_DEATH][2])
    { srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_THREE_W); srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_THREE_H);}
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_PLATED_DEATH][3])
    { srcRect.w = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_FOUR_W); srcRect.h = static_cast<int>(AnimationsSize::ORC_PLATED_DEATH_FOUR_H);}


    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::SOLDIER_DEATH]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_DEATH][0])
    {
      srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_DEATH_ONE_W);
      srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_DEATH_ONE_H);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_DEATH][1])
    {
      srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_DEATH_TWO_W);
      srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_DEATH_TWO_H);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_DEATH][2])
    {
      srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_DEATH_THREE_W);
      srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_DEATH_THREE_H);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::SOLDIER_DEATH][3])
    {
      srcRect.w = static_cast<int>(AnimationsSize::SOLDIER_DEATH_FOUR_W);
      srcRect.h = static_cast<int>(AnimationsSize::SOLDIER_DEATH_FOUR_H);
    }

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_IDLE]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_IDLE][2] 
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_IDLE][3])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_IDLE_H_EXCEPTION);
    }
    else
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_IDLE_H);
    }

    srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_IDLE_W);


    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_WALK]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_IDLE][3] 
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_IDLE][7])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_WALK_H_EXCEPTION);
    }
    else
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_WALK_H);
    }

    srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_WALK_W);


    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_HURT]))
  {
    
    srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_HURT_H);
    srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_HURT_W);


    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_DEATH]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_DEATH][0])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_ONE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_ONE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_DEATH][1])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_TWO_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_TWO_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_DEATH][2])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_THREE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_THREE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_DEATH][3])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FOUR_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FOUR_W);
    }

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][0])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_ONE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_ONE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][1])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_TWO_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_TWO_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][2])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_THREE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_THREE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][3])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_FOUR_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_FOUR_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][4])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_FIVE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_FIVE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][5])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_SIX_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_SIX_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][6])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_SEVEN_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_FIRST_ATTACK_SEVEN_W);
    }

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][0])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_ONE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_ONE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][1])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_TWO_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_TWO_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][2]
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][6])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_THREE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_THREE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][3]
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][7])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_FOUR_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_FOUR_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][4]
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][8])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_FIVE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_FIVE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][5]
    || current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][9])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_SIX_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_SIX_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][10])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_SEVEN_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_DEATH_SECOND_ATTACK_SEVEN_W);
    }

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if(doTexturesMatch(current_frames_texture, textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK]))
  {
    if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][0])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_ONE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_ONE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][1])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_TWO_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_TWO_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][2])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_THREE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_THREE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][3])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_FOUR_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_FOUR_W); //HERER
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][4])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_FIVE_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_FIVE_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][5])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_SIX_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_SIX_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][6])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_SEVEN_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_SEVEN_W);
    }
    else if(current_frames_texture == textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][7])
    {
      srcRect.h = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_EIGHT_H);
      srcRect.w = static_cast<int>(AnimationsSize::ORC_ELITE_THIRD_ATTACK_EIGHT_W);
    }

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }

  


  return {srcRect, dstRect};
  
}

void Map::renderHealth(Tools* main_tools) noexcept
{
  // OVDE SI STAO RENDERAJ SRCA POVEZI IH SA LOGIKOM!!!!
}


void Map::renderPlayer(Tools* main_tools) noexcept
{
  Soldier* player = dynamic_cast<Soldier*>(main_tools->getGame()->getSoldier());
  int map_height = grid_.size() * static_cast<int>(Grid::TILE_SIZE);
  int map_width = grid_[0].size() * static_cast<int>(Grid::TILE_SIZE);

  int x_off_set = (main_tools->getScreenWidth() - map_width) / 2;
  int y_off_set = (main_tools->getScreenHeight() - map_height) / 2;

  float x_axis = player->getXAxisCoordinate();
  float y_axis = player->getYAxisCoordinate();

  int screen_x = (int)std::round(x_axis + x_off_set);
  int screen_y = (int)std::round(y_axis + y_off_set);

  auto[srcRectChar, dstRectChar] = getSrcAndDstRectForAnimations(screen_x, screen_y,
  textures_for_animations[player->getAnimationState()][player->getCurrentFrame()]);

  if(player->isLookingLeft() || player->isLookingUp()) 
  {
    SDL_RenderCopyEx(main_tools->getMainRenderer(), textures_for_animations[player->getAnimationState()][player->getCurrentFrame()],
    &srcRectChar, &dstRectChar, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
  }
  else
  {
    SDL_RenderCopy(main_tools->getMainRenderer(), 
    textures_for_animations[player->getAnimationState()][player->getCurrentFrame()], &srcRectChar, &dstRectChar);
  }
  
  player->setSDLRect(dstRectChar);

}


void Map::renderOrcs(Tools* main_tools) noexcept
{
  Soldier* player = dynamic_cast<Soldier*>(main_tools->getGame()->getSoldier());
  std::vector<Character*>& current_level_enemies = main_tools->getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];
  
  int map_height = grid_.size() * static_cast<int>(Grid::TILE_SIZE);
  int map_width = grid_[0].size() * static_cast<int>(Grid::TILE_SIZE);

  int x_off_set = (main_tools->getScreenWidth() - map_width) / 2;
  int y_off_set = (main_tools->getScreenHeight() - map_height) / 2;

  

  

  for(int index = 0; index < current_level_enemies.size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(current_level_enemies[index]);
    if(placeholder == nullptr) { continue; }

    float x_axis = placeholder->getXAxisCoordinate();
    float y_axis = placeholder->getYAxisCoordinate();

    int screen_x = (int)std::round(x_axis + x_off_set);
    int screen_y = (int)std::round(y_axis + y_off_set);

    
    auto[srcRectChar, dstRectChar] = getSrcAndDstRectForAnimations(screen_x, screen_y,
    textures_for_animations[placeholder->getAnimationState()][placeholder->getCurrentFrame()]);

    if(placeholder->isLookingLeft() || placeholder->isLookingUp())
    {
      SDL_RenderCopyEx(main_tools->getMainRenderer(), textures_for_animations[placeholder->getAnimationState()][placeholder->getCurrentFrame()],
      &srcRectChar, &dstRectChar, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
    }
    else
    {
      SDL_RenderCopy(main_tools->getMainRenderer(), 
      textures_for_animations[placeholder->getAnimationState()][placeholder->getCurrentFrame()], &srcRectChar, &dstRectChar);
    }
    
    placeholder->setSDLRect(dstRectChar);
    
  }
}

void Map::renderMapObjects(Tools* main_tool) noexcept
{
  int map_height = grid_.size() * static_cast<int>(Grid::TILE_SIZE);
  int map_width = grid_[0].size() * static_cast<int>(Grid::TILE_SIZE);

  int x_off_set = (main_tool->getScreenWidth() - map_width) / 2;
  int y_off_set = (main_tool->getScreenHeight() - map_height) / 2;

  int x_axis = 0;
  int y_axis = 0;

  for(int index = 0; index < this->current_object_on_this_level_.size(); index++)
  {
    if(Candlestick* placeholder =  dynamic_cast<Candlestick*>(current_object_on_this_level_[index]))
    {
      if(placeholder->getAnimationState() == AnimationState::CANDLESTICK_BURNING)
      {
        x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
        y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

        auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
        textures_for_animations[AnimationState::CANDLESTICK_BURNING][placeholder->getCurrentFrame()], x_off_set);
        SDL_RenderCopy(main_tool->getMainRenderer(), 
        textures_for_animations[AnimationState::CANDLESTICK_BURNING][placeholder->getCurrentFrame()],
        &srcRectCandleStick, &dstRectCandleStick);
      }
    }
    else if(Needles* placeholder = dynamic_cast<Needles*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick);
    }
    else if(Ladder* placeholder = dynamic_cast<Ladder*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[AnimationState::LADDERS_ARROW_MOVING][0], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[AnimationState::LADDERS_ARROW_MOVING][0],
      &srcRectCandleStick, &dstRectCandleStick); // Currently ladder arrow is not available!
    }
    else if(Torch* placeholder = dynamic_cast<Torch*>(current_object_on_this_level_[index]))
    {
      TorchType type = placeholder->getType();
      AnimationState state;

      if(type == TorchType::HORIZONTAL_TORCH) { state = AnimationState::TORCHES_FLAME_HORIZONTAL_WALL;}
      else if(type == TorchType::VERTICAL_TORCH || type == TorchType::VERTICAL_TORCH_INVERTED) { state = AnimationState::TORCHES_VERTICAL_WALL;}

      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[state][placeholder->getCurrentFrame()], x_off_set);
      if(type == TorchType::HORIZONTAL_TORCH || type == TorchType::VERTICAL_TORCH)
      {
        if(type == TorchType::VERTICAL_TORCH) { //dstRectCandleStick.x -= TORCHES_VERTICAL_X_OFFSET;
          }
        SDL_RenderCopy(main_tool->getMainRenderer(), 
        textures_for_animations[state][placeholder->getCurrentFrame()],
        &srcRectCandleStick, &dstRectCandleStick);  
      }
      else if(type == TorchType::VERTICAL_TORCH_INVERTED)
      {
        dstRectCandleStick.x += TORCHES_VERTICAL_X_OFFSET * 2; // < --- fix this with math not hard code!
        SDL_RenderCopyEx(main_tool->getMainRenderer(), 
        textures_for_animations[state][placeholder->getCurrentFrame()],
        &srcRectCandleStick, &dstRectCandleStick, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
      }
      
    }
    else if(Shopkeeper* placeholder = dynamic_cast<Shopkeeper*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(Banner* placeholder = dynamic_cast<Banner*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[AnimationState::BANNER][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[AnimationState::BANNER][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(Chest* placeholder = dynamic_cast<Chest*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;
      AnimationState state;

      if(placeholder->getType() == ChestType::BIG_CHEST) { state = AnimationState::CHEST_BIG_ANIM;}
      else if(placeholder->getType() == ChestType::BIG_CHEST_OPENING) { state = AnimationState::CHEST_BIG_OPENINIG;}
      else if(placeholder->getType() == ChestType::MINI_CHEST) { state = AnimationState::CHEST_MINI_ANIM;}
      else if(placeholder->getType() == ChestType::MINI_CHEST_OPENING) { state = AnimationState::CHEST_MINI_OPENING;}
 
      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[state][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[state][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(Box* placeholder = dynamic_cast<Box*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;
      AnimationState state;


      

      if(placeholder->getType() == BoxType::IRON_BIG_BOX) { state = AnimationState::BOX_BIG_IRON;}
      else if(placeholder->getType() == BoxType::IRON_MINI_BOX) { state = AnimationState::BOX_SMALL_IRON;}
      else if(placeholder->getType() == BoxType::WOOD_BIG_BOX) { state = AnimationState::BOX_BIG_WOOD;}
      else if(placeholder->getType() == BoxType::WOOD_MINI_BOX) { state = AnimationState::BOX_SMALL_WOOD;}
 

      //std::cout << "Current texture: " << textures_for_animations[state][placeholder->getCurrentFrame()] << "\n";

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[state][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[state][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(Key* placeholder = dynamic_cast<Key*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;
      AnimationState state;


      

      if(placeholder->getType() == KeyType::GOLD_KEY) { state = AnimationState::GOLD_KEY;}
      else if(placeholder->getType() == KeyType::SILVER_KEY) { state = AnimationState::SILVER_KEY;}

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[state][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[state][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(Flamethrower* placeholder = dynamic_cast<Flamethrower*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;
      AnimationState state;
      
      if(placeholder->getType() == FlamethrowerType::HORIZONTAL) { state = AnimationState::HORIZONTAL_FLAMETHROWER;}
      else if(placeholder->getType() == FlamethrowerType::VERTICAL) { state = AnimationState::VERTICAL_FLAMETHROWER;}

      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[state][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[state][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    else if(ArrowTrap* placeholder = dynamic_cast<ArrowTrap*>(current_object_on_this_level_[index]))
    {
      x_axis = placeholder->getXCoord() * static_cast<int>(Grid::TILE_SIZE) + x_off_set;
      y_axis = placeholder->getYCoord() * static_cast<int>(Grid::TILE_SIZE) + y_off_set;
      
      auto [srcRectCandleStick, dstRectCandleStick] = findDimenstionsForMapObjects(x_axis, y_axis, 
      textures_for_animations[placeholder->getAnimationState()][placeholder->getCurrentFrame()], x_off_set);
      SDL_RenderCopy(main_tool->getMainRenderer(), 
      textures_for_animations[placeholder->getAnimationState()][placeholder->getCurrentFrame()],
      &srcRectCandleStick, &dstRectCandleStick); 
    }
    

  }
}

std::pair<SDL_Rect, SDL_Rect> Map::findDimenstionsForMapObjects(int x_axis, int y_axis, SDL_Texture* texture_current, int x_off_set) noexcept
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = 0;
  srcRect.y = 0;
  dstRect.x = x_axis;
  dstRect.y = y_axis;

  if(texture_current == textures_for_animations[AnimationState::CANDLESTICK_BURNING][0] 
  || texture_current == textures_for_animations[AnimationState::CANDLESTICK_BURNING][1]
  || texture_current == textures_for_animations[AnimationState::CANDLESTICK_BURNING][2]
  || texture_current == textures_for_animations[AnimationState::CANDLESTICK_BURNING][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::CANDLESTICK_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::CANDLESTICK_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) - CANDLESTICK_Y_OFFSET;
  }
  else if(texture_current == textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][0] 
  || texture_current == textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][1] 
  || texture_current == textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][2] 
  || texture_current == textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][3] )
  {
    srcRect.h = static_cast<int>(AnimationsSize::NEEDLES_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::NEEDLES_BOTH) ;

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;

    dstRect.y += NEEDLES_Y_OFFSET;

    // Shouldnt move its x since he takes up the whole 64x64!
  }
  else if(texture_current == textures_for_animations[AnimationState::LADDERS_ARROW_MOVING][0])
  {
    srcRect.h = static_cast<int>(AnimationsSize::LADDERS_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::LADDERS_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) / 2;
  }
  else if(texture_current == textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][0]
  || texture_current == textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][1]
  || texture_current == textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][2]
  || texture_current == textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::TORCHES_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::TORCHES_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) / 2;
  }
  else if ( texture_current == textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][0]
  || texture_current == textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][1]
  || texture_current == textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][2]
  || texture_current == textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::SHOPKEEPER_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::SHOPKEEPER_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if (texture_current == textures_for_animations[AnimationState::BANNER][0]
  || texture_current == textures_for_animations[AnimationState::BANNER][1]
  || texture_current == textures_for_animations[AnimationState::BANNER][2]
  || texture_current == textures_for_animations[AnimationState::BANNER][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::BANNER_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::BANNER_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h) / 2;
  }
  else if (texture_current == textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][0]
  || texture_current == textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][1]
  || texture_current == textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][2]
  || texture_current == textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][3])
  {
    srcRect.h = static_cast<int>(AnimationsSize::TORCHES_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::TORCHES_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    // check out x and y
  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::CHEST_BIG_OPENINIG])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::CHEST_BIG_ANIM])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::CHEST_MINI_ANIM])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::CHEST_MINI_OPENING])) // Zamjeni samo sve sa ovim! <--------------------------!
  {
    srcRect.h = static_cast<int>(AnimationsSize::CHEST_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::CHEST_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);



  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::BOX_SMALL_IRON])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::BOX_SMALL_WOOD]))
  {

    srcRect.h = static_cast<int>(AnimationsSize::BOX_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::BOX_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);

  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::BOX_BIG_WOOD])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::BOX_BIG_IRON])) 
  {
    srcRect.h = static_cast<int>(AnimationsSize::BOX_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::BOX_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_THREE;
    dstRect.w = srcRect.w * SCALING_FACTOR_THREE;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);


  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::GOLD_KEY])
  || doTexturesMatch(texture_current, textures_for_animations[AnimationState::SILVER_KEY])) 
  {
    srcRect.h = static_cast<int>(AnimationsSize::KEYS_BOTH);
    srcRect.w = static_cast<int>(AnimationsSize::KEYS_BOTH);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;

    dstRect.x = x_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.w) / 2;
    dstRect.y = y_axis + (static_cast<int>(Grid::TILE_SIZE) - dstRect.h);
  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER])) 
  {
    srcRect.h = static_cast<int>(AnimationsSize::HORIZONTAL_FLAMETHROWER_H);
    srcRect.w = static_cast<int>(AnimationsSize::HORIZONTAL_FLAMETHROWER_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER])) 
  {
    srcRect.h = static_cast<int>(AnimationsSize::VERTICAL_FLAMETHROWER_H);
    srcRect.w = static_cast<int>(AnimationsSize::VERTICAL_FLAMETHROWER_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
  }
  else if (doTexturesMatch(texture_current, textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION])) 
  {
    srcRect.h = static_cast<int>(AnimationsSize::ARROW_TRAP_H);
    srcRect.w = static_cast<int>(AnimationsSize::ARROW_TRAP_W);

    dstRect.h = srcRect.h * SCALING_FACTOR_FOUR;
    dstRect.w = srcRect.w * SCALING_FACTOR_FOUR;
  }



  return {srcRect, dstRect};

}

bool Map::doTexturesMatch(SDL_Texture* texture_current, std::vector<SDL_Texture*>& vector_of_specific_animation)
{
  return std::find(vector_of_specific_animation.begin(), vector_of_specific_animation.end(), texture_current) != vector_of_specific_animation.end();
}



