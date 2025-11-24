#include "game.hpp"

#include "../celaUtility.hpp"
#include "map.hpp"
#include "character.hpp"
#include "soldier.hpp"
#include "orc.hpp"
#include "inventory.hpp"
#include "candlestick.hpp"
#include "mapObjects.hpp"



void Game::makeMaps(Tools* main_tools) noexcept
{
  loadTextures(main_tools);

  this->soldier_ = new Soldier();
  this->soldier_->setInventory(new Inventory(main_tools));

  fade_alpha_ = 0.0f;
  fading_in_ = false;
  fading_out_ = false;
  fade_speed_ = 255.0f / 1.0f; // fading in 1 second

  int index = 0;

  this->maps_.resize(static_cast<int>(Ranges::LEVELS) + 1);
  

  std::vector<std::vector<int>> first_level_grid(static_cast<int>(Ranges::LEVEL_ONE_HEIGHT),
  std::vector<int>(static_cast<int>(Ranges::LEVEL_ONE_WIDTH)));
  //{73, 66, 0, 0, 0, 0, 0, 0, 0, 73, -1, -1, -1, -1},

  first_level_grid = 
  {
    {-1, -1, -1, -1, 76, 69, 70, 71, 69, 70, 71, 69, 70, 2, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 22, 68, 0, static_cast<int>(Grid::NEEDLES), 66, 68, static_cast<int>(Grid::SKELETON_BONES), 22, 73, -1, -1, -1, -1},
    {-1, -1, -1, -1, 76, 0, 67, 0, static_cast<int>(Grid::NEEDLES), 0, 0, 67, 0, 2, -1, -1, -1, -1},
    {76, 69, 70, 71, 70, 0, 66, 0, 0, 68, 0, 0, 0, 70 , 69, 70, 71 , 2}, // here
    {77, 3, 0, 0, 21, 0, 0, 67, 0, 0, 0, 4, 0, static_cast<int>(Grid::DOORS_VERTICAL) , 0, 0, static_cast<int>(Grid::LADDERS), 73},
    {78, 72, 72, 72, 79, 0, 0, 0, 68, 67, 0, 68, 0, 75 , 72, 72, 72 , 74}, // ovde 70 ne valja treba cosak novi!!!
    {-1, -1, -1, -1, 76, static_cast<int>(Grid::SKELETON_BONES), 0, 66, static_cast<int>(Grid::NEEDLES), 68, 0, 0, static_cast<int>(Grid::SKELETON_HEAD), 2, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 22, static_cast<int>(Grid::SKELETON_BONES), 0, static_cast<int>(Grid::NEEDLES), 0, 0, 66, 22, 73, -1, -1, -1, -1},
    {-1, -1, -1, -1, 78, 72, 72, 72, 72, 72, 72, 72, 72, 74, -1, -1, -1, -1}
  };


  std::vector<std::vector<int>> idle_zone_grid(static_cast<int>(Ranges::IDLE_ZONE_HEIGHT),
  std::vector<int>(static_cast<int>(Ranges::IDLE_ZONE_WIDTH)));

  idle_zone_grid =
  {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, 77, 69, static_cast<int>(Grid::TORCH_HORIZONTAL_WALL), 71, static_cast<int>(Grid::TORCH_HORIZONTAL_WALL), 70, 73, -1},
    {-1, 76, 0, 0, static_cast<int>(Grid::LADDERS), 0, static_cast<int>(Grid::SKELETON_HEAD), 2, -1},
    {-1, 77, 0, 3, 0, 0, static_cast<int>(Grid::SHOPKEEPER), 73, -1},
    {-1, 76, static_cast<int>(Grid::SKELETON_BONES), 0, 0, 0, 0, 2, -1},
    {-1, 78, 72, 72, 72, 72, 72, 74, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  };

  std::vector<std::vector<int>> second_level_grid = 
  { // 16 x 16
    {-1, -1, -1, -1, -1, 77, 69, 70, 71, 69, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 76, 38, 40, 42, 30, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 77, 34, 4, 0, 35, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 76, 0, 0, 0, 0, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 78, 79, 23, 23, 75, 74, -1, -1, -1, -1, -1},
    {77, 69, 29, 71, 73, 77, 69, 0, 0, 69, 73, 77, 69, 29, 71, 73, -1},

    {76, 36, 18, 22, 44, 46, 0, 0, 12, 0, 47, 48, 22, 0, 30, 2},
    {77, 37, 4, 0, 0, 0, 0, 3, 0, 0, 0, 21, 0, 4, 43, 73},
    {76, 31, 0, 0, 75, 79, 31, 0, 0, 0, 75, 79, 0, 39, 41, 2},
    {78, 72, 72, 72, 74, 78, 79, 45, 0, 75, 74, 78, 72, 72, 72, 74},

    {-1, -1, -1, -1, -1, 77, 69, 32, 33, 69, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 76, 0, 0, 0, 26, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 77, 34, 24, 4, 35, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 76, 27, 0, 36, 0, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, 78, 72, 72, 72, 72, 74, -1, -1, -1, -1, -1}
  };



  std::vector<std::vector<int>> third_level_grid(static_cast<int>(Ranges::LEVEL_THREE_HEIGHT),
  std::vector<int>(static_cast<int>(Ranges::LEVEL_THREE_WIDTH)));

  third_level_grid =
  {
    {-1, 77, 69, 47, 48, 70 , 69, 44, 29, 44, 70, 71, 71, 69 , 70, 73, -1},
    {-1, 76, 36, 43, 18, 0, 68, 66, 0, 67, 0, 0, 67, 27, 22, 2, -1}, // last added 18
    {-1, 77, 37, 68, 4, 66, 0, 0, 68, 0, 4, 0, 68, 0, 26, 73, -1}, // First Chamber !
    {-1, 76, 0, 66, 67, 68, 0, 67, 0, 0, 67, 0, 66, 0, 37, 2, -1},
    {-1, 77, 0, 75, 72, 72, 72, 79, 0, 75, 72, 72, 72, 79, 0, 73, -1},

    {-1, 76, 23, 2, -1, -1, -1, 77, 23, 73, -1, -1, -1, 76, 0, 2, -1, -1}, // Hallway to first Chamber!

    {-1, 77, 23, 73, -1, 77, 70, 25, 0, 25 ,71, 73, -1, 77, 23, 73}, 
    {-1, 76, 0, 2, -1, 76, 31, 0, 0, 67, 40, 2, -1, 76, 0, 2}, 
    {-1, 77, 20, 73, -1, 77, 0, 3, 66, 0, 12, 73, -1, 77, 19, 73, -1,}, // Starting Chamber
    {-1, 76, 0, 2, -1, 76, 34, 0, 0, 68, 35, 2, -1, 76, 0, 2}, 
    {-1, 77, 23, 73, -1, 78, 72, 79, 0, 75, 72, 74, -1, 77, 23, 73}, 

    {-1, 76, 23, 2, -1, -1, -1, 77, 23, 73, -1, -1, -1, 76, 23, 2, -1, -1}, // Hallway to second Chamber!

    {-1, 77, 0, 48, 44, 70 , 44, 25, 0, 25, 44, 48, 44, 69 , 0, 73, -1},
    {-1, 76, 0, 68, 66, 0, 0, 66, 67, 0, 0, 0, 68, 37, 36, 2, -1},
    {-1, 77, 27, 0, 0, 4, 0, 68, 0, 0, 0, 67, 4, 0, 24, 73, -1}, // First Chamber !
    {-1, 76, 22, 26, 0, 0, 66, 67, 68, 0, 68, 0, 66, 67, 39, 2, -1}, // last added 19
    {-1, 78, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 74, -1},
    
  };


  std::vector<std::vector<int>> fourth_level_grid(static_cast<int>(Ranges::LEVEL_FOUR_HEIGHT),
  std::vector<int>(static_cast<int>(Ranges::LEVEL_FOUR_WIDTH)));


  fourth_level_grid = 
  {
    { -1, 77, 69, 29, 71, 73, 77, 69, 29, 71, 73, 77, 69, 29, 71, 73, 77, 69, 29, 71, 73},
    { -1, 76, 40, 36, 67, 25, 25, 31, 66, 68, 44, 46, 15, 12, 68, 25, 25, 9, 12, 0, 2},
    { -1, 77, 9, 4, 66, 23, 23, 66, 4, 66, 67, 68, 0, 4, 67, 23, 23, 67, 3, 66, 73},
    { -1, 76, 9, 68, 0, 75 ,79 , 0, 0, 27, 75, 79, 66, 67, 66, 75, 79, 66, 67, 68, 2},
    { -1, 78, 79, 66, 75 ,74, 78, 72, 72, 72 ,74, 78, 72, 72, 72, 74, 78, 72 ,72 ,72 , 74},

    { -1, -1 , 77, 67, 73},

    { -1, 77, 25, 66, 71, 73, 77, 69, 70, 71, 73, 77, 69, 70, 71, 73, 77, 69, 70, 71, 73},
    { -1, 76, 68, 68, 67, 44, 46, 68, 66, 67, 25, 25, 66, 11, 17, 44, 46, 12, 36, 36, 2},
    { -1, 77, 9, 4, 66, 67, 66, 66, 4, 67, 23, 23, 68, 4, 67, 67, 68, 68, 24, 67, 73},
    { -1, 76, 22, 19, 66, 75 ,79 , 68, 9, 37, 75, 79, 9, 9, 66, 75, 79, 36, 66, 68, 2},
    { -1, 78, 72, 72, 72 ,74, 78, 72, 72, 72 ,74, 78, 72, 72, 72, 74, 78, 72 ,72 ,72 , 74},
  };


  std::vector<std::vector<int>> boss_level_grid(static_cast<int>(Ranges::LEVEL_FIVE_HEIGHT),
  std::vector<int>(static_cast<int>(Ranges::LEVEL_FIVE_WIDTH)));


  boss_level_grid = 
  {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, 77, 69, 70, 71, 29, 70, 71, 69, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 76, 22, 67, 68, 24, 23, 26, 22, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 66, 23, 67, 4, 66, 67, 27, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 76, 68, 67, 66, 66, 67, 23, 68, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 67, 66, 68, 66, 66, 68, 67, 73, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, 76, 66, 23, 66, 67, 23, 66, 66, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 67, 67, 68, 23, 68, 67, 67, 73, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 76, 68, 23, 66, 67, 66, 23, 66, 2, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 77, 66, 68, 68, 3, 67, 66, 68, 73, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, 76, 22, 66, 67, 68, 68, 66, 22, 2, -1, -1, -1, -1, -1},

    {-1, -1, -1, -1, 78, 72, 72, 72, 72, 72, 72, 72, 74, -1, -1, -1, -1, -1},
  };






  //Map first_level_map(first_level_grid); // making first level 
  // will later just push back each level

  // For now ill make just first level then later ill design others
  // maybe we can use Views here, so we dont make another 4 2D arrays

  this->maps_.insert(this->maps_.begin() + index, new Map(first_level_grid));
  this->findingOrcs(index);
  this->findMapObjects(index);

  index++;

  this->maps_.insert(this->maps_.begin() + index, new Map(second_level_grid));
  this->findingOrcs(index);
  this->findMapObjects(index);

  index++;

  this->maps_.insert(this->maps_.begin() + index, new Map(third_level_grid));
  this->findingOrcs(index);
  this->findMapObjects(index);

  index++;

  this->maps_.insert(this->maps_.begin() + index, new Map(fourth_level_grid));
  this->findingOrcs(index);
  this->findMapObjects(index);

  index++;

  this->maps_.insert(this->maps_.begin() + index, new Map(boss_level_grid));
  this->findingOrcs(index);
  this->findMapObjects(index);



  this->maps_.insert(this->maps_.begin() + static_cast<int>(Ranges::LEVELS), new Map(idle_zone_grid));
  this->findingOrcs(static_cast<int>(Ranges::LEVELS));
  this->findMapObjects(static_cast<int>(Ranges::LEVELS));

  

}

void Game::findingOrcs(int current_level) noexcept
{
  OrcType type;
  if(current_level <= 1) { type = OrcType::CLASSIC;}
  else if(current_level <= 3) { type = OrcType::PLATED;}
  else if(current_level == 4) { type = OrcType::ELITE;
  
  }
  for(int index = 0; index < this->getMaps()[current_level]->getGrid().size(); index++)
  {
    for(int inner = 0; inner < this->getMaps()[current_level]->getGrid()[index].size(); inner++)
    {
      if(this->getMaps()[current_level]->getGrid()[index][inner] == static_cast<int>(Grid::CHARACTER_ORC))
      {
        Character* placeholder = new Orc(type);
        placeholder->setYaxisCoords((float)index * static_cast<float>(Grid::TILE_SIZE));
        placeholder->setXaxisCoords((float)inner * static_cast<float>(Grid::TILE_SIZE));
        placeholder->setXcoordinate(inner);
        placeholder->setYcoordinate(index);
        this->getEnemiesOnLevel()[current_level].push_back(placeholder);
      }
    }
  }
}

void Game::findMapObjects(int current_level) noexcept
{
  Map* placeholder = this->getMaps()[current_level];

  for(int index = 0; index < placeholder->getGrid().size(); index++)
  {
    for(int inner = 0; inner < placeholder->getGrid()[index].size(); inner++)
    {
      int tag = placeholder->getGrid()[index][inner];

      if(tag == static_cast<int>(Grid::CANDLESTICK))
      {
        MapObjects* object = new Candlestick(); // Navodno ovo ne kopira
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::NEEDLES))
      {
        MapObjects* object = new Needles();
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::LADDERS))
      {
        MapObjects* object = new Ladder();
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::DOORS_VERTICAL) || tag == static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING) ||
      tag == static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING))
      {
        MapObjects* object = nullptr;
        if(tag == static_cast<int>(Grid::DOORS_VERTICAL)) { object = new Doors(current_level, DoorType::VERTICAL);}
        else if( tag == static_cast<int>(Grid::DOORS_HORIZONTAL_LEFT_WING)) { object = new Doors(current_level, DoorType::HORIZONTAL_LEFT);}
        else if( tag == static_cast<int>(Grid::DOORS_HORIZONTAL_RIGHT_WING)) { object = new Doors(current_level, DoorType::HORIZONTAL_RIGHT);}
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::TORCH_HORIZONTAL_WALL) || tag == static_cast<int>(Grid::TORCH_VERTICAL_LEFT_SIDE) 
      || tag == static_cast<int>(Grid::TORCH_VERTICAL_RIGHT_SIDE))
      {
        MapObjects* object = nullptr;

        if(tag == static_cast<int>(Grid::TORCH_HORIZONTAL_WALL)) { object = new Torch(TorchType::HORIZONTAL_TORCH);}
        else if( tag == static_cast<int>(Grid::TORCH_VERTICAL_LEFT_SIDE)) { object = new Torch(TorchType::VERTICAL_TORCH);}
        else if ( tag == static_cast<int>(Grid::TORCH_VERTICAL_RIGHT_SIDE)) { object = new Torch(TorchType::VERTICAL_TORCH_INVERTED);}


        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::SHOPKEEPER))
      {
        MapObjects* object = new Shopkeeper();
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::BANNER))
      {
        MapObjects* object = new Banner();
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::CHEST) || tag == static_cast<int>(Grid::CHEST_MINI))
      {
        MapObjects* object = nullptr;
        if(tag == static_cast<int>(Grid::CHEST)) { object = new Chest(ChestType::BIG_CHEST);}
        else if( tag == static_cast<int>(Grid::CHEST_MINI)) { object = new Chest(ChestType::MINI_CHEST);}

        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::BOX_IRON_BIG) || tag == static_cast<int>(Grid::BOX_IRON_SMALL)
      || tag == static_cast<int>(Grid::BOX_WOOD_BIG) || tag == static_cast<int>(Grid::BOX_WOOD_SMALL))
      {
        MapObjects* object = nullptr;
        if(tag == static_cast<int>(Grid::BOX_IRON_BIG)) { object = new Box(BoxType::IRON_BIG_BOX);}
        else if(tag == static_cast<int>(Grid::BOX_IRON_SMALL)) { object = new Box(BoxType::IRON_MINI_BOX);}
        else if(tag == static_cast<int>(Grid::BOX_WOOD_BIG)) { object = new Box(BoxType::WOOD_BIG_BOX);}
        else if(tag == static_cast<int>(Grid::BOX_WOOD_SMALL)) { object = new Box(BoxType::WOOD_MINI_BOX);}

        

        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::SILVER_KEY) || tag == static_cast<int>(Grid::GOLD_KEY))
      {
        MapObjects* object = nullptr;
        if(tag == static_cast<int>(Grid::SILVER_KEY)) { object = new Key(KeyType::SILVER_KEY);}
        else if(tag == static_cast<int>(Grid::GOLD_KEY)) { object = new Key(KeyType::GOLD_KEY);}
        

        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::FLAMETHROWER_VERTICAL) || tag == static_cast<int>(Grid::FLAMETHROWER_HORIZONTAL))
      {
        MapObjects* object = nullptr;
        if(tag == static_cast<int>(Grid::FLAMETHROWER_VERTICAL)) { object = new Flamethrower(FlamethrowerType::VERTICAL);}
        else if(tag == static_cast<int>(Grid::FLAMETHROWER_HORIZONTAL)) { object = new Flamethrower(FlamethrowerType::HORIZONTAL);}
        

        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
      else if( tag == static_cast<int>(Grid::ARROW_TRAP))
      {
        MapObjects* object = new ArrowTrap();
        object->setXCoord(inner);
        object->setYCoord(index);
        placeholder->getMapObjects().push_back(object);
      }
    }
  }
}


void Game::loadTextures(Tools* main_tools) noexcept
{
  // Map(textures)

  // Floor
  SDL_Surface* surface_for_floor = IMG_Load("design/texture/floorForBegining.png");
  SDL_Texture* texture_for_floor = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_floor);
  SDL_FreeSurface(surface_for_floor);

  SDL_Surface* surface_for_floor_new_first = IMG_Load("design/texture/FloorNewOne.png");
  SDL_Texture* texture_for_floor_new_first = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_floor_new_first);
  SDL_FreeSurface(surface_for_floor_new_first);

  SDL_Surface* surface_for_floor_new_second = IMG_Load("design/texture/FloorNewTwo.png");
  SDL_Texture* texture_for_floor_new_second = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_floor_new_second);
  SDL_FreeSurface(surface_for_floor_new_second);

  SDL_Surface* surface_for_floor_new_three = IMG_Load("design/texture/FloorNewThird.png");
  SDL_Texture* texture_for_floor_new_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_floor_new_three);
  SDL_FreeSurface(surface_for_floor_new_three);

  // Vertical Wall
  SDL_Surface* surface_for_vertical_wall = IMG_Load("design/texture/verticalWall.png");
  SDL_Texture* texture_for_vertical_wall = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall);
  SDL_FreeSurface(surface_for_vertical_wall);

  SDL_Surface* surface_for_vertical_wall_new_first = IMG_Load("design/texture/WallVerticalSecond.png");
  SDL_Texture* texture_for_vertical_wall_new_first = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall_new_first);
  SDL_FreeSurface(surface_for_vertical_wall_new_first);

  SDL_Surface* surface_for_vertical_wall_new_second = IMG_Load("design/texture/WallVerticalEdgesDown.png");
  SDL_Texture* texture_for_vertical_wall_new_second = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall_new_second);
  SDL_FreeSurface(surface_for_vertical_wall_new_second);

  SDL_Surface* surface_for_vertical_wall_padding_left = IMG_Load("design/texture/WallVerticalLeftPadding.png");
  SDL_Texture* texture_for_vertical_wall_padding_left = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall_padding_left);
  SDL_FreeSurface(surface_for_vertical_wall_padding_left);

  SDL_Surface* surface_for_vertical_wall_downside_with_padding = IMG_Load("design/texture/WallVerticalDownSideLeftPadding.png");
  SDL_Texture* texture_for_vertical_wall_downside_with_padding = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall_downside_with_padding);
  SDL_FreeSurface(surface_for_vertical_wall_downside_with_padding);

  SDL_Surface* surface_for_vertical_wall_two_squares_with_padding = IMG_Load("design/texture/WallVerticalNewTwoSquaresLeftPadding.png");
  SDL_Texture* texturee_for_vertical_wall_two_squares_with_padding = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_vertical_wall_two_squares_with_padding);
  SDL_FreeSurface(surface_for_vertical_wall_two_squares_with_padding);

  // Horizontal Wall
  SDL_Surface* surface_for_horizontal_wall = IMG_Load("design/texture/horizontalWall.png");
  SDL_Texture* texture_for_horizontal_wall = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_horizontal_wall);
  SDL_FreeSurface(surface_for_horizontal_wall);

  SDL_Surface* surface_for_horizontal_wall_new_first = IMG_Load("design/texture/HorizontalWallFirst.png");
  SDL_Texture* texture_for_horizontal_wall_new_first = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_horizontal_wall_new_first);
  SDL_FreeSurface(surface_for_horizontal_wall_new_first);

  SDL_Surface* surface_for_horizontal_wall_new_second = IMG_Load("design/texture/HorizontalWallSecond.png");
  SDL_Texture* texture_for_horizontal_wall_new_second = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_horizontal_wall_new_second);
  SDL_FreeSurface(surface_for_horizontal_wall_new_second);

  SDL_Surface* surface_for_horizontal_wall_new_third = IMG_Load("design/texture/HorizontalWallThird.png");
  SDL_Texture* texture_for_horizontal_wall_new_third = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_horizontal_wall_new_third);
  SDL_FreeSurface(surface_for_horizontal_wall_new_third);

  SDL_Surface* surface_for_horizontal_wall_down_side = IMG_Load("design/texture/WallHorizontalDownNewFirst.png");
  SDL_Texture* texture_for_horizontal_wall_down_side = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_horizontal_wall_down_side);
  SDL_FreeSurface(surface_for_horizontal_wall_down_side);

  //Corner Walls

  SDL_Surface* surface_for_corner_wall_top_left = IMG_Load("design/texture/CornerWallTOPLEFT.png");
  SDL_Texture* texture_for_corner_wall_top_left = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_corner_wall_top_left);
  SDL_FreeSurface(surface_for_corner_wall_top_left);

  SDL_Surface* surface_for_corner_wall_top_right = IMG_Load("design/texture/WallEdgeTopRightCorner.png");
  SDL_Texture* texture_for_corner_wall_top_right = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_corner_wall_top_right);
  SDL_FreeSurface(surface_for_corner_wall_top_right);
  // ubaci u mapu

  //Chars
  SDL_Surface* surface_for_soldier = IMG_Load("design/soldierStanding.png");
  SDL_Texture* texture_for_soldier = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier);
  SDL_FreeSurface(surface_for_soldier);

  SDL_Surface* surface_for_orc = IMG_Load("design/OrcStanding.png");
  SDL_Texture* texture_for_orc = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc);
  SDL_FreeSurface(surface_for_orc);

  SDL_Surface* surface_for_full_hearth = IMG_Load("design/HearthFull.png");
  SDL_Texture* texture_for_full_hearth = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_full_hearth);
  SDL_FreeSurface(surface_for_full_hearth);

  SDL_Surface* surface_for_half_hearth = IMG_Load("design/HalfHearth.png");
  SDL_Texture* texture_for_half_hearth = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_half_hearth);
  SDL_FreeSurface(surface_for_half_hearth);

  SDL_Surface* surface_for_empty_hearth = IMG_Load("design/HearthEmpty.png");
  SDL_Texture* texture_for_empty_hearth = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_empty_hearth);
  SDL_FreeSurface(surface_for_empty_hearth);


  //Items

  SDL_Surface* surface_for_doors_vertical = IMG_Load("design/DoorsVerticalPixel.png");
  SDL_Texture* texture_for_doors_vertical = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_doors_vertical);
  SDL_FreeSurface(surface_for_doors_vertical);

  SDL_Surface* surface_for_coin = IMG_Load("design/coin.png");
  SDL_Texture* texture_for_coin = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_coin);
  SDL_FreeSurface(surface_for_coin);

  SDL_Surface* surface_for_mushroom = IMG_Load("design/MushroomRed.png");
  SDL_Texture* texture_for_mushroom = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_mushroom);
  SDL_FreeSurface(surface_for_mushroom);

  SDL_Surface* surface_for_sapphire_ring = IMG_Load("design/RingSapphireGold.png");
  SDL_Texture* texture_for_sapphire_ring = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_sapphire_ring);
  SDL_FreeSurface(surface_for_sapphire_ring);

  SDL_Surface* surface_for_health_pot = IMG_Load("design/HealthPotionMediumcopy.png");
  SDL_Texture* texture_for_health_pot = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_health_pot);
  SDL_FreeSurface(surface_for_health_pot);

  SDL_Surface* surface_for_ring_ruby = IMG_Load("design/RingRuby.png");
  SDL_Texture* texture_for_ring_ruby = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_ring_ruby);
  SDL_FreeSurface(surface_for_ring_ruby);

  SDL_Surface* surface_for_ring_sapphire = IMG_Load("design/RingSapphire.png");
  SDL_Texture* texture_for_ring_sapphire = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_ring_sapphire);
  SDL_FreeSurface(surface_for_ring_sapphire);

  SDL_Surface* surface_for_stone_sword = IMG_Load("design/StoneSword.png");
  SDL_Texture* texture_for_stone_sword = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_stone_sword);
  SDL_FreeSurface(surface_for_stone_sword);

  SDL_Surface* surface_for_gold_sword = IMG_Load("design/GoldSword.png");
  SDL_Texture* texture_for_gold_sword = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_gold_sword);
  SDL_FreeSurface(surface_for_gold_sword);

  SDL_Surface* surface_for_big_gold_sword = IMG_Load("design/SwordWideGold.png");
  SDL_Texture* texture_for_big_gold_sword = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_big_gold_sword);
  SDL_FreeSurface(surface_for_big_gold_sword);

  SDL_Surface* surface_for_charm_ruby = IMG_Load("design/CharmRuby.png");
  SDL_Texture* texture_for_charm_ruby = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_charm_ruby);
  SDL_FreeSurface(surface_for_charm_ruby);

  SDL_Surface* surface_for_charm_ruby_gold = IMG_Load("design/CharmRubyGold.png");
  SDL_Texture* texture_for_charm_ruby_gold = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_charm_ruby_gold);
  SDL_FreeSurface(surface_for_charm_ruby_gold);

  SDL_Surface* surface_for_charm_sapphire = IMG_Load("design/CharmSapphire.png");
  SDL_Texture* texture_for_charm_sapphire = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_charm_sapphire);
  SDL_FreeSurface(surface_for_charm_sapphire);

  SDL_Surface* surface_for_skeleton_head = IMG_Load("design/SkeletonHead.png");
  SDL_Texture* texture_for_skeleton_head = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_skeleton_head);
  SDL_FreeSurface(surface_for_skeleton_head);

  SDL_Surface* surface_for_skeleton_bones = IMG_Load("design/SkeletonBones.png");
  SDL_Texture* texture_for_skeleton_bones = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_skeleton_bones);
  SDL_FreeSurface(surface_for_skeleton_bones);

  SDL_Surface* surface_big_cobweb = IMG_Load("design/BigCobweb.png");
  SDL_Texture* texture_big_cobweb = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_cobweb);
  SDL_FreeSurface(surface_big_cobweb);

  SDL_Surface* surface_small_cobweb = IMG_Load("design/SmallCobweb.png");
  SDL_Texture* texture_small_cobweb = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_cobweb);
  SDL_FreeSurface(surface_small_cobweb);

  SDL_Surface* surface_horizontal_doors_left_wing = IMG_Load("design/HorizontalDoorsLeftWing.png");
  SDL_Texture* texture_horizontal_doors_left_wing = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_doors_left_wing);
  SDL_FreeSurface(surface_horizontal_doors_left_wing);

  SDL_Surface* surface_horizontal_doors_right_wing = IMG_Load("design/HorizontalDoorsRightWing.png");
  SDL_Texture* texture_horizontal_doors_right_wing = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_doors_right_wing);
  SDL_FreeSurface(surface_horizontal_doors_right_wing);

  // Chains!

  SDL_Surface* surface_chains_one = IMG_Load("design/ChainOne.png");
  SDL_Texture* texture_chains_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_chains_one);
  SDL_FreeSurface(surface_chains_one);

  SDL_Surface* surface_chains_two = IMG_Load("design/ChainTwo.png");
  SDL_Texture* texture_chains_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_chains_two);
  SDL_FreeSurface(surface_chains_two);

  textures_for_map[Grid::CHAIN_ONE] = texture_chains_one;
  textures_for_map[Grid::CHAIN_TWO] = texture_chains_two;



  textures_for_map[Grid::FLOOR] = texture_for_floor;
  textures_for_map[Grid::FLOOR_NEW_ONE] = texture_for_floor_new_first;
  textures_for_map[Grid::FLOOR_NEW_TWO] = texture_for_floor_new_second;
  textures_for_map[Grid::FLOOR_NEW_THREE] = texture_for_floor_new_three;

  textures_for_map[Grid::WALL_VERTICAL] = texture_for_vertical_wall;
  textures_for_map[Grid::WALL_VERTICAL_NEW] = texture_for_vertical_wall_new_first;
  textures_for_map[Grid::WALL_VERTICAL_EDGE_DOWNSIDE] = texture_for_vertical_wall_new_second;
  textures_for_map[Grid::WALL_VERTICAL_LEFT_CLASSIC_PADDING] = texture_for_vertical_wall_padding_left;
  textures_for_map[Grid::WALL_VERTICAL_NEW_DOWNSIDE_WITH_PADDING] = texture_for_vertical_wall_downside_with_padding;
  textures_for_map[Grid::WALL_VERTICAL_NEW_WITH_PADDING] = texturee_for_vertical_wall_two_squares_with_padding;

  textures_for_map[Grid::WALL_HORIZONTAL] = texture_for_horizontal_wall;
  textures_for_map[Grid::WALL_HORIZONTAL_NEW_ONE] = texture_for_horizontal_wall_new_first;
  textures_for_map[Grid::WALL_HORIZONTAL_NEW_TWO] = texture_for_horizontal_wall_new_second;
  textures_for_map[Grid::WALL_HORIZONTAL_NEW_THREE] = texture_for_horizontal_wall_new_third;
  textures_for_map[Grid::WALL_HORIZONTAL_NEW_DOWNSIDE] = texture_for_horizontal_wall_down_side;

  textures_for_map[Grid::WALL_CORNER_TOP_LEFT] = texture_for_corner_wall_top_left;
  textures_for_map[Grid::WALL_CORNER_TOP_RIGHT] = texture_for_corner_wall_top_right;


  textures_for_map[Grid::CHARACTER_SOLD] = texture_for_soldier;
  textures_for_map[Grid::CHARACTER_ORC] = texture_for_orc;
  textures_for_map[Grid::HEARTH_FULL] = texture_for_full_hearth;
  textures_for_map[Grid::HEARTH_HALF] = texture_for_half_hearth;
  textures_for_map[Grid::HEARTH_EMPTY] = texture_for_empty_hearth;
  textures_for_map[Grid::COIN] = texture_for_coin;
  textures_for_map[Grid::MUSHROOM] = texture_for_mushroom;
  textures_for_map[Grid::RING_SAPPHIRE_GOLD] = texture_for_sapphire_ring;
  textures_for_map[Grid::HEALTH_POT] = texture_for_health_pot;
  textures_for_map[Grid::RING_RUBY] = texture_for_ring_ruby;
  textures_for_map[Grid::RING_SAPPHIRE] = texture_for_ring_sapphire;
  textures_for_map[Grid::STONE_SWORD] = texture_for_stone_sword;
  textures_for_map[Grid::GOLD_SWORD] = texture_for_gold_sword;
  textures_for_map[Grid::BIG_GOLD_SWORD]= texture_for_big_gold_sword;
  textures_for_map[Grid::TRINKET_RUBY] = texture_for_charm_ruby;
  textures_for_map[Grid::TRINKET_RUBY_GOLD] = texture_for_charm_ruby_gold;
  textures_for_map[Grid::TRINKET_SAPPHIRE] = texture_for_charm_sapphire;
  textures_for_map[Grid::DOORS_VERTICAL] = texture_for_doors_vertical;
  textures_for_map[Grid::SKELETON_HEAD] = texture_for_skeleton_head;
  textures_for_map[Grid::SKELETON_BONES] = texture_for_skeleton_bones;
  textures_for_map[Grid::BIG_COBWEB] = texture_big_cobweb;
  textures_for_map[Grid::SMALL_COBWEB] = texture_small_cobweb;
  textures_for_map[Grid::DOORS_HORIZONTAL_RIGHT_WING] = texture_horizontal_doors_right_wing;
  textures_for_map[Grid::DOORS_HORIZONTAL_LEFT_WING] = texture_horizontal_doors_left_wing;

  //Idle Frames!
  SDL_Surface* surface_for_soldier_idle_one = IMG_Load("design/SoldierIdleOne.png");
  SDL_Texture* texture_for_soldier_idle_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_one);
  SDL_FreeSurface(surface_for_soldier_idle_one);

  SDL_Surface* surface_for_soldier_idle_two = IMG_Load("design/SoldierIdleTwo.png");
  SDL_Texture* texture_for_soldier_idle_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_two);
  SDL_FreeSurface(surface_for_soldier_idle_two);

  SDL_Surface* surface_for_soldier_idle_three = IMG_Load("design/SoldierIdleThree.png");
  SDL_Texture* texture_for_soldier_idle_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_three);
  SDL_FreeSurface(surface_for_soldier_idle_three);

  SDL_Surface* surface_for_soldier_idle_four = IMG_Load("design/SoldierIdleFour.png");
  SDL_Texture* texture_for_soldier_idle_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_four);
  SDL_FreeSurface(surface_for_soldier_idle_four);

  SDL_Surface* surface_for_soldier_idle_five = IMG_Load("design/SoldierIdleFive.png");
  SDL_Texture* texture_for_soldier_idle_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_five);
  SDL_FreeSurface(surface_for_soldier_idle_five);

  SDL_Surface* surface_for_soldier_idle_six = IMG_Load("design/SoldierIdleSix.png");
  SDL_Texture* texture_for_soldier_idle_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_idle_six);
  SDL_FreeSurface(surface_for_soldier_idle_six);

  // Constr
  SDL_Surface* surface_for_orc_idle_one = IMG_Load("design/OrcIdleOne.png");
  SDL_Texture* texture_for_orc_idle_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_one);
  SDL_FreeSurface(surface_for_orc_idle_one);

  SDL_Surface* surface_for_orc_idle_two = IMG_Load("design/OrcIdleTwo.png");
  SDL_Texture* texture_for_orc_idle_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_two);
  SDL_FreeSurface(surface_for_orc_idle_two);

  SDL_Surface* surface_for_orc_idle_three = IMG_Load("design/OrcIdleThree.png");
  SDL_Texture* texture_for_orc_idle_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_three);
  SDL_FreeSurface(surface_for_orc_idle_three);

  SDL_Surface* surface_for_orc_idle_four = IMG_Load("design/OrcIdleFour.png");
  SDL_Texture* texture_for_orc_idle_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_four);
  SDL_FreeSurface(surface_for_orc_idle_four);

  SDL_Surface* surface_for_orc_idle_five = IMG_Load("design/OrcIdleFive.png");
  SDL_Texture* texture_for_orc_idle_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_five);
  SDL_FreeSurface(surface_for_orc_idle_five);

  SDL_Surface* surface_for_orc_idle_six = IMG_Load("design/OrcIdleSix.png");
  SDL_Texture* texture_for_orc_idle_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_idle_six);
  SDL_FreeSurface(surface_for_orc_idle_six);


  //Attacking Frames!
  SDL_Surface* surface_for_soldier_attack_first_anim = IMG_Load("design/soldierAttackAnimationFirst.png");
  SDL_Texture* texture_for_soldier_attack_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_attack_first_anim);
  SDL_FreeSurface(surface_for_soldier_attack_first_anim);

  SDL_Surface* surface_for_soldier_attack_second_anim = IMG_Load("design/SoldierAttackAnimationTwo.png");
  SDL_Texture* texture_for_soldier_attack_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_attack_second_anim);
  SDL_FreeSurface(surface_for_soldier_attack_second_anim);

  SDL_Surface* surface_for_soldier_attack_third_anim = IMG_Load("design/SoldierAttackAnimationThree.png");
  SDL_Texture* texture_for_soldier_attack_third_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_attack_third_anim);
  SDL_FreeSurface(surface_for_soldier_attack_third_anim);

  SDL_Surface* surface_for_soldier_attack_fourth_anim = IMG_Load("design/SoldierAttackAnimationFourth.png");
  SDL_Texture* texture_for_soldier_attack_fourth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_attack_fourth_anim);
  SDL_FreeSurface(surface_for_soldier_attack_fourth_anim);

  SDL_Surface* surface_for_soldier_attack_fifth_anim = IMG_Load("design/SoldierAttackAnimationsFive.png");
  SDL_Texture* texture_for_soldier_attack_fifth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_attack_fifth_anim);
  SDL_FreeSurface(surface_for_soldier_attack_fifth_anim);

  SDL_Surface* surface_for_orc_attacking_first_anim = IMG_Load("design/OrcAttackAnimationFirst.png");
  SDL_Texture* texture_for_orc_attacking_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_attacking_first_anim);
  SDL_FreeSurface(surface_for_orc_attacking_first_anim);

  SDL_Surface* surface_for_orc_attacking_second_anim = IMG_Load("design/OrcAttackingAnimationSecond.png");
  SDL_Texture* texture_for_orc_attacking_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_attacking_second_anim);
  SDL_FreeSurface(surface_for_orc_attacking_second_anim);

  SDL_Surface* surface_for_orc_attacking_three_anim = IMG_Load("design/OrcAttackAnimationThree.png");
  SDL_Texture* texture_for_orc_attacking_three_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_attacking_three_anim);
  SDL_FreeSurface(surface_for_orc_attacking_three_anim);

  SDL_Surface* surface_for_orc_attacking_four_anim = IMG_Load("design/OrcAttackAnimationFour.png");
  SDL_Texture* texture_for_orc_attacking_four_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_attacking_four_anim);
  SDL_FreeSurface(surface_for_orc_attacking_four_anim);

  SDL_Surface* surface_for_orc_attacking_five_anim = IMG_Load("design/OrcAttackAnimationFive.png");
  SDL_Texture* texture_for_orc_attacking_five_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_attacking_five_anim);
  SDL_FreeSurface(surface_for_orc_attacking_five_anim);

  //Walking Frames!

  SDL_Surface* surface_for_soldier_walking_first_anim = IMG_Load("design/SoldierWalkingFirstAnimation.png");
  SDL_Texture* texture_for_soldier_walking_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_first_anim);
  SDL_FreeSurface(surface_for_soldier_walking_first_anim);

  SDL_Surface* surface_for_soldier_walking_second_anim = IMG_Load("design/SoldierWalkingSecondAnimation.png");
  SDL_Texture* texture_for_soldier_walking_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_second_anim);
  SDL_FreeSurface(surface_for_soldier_walking_second_anim);

  SDL_Surface* surface_for_soldier_walking_third_anim = IMG_Load("design/SoldierWalkingThirdAnimation.png");
  SDL_Texture* texture_for_soldier_walking_third_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_third_anim);
  SDL_FreeSurface(surface_for_soldier_walking_third_anim);

  SDL_Surface* surface_for_soldier_walking_fourth_anim = IMG_Load("design/SoldierWalkingFourthAnimation.png");
  SDL_Texture* texture_for_soldier_walking_fourth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_fourth_anim);
  SDL_FreeSurface(surface_for_soldier_walking_fourth_anim);

  SDL_Surface* surface_for_soldier_walking_fifth_anim = IMG_Load("design/SoldierWalkingFifthAnimation.png");
  SDL_Texture* texture_for_soldier_walking_fifth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_fifth_anim);
  SDL_FreeSurface(surface_for_soldier_walking_fifth_anim);

  SDL_Surface* surface_for_soldier_walking_sixth_anim = IMG_Load("design/SoldierWalkingSixthAnimation.png");
  SDL_Texture* texture_for_soldier_walking_sixth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_sixth_anim);
  SDL_FreeSurface(surface_for_soldier_walking_sixth_anim);

  SDL_Surface* surface_for_soldier_walking_seventh_anim = IMG_Load("design/SoldierWalkingSeventhAnimation.png");
  SDL_Texture* texture_for_soldier_walking_seventh_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_walking_seventh_anim);
  SDL_FreeSurface(surface_for_soldier_walking_seventh_anim);

  SDL_Surface* surface_for_orc_walking_first_anim = IMG_Load("design/OrcWalkAnimationFirst.png");
  SDL_Texture* texture_for_orc_walking_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_first_anim);
  SDL_FreeSurface(surface_for_orc_walking_first_anim);

  SDL_Surface* surface_for_orc_walking_second_anim = IMG_Load("design/OrcWalkAnimationSecond.png");
  SDL_Texture* texture_for_orc_walking_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_second_anim);
  SDL_FreeSurface(surface_for_orc_walking_second_anim);

  SDL_Surface* surface_for_orc_walking_three_anim = IMG_Load("design/OrcWalkAnimationThree.png");
  SDL_Texture* texture_for_orc_walking_three_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_three_anim);
  SDL_FreeSurface(surface_for_orc_walking_three_anim);

  SDL_Surface* surface_for_orc_walking_four_anim = IMG_Load("design/OrcWalkAnimationFour.png");
  SDL_Texture* texture_for_orc_walking_four_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_four_anim);
  SDL_FreeSurface(surface_for_orc_walking_four_anim);

  SDL_Surface* surface_for_orc_walking_five_anim = IMG_Load("design/OrcWalkAnimationFive.png");
  SDL_Texture* texture_for_orc_walking_five_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_five_anim);
  SDL_FreeSurface(surface_for_orc_walking_five_anim);

  SDL_Surface* surface_for_orc_walking_six_anim = IMG_Load("design/OrcWalkAnimationSix.png");
  SDL_Texture* texture_for_orc_walking_six_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_six_anim);
  SDL_FreeSurface(surface_for_orc_walking_six_anim);

  SDL_Surface* surface_for_orc_walking_seven_anim = IMG_Load("design/OrcWalkAnimationSeven.png");
  SDL_Texture* texture_for_orc_walking_seven_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_walking_seven_anim);
  SDL_FreeSurface(surface_for_orc_walking_seven_anim);

  // Special Ability !

  SDL_Surface* surface_for_soldier_special_attack_one = IMG_Load("design/SoldierSpecialAttackOne.png");
  SDL_Texture* texture_for_soldier_special_attack_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_one);
  SDL_FreeSurface(surface_for_soldier_special_attack_one);

  SDL_Surface* surface_for_soldier_special_attack_two = IMG_Load("design/SoldierSpecialAttackTwo.png");
  SDL_Texture* texture_for_soldier_special_attack_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_two);
  SDL_FreeSurface(surface_for_soldier_special_attack_two);

  SDL_Surface* surface_for_soldier_special_attack_three = IMG_Load("design/SoldierSpecialAttackThree.png");
  SDL_Texture* texture_for_soldier_special_attack_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_three);
  SDL_FreeSurface(surface_for_soldier_special_attack_three);

  SDL_Surface* surface_for_soldier_special_attack_four = IMG_Load("design/SoldierSpecialAttackFour.png");
  SDL_Texture* texture_for_soldier_special_attack_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_four);
  SDL_FreeSurface(surface_for_soldier_special_attack_four);

  SDL_Surface* surface_for_soldier_special_attack_five = IMG_Load("design/SoldierSpecialAttackFive.png");
  SDL_Texture* texture_for_soldier_special_attack_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_five);
  SDL_FreeSurface(surface_for_soldier_special_attack_five);

  SDL_Surface* surface_for_soldier_special_attack_six = IMG_Load("design/SoldierSpecialAttackSix.png");
  SDL_Texture* texture_for_soldier_special_attack_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_special_attack_six);
  SDL_FreeSurface(surface_for_soldier_special_attack_six);

  // Hurt Frames!

  SDL_Surface* surface_for_soldier_hurt_first_anim = IMG_Load("design/SoldierHurtAnimationOne.png");
  SDL_Texture* texture_for_soldier_hurt_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_hurt_first_anim);
  SDL_FreeSurface(surface_for_soldier_hurt_first_anim);

  SDL_Surface* surface_for_soldier_hurt_second_anim = IMG_Load("design/SoldierHurtAnimationTwo.png");
  SDL_Texture* texture_for_soldier_hurt_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_hurt_second_anim);
  SDL_FreeSurface(surface_for_soldier_hurt_second_anim);

  SDL_Surface* surface_for_soldier_hurt_third_anim = IMG_Load("design/SoldierHurtAnimationThree.png");
  SDL_Texture* texture_for_soldier_hurt_third_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_hurt_third_anim);
  SDL_FreeSurface(surface_for_soldier_hurt_third_anim);

  SDL_Surface* surface_for_soldier_hurt_four_anim = IMG_Load("design/SoldierHurtAnimationFour.png");
  SDL_Texture* texture_for_soldier_hurt_four_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_soldier_hurt_four_anim);
  SDL_FreeSurface(surface_for_soldier_hurt_four_anim);

  SDL_Surface* surface_for_orc_hurt_first_anim = IMG_Load("design/OrcHurtAnimationOne.png");
  SDL_Texture* texture_for_orc_hurt_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_hurt_first_anim);
  SDL_FreeSurface(surface_for_orc_hurt_first_anim);

  SDL_Surface* surface_for_orc_hurt_second_anim = IMG_Load("design/OrcHurtAnimationTwo.png");
  SDL_Texture* texture_for_orc_hurt_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_hurt_second_anim);
  SDL_FreeSurface(surface_for_orc_hurt_second_anim);

  SDL_Surface* surface_for_orc_hurt_third_anim = IMG_Load("design/OrcHurtAnimationThree.png");
  SDL_Texture* texture_for_orc_hurt_third_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_hurt_third_anim);
  SDL_FreeSurface(surface_for_orc_hurt_third_anim);

  SDL_Surface* surface_for_orc_hurt_fourth_anim = IMG_Load("design/OrcHurtAnimationFour.png");
  SDL_Texture* texture_for_orc_hurt_fourth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_hurt_fourth_anim);
  SDL_FreeSurface(surface_for_orc_hurt_fourth_anim);

  // Death Animations !

  SDL_Surface* surface_for_orc_death_first_anim = IMG_Load("design/OrcDeathAnimationOne.png");
  SDL_Texture* texture_for_orc_death_first_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_death_first_anim);
  SDL_FreeSurface(surface_for_orc_death_first_anim);

  SDL_Surface* surface_for_orc_death_second_anim = IMG_Load("design/OrcDeathAnimationTwo.png");
  SDL_Texture* texture_for_orc_death_second_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_death_second_anim);
  SDL_FreeSurface(surface_for_orc_death_second_anim);

  SDL_Surface* surface_for_orc_death_third_anim = IMG_Load("design/OrcDeathAnimationThree.png");
  SDL_Texture* texture_for_orc_death_third_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_death_third_anim);
  SDL_FreeSurface(surface_for_orc_death_third_anim);

  SDL_Surface* surface_for_orc_death_fourth_anim = IMG_Load("design/OrcDeathAnimationFour.png");
  SDL_Texture* texture_for_orc_death_fourth_anim = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_orc_death_fourth_anim);
  SDL_FreeSurface(surface_for_orc_death_fourth_anim);


  //Map Objects !

  //Candlestick !
  SDL_Surface* surface_for_candlestick_first = IMG_Load("design/CandleStickOne.png");
  SDL_Texture* texture_for_candlestick_first = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_candlestick_first);
  SDL_FreeSurface(surface_for_candlestick_first);

  SDL_Surface* surface_for_candlestick_second = IMG_Load("design/CandleStickTwo.png");
  SDL_Texture* texture_for_candlestick_second = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_candlestick_second);
  SDL_FreeSurface(surface_for_candlestick_second);

  SDL_Surface* surface_for_candlestick_third = IMG_Load("design/CandleStickThree.png");
  SDL_Texture* texture_for_candlestick_third = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_candlestick_third);
  SDL_FreeSurface(surface_for_candlestick_third);

  SDL_Surface* surface_for_candlestick_fourth = IMG_Load("design/CandleStickThree.png");
  SDL_Texture* texture_for_candlestick_fourth = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_candlestick_fourth);
  SDL_FreeSurface(surface_for_candlestick_fourth);


  // Needles
  SDL_Surface* surface_for_needles_first = IMG_Load("design/NeedlesOne.png");
  SDL_Texture* texture_for_needles_first = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_needles_first);
  SDL_FreeSurface(surface_for_needles_first);

  SDL_Surface* surface_for_needles_second = IMG_Load("design/NeedlesTwo.png");
  SDL_Texture* texture_for_needles_second = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_needles_second);
  SDL_FreeSurface(surface_for_needles_second);

  SDL_Surface* surface_for_needles_thrid = IMG_Load("design/NeedlesThree.png");
  SDL_Texture* texture_for_needles_third = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_needles_thrid);
  SDL_FreeSurface(surface_for_needles_thrid);

  SDL_Surface* surface_for_needles_fourth = IMG_Load("design/NeedlesFour.png");
  SDL_Texture* texture_for_needles_fourth = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_needles_fourth);
  SDL_FreeSurface(surface_for_needles_fourth);

  // Ladder
  SDL_Surface* surface_for_ladders = IMG_Load("design/Ladders.png");
  SDL_Texture* texture_for_ladders = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_ladders);
  SDL_FreeSurface(surface_for_ladders);

  //Torch for Horizontal walls!

  SDL_Surface* surface_for_torch_horizontal_one = IMG_Load("design/TorchOne.png");
  SDL_Texture* texture_for_torch_horizontal_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_horizontal_one);
  SDL_FreeSurface(surface_for_torch_horizontal_one);

  SDL_Surface* surface_for_torch_horizontal_two = IMG_Load("design/TorchTwo.png");
  SDL_Texture* texture_for_torch_horizontal_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_horizontal_two);
  SDL_FreeSurface(surface_for_torch_horizontal_two);

  SDL_Surface* surface_for_torch_horizontal_three = IMG_Load("design/TorchThree.png");
  SDL_Texture* texture_for_torch_horizontal_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_horizontal_three);
  SDL_FreeSurface(surface_for_torch_horizontal_three);

  SDL_Surface* surface_for_torch_horizontal_four = IMG_Load("design/TorchFour.png");
  SDL_Texture* texture_for_torch_horizontal_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_horizontal_four);
  SDL_FreeSurface(surface_for_torch_horizontal_four);

  // Torch for Vertical Walls!

  SDL_Surface* surface_for_torch_vertical_one = IMG_Load("design/VerticalTorchOne.png");
  SDL_Texture* texture_for_torch_vertical_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_vertical_one);
  SDL_FreeSurface(surface_for_torch_vertical_one);

  SDL_Surface* surface_for_torch_vertical_two = IMG_Load("design/VerticalTorchTwo.png");
  SDL_Texture* texture_for_torch_vertical_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_vertical_two);
  SDL_FreeSurface(surface_for_torch_vertical_two);

  SDL_Surface* surface_for_torch_vertical_three = IMG_Load("design/VerticalTorchThree.png");
  SDL_Texture* texture_for_torch_vertical_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_vertical_three);
  SDL_FreeSurface(surface_for_torch_vertical_three);

  SDL_Surface* surface_for_torch_vertical_four = IMG_Load("design/VerticalTorchFour.png");
  SDL_Texture* texture_for_torch_vertical_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_torch_vertical_four);
  SDL_FreeSurface(surface_for_torch_vertical_four);

  // ShopKeeper/Priest Look

  SDL_Surface* surface_shopkeeper_one = IMG_Load("design/PriestOne.png");
  SDL_Texture* texture_shopkeeper_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_shopkeeper_one);
  SDL_FreeSurface(surface_shopkeeper_one);

  SDL_Surface* surface_shopkeeper_two = IMG_Load("design/PriestTwo.png");
  SDL_Texture* texture_shopkeeper_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_shopkeeper_two);
  SDL_FreeSurface(surface_shopkeeper_two);

  SDL_Surface* surface_shopkeeper_three = IMG_Load("design/PriestThree.png");
  SDL_Texture* texture_shopkeeper_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_shopkeeper_three);
  SDL_FreeSurface(surface_shopkeeper_three);

  SDL_Surface* surface_shopkeeper_four = IMG_Load("design/PriestFour.png");
  SDL_Texture* texture_shopkeeper_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_shopkeeper_four);
  SDL_FreeSurface(surface_shopkeeper_four);

  //Banner !

  SDL_Surface* surface_banner_one = IMG_Load("design/BannerOne.png");
  SDL_Texture* texture_banner_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_banner_one);
  SDL_FreeSurface(surface_banner_one);

  SDL_Surface* surface_banner_two = IMG_Load("design/BannerTwo.png");
  SDL_Texture* texture_banner_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_banner_two);
  SDL_FreeSurface(surface_banner_two);

  SDL_Surface* surface_banner_three = IMG_Load("design/BannerThree.png");
  SDL_Texture* texture_banner_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_banner_three);
  SDL_FreeSurface(surface_banner_three);

  SDL_Surface* surface_banner_four = IMG_Load("design/BannerFour.png");
  SDL_Texture* texture_banner_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_banner_four);
  SDL_FreeSurface(surface_banner_four);


  // Chest!

  // Mini Chest!

  SDL_Surface* surface_mini_chest_one = IMG_Load("design/ChestMiniOne.png");
  SDL_Texture* texture_mini_chest_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_one);
  SDL_FreeSurface(surface_mini_chest_one);

  SDL_Surface* surface_mini_chest_two = IMG_Load("design/ChestMiniTwo.png");
  SDL_Texture* texture_mini_chest_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_two);
  SDL_FreeSurface(surface_mini_chest_two);

  SDL_Surface* surface_mini_chest_three = IMG_Load("design/ChestMiniThree.png");
  SDL_Texture* texture_mini_chest_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_three);
  SDL_FreeSurface(surface_mini_chest_three);

  SDL_Surface* surface_mini_chest_four = IMG_Load("design/ChestMiniFour.png");
  SDL_Texture* texture_mini_chest_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_four);
  SDL_FreeSurface(surface_mini_chest_four);

  // Mini Chest Opening!

  SDL_Surface* surface_mini_chest_opening_one = IMG_Load("design/ChestMiniOpeningOne.png");
  SDL_Texture* texture_mini_chest_opening_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_opening_one);
  SDL_FreeSurface(surface_mini_chest_opening_one);

  SDL_Surface* surface_mini_chest_opening_two = IMG_Load("design/ChestMiniOpeningTwo.png");
  SDL_Texture* texture_mini_chest_opening_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_opening_two);
  SDL_FreeSurface(surface_mini_chest_opening_two);

  SDL_Surface* surface_mini_chest_opening_three = IMG_Load("design/ChestMiniOpeningThree.png");
  SDL_Texture* texture_mini_chest_opening_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_opening_three);
  SDL_FreeSurface(surface_mini_chest_opening_three);

  SDL_Surface* surface_mini_chest_opening_four = IMG_Load("design/ChestMiniOpeningFour.png");
  SDL_Texture* texture_mini_chest_opening_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_mini_chest_opening_four);
  SDL_FreeSurface(surface_mini_chest_opening_four);

  //Big Chest !

  SDL_Surface* surface_big_chest_one = IMG_Load("design/BigChestOne.png");
  SDL_Texture* texture_big_chest_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_one);
  SDL_FreeSurface(surface_big_chest_one); 
  
  SDL_Surface* surface_big_chest_two = IMG_Load("design/BigChestTwo.png");
  SDL_Texture* texture_big_chest_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_two);
  SDL_FreeSurface(surface_big_chest_two); 

  SDL_Surface* surface_big_chest_three = IMG_Load("design/BigChestThree.png");
  SDL_Texture* texture_big_chest_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_three);
  SDL_FreeSurface(surface_big_chest_three); 

  SDL_Surface* surface_big_chest_four = IMG_Load("design/BigChestFour.png");
  SDL_Texture* texture_big_chest_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_four);
  SDL_FreeSurface(surface_big_chest_four); 

  // Big Chest Opening !

  SDL_Surface* surface_big_chest_opening_one = IMG_Load("design/BigChestOpeningOne.png");
  SDL_Texture* texture_big_chest_opening_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_opening_one);
  SDL_FreeSurface(surface_big_chest_opening_one);

  SDL_Surface* surface_big_chest_opening_two = IMG_Load("design/BigChestOpeningTwo.png");
  SDL_Texture* texture_big_chest_opening_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_opening_two);
  SDL_FreeSurface(surface_big_chest_opening_two);

  SDL_Surface* surface_big_chest_opening_three = IMG_Load("design/BigChestOpeningThree.png");
  SDL_Texture* texture_big_chest_opening_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_opening_three);
  SDL_FreeSurface(surface_big_chest_opening_three);

  SDL_Surface* surface_big_chest_opening_four = IMG_Load("design/BigChestOpeningFour.png");
  SDL_Texture* texture_big_chest_opening_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_chest_opening_four);
  SDL_FreeSurface(surface_big_chest_opening_four);

  // Boxes!

  // Small Iron Box!

  SDL_Surface* surface_small_iron_box_one = IMG_Load("design/BoxSmallOne.png");
  SDL_Texture* texture_small_iron_box_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_iron_box_one);
  SDL_FreeSurface(surface_small_iron_box_one);

  SDL_Surface* surface_small_iron_box_two = IMG_Load("design/BoxSmallTwo.png");
  SDL_Texture* texture_small_iron_box_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_iron_box_two);
  SDL_FreeSurface(surface_small_iron_box_two);

  SDL_Surface* surface_small_iron_box_three = IMG_Load("design/BoxSmallThree.png");
  SDL_Texture* texture_small_iron_box_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_iron_box_three);
  SDL_FreeSurface(surface_small_iron_box_three);

  SDL_Surface* surface_small_iron_box_four = IMG_Load("design/BoxSmallFour.png");
  SDL_Texture* texture_small_iron_box_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_iron_box_four);
  SDL_FreeSurface(surface_small_iron_box_four);

  // Small Wood Box!

  SDL_Surface* surface_small_wood_box_one = IMG_Load("design/BoxSmallOneWood.png");
  SDL_Texture* texture_small_wood_box_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_wood_box_one);
  SDL_FreeSurface(surface_small_wood_box_one);

  SDL_Surface* surface_small_wood_box_two = IMG_Load("design/BoxSmallTwoWood.png");
  SDL_Texture* texture_small_wood_box_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_wood_box_two);
  SDL_FreeSurface(surface_small_wood_box_two);

  SDL_Surface* surface_small_wood_box_three = IMG_Load("design/BoxSmallThreeWood.png");
  SDL_Texture* texture_small_wood_box_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_wood_box_three);
  SDL_FreeSurface(surface_small_wood_box_three);

  SDL_Surface* surface_small_wood_box_four = IMG_Load("design/BoxSmallFourWood.png");
  SDL_Texture* texture_small_wood_box_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_small_wood_box_four);
  SDL_FreeSurface(surface_small_wood_box_four);

  // Big Iron Box!

  SDL_Surface* surface_big_iron_box_one = IMG_Load("design/BoxIronBigOne.png");
  SDL_Texture* texture_big_iron_box_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_iron_box_one);
  SDL_FreeSurface(surface_big_iron_box_one);

  SDL_Surface* surface_big_iron_box_two = IMG_Load("design/BoxIronBigTwo.png");
  SDL_Texture* texture_big_iron_box_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_iron_box_two);
  SDL_FreeSurface(surface_big_iron_box_two);

  SDL_Surface* surface_big_iron_box_three = IMG_Load("design/BoxIronBigThree.png");
  SDL_Texture* texture_big_iron_box_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_iron_box_three);
  SDL_FreeSurface(surface_big_iron_box_three);

  SDL_Surface* surface_big_iron_box_four = IMG_Load("design/BoxIronBigFour.png");
  SDL_Texture* texture_big_iron_box_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_iron_box_four);
  SDL_FreeSurface(surface_big_iron_box_four);

  // Big Wood Box!

  SDL_Surface* surface_big_wood_box_one = IMG_Load("design/BoxWoodBigOne.png");
  SDL_Texture* texture_big_wood_box_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_wood_box_one);
  SDL_FreeSurface(surface_big_wood_box_one);

  SDL_Surface* surface_big_wood_box_two = IMG_Load("design/BoxWoodBigTwo.png");
  SDL_Texture* texture_big_wood_box_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_wood_box_two);
  SDL_FreeSurface(surface_big_wood_box_two);

  SDL_Surface* surface_big_wood_box_three = IMG_Load("design/BoxWoodBigThree.png");
  SDL_Texture* texture_big_wood_box_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_wood_box_three);
  SDL_FreeSurface(surface_big_wood_box_three);

  SDL_Surface* surface_big_wood_box_four = IMG_Load("design/BoxWoodBigFour.png");
  SDL_Texture* texture_big_wood_box_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_big_wood_box_four);
  SDL_FreeSurface(surface_big_wood_box_four);

  // Silver Key

  SDL_Surface* surface_silver_key_one = IMG_Load("design/KeySilverOne.png");
  SDL_Texture* texture_silver_key_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_silver_key_one);
  SDL_FreeSurface(surface_silver_key_one);

  SDL_Surface* surface_silver_key_two = IMG_Load("design/KeySilverTwo.png");
  SDL_Texture* texture_silver_key_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_silver_key_two);
  SDL_FreeSurface(surface_silver_key_two);

  SDL_Surface* surface_silver_key_three = IMG_Load("design/KeySilverThree.png");
  SDL_Texture* texture_silver_key_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_silver_key_three);
  SDL_FreeSurface(surface_silver_key_three);

  SDL_Surface* surface_silver_key_four = IMG_Load("design/KeySilverFour.png");
  SDL_Texture* texture_silver_key_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_silver_key_four);
  SDL_FreeSurface(surface_silver_key_four);

  // Gold Key

  SDL_Surface* surface_gold_key_one = IMG_Load("design/KeyGoldOne.png");
  SDL_Texture* texture_gold_key_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_gold_key_one);
  SDL_FreeSurface(surface_gold_key_one);

  SDL_Surface* surface_gold_key_two = IMG_Load("design/KeyGoldTwo.png"); 
  SDL_Texture* texture_gold_key_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_gold_key_two);
  SDL_FreeSurface(surface_gold_key_two);

  SDL_Surface* surface_gold_key_three = IMG_Load("design/KeyGoldThree.png"); 
  SDL_Texture* texture_gold_key_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_gold_key_three);
  SDL_FreeSurface(surface_gold_key_three);

  SDL_Surface* surface_gold_key_four = IMG_Load("design/KeyGoldFour.png"); 
  SDL_Texture* texture_gold_key_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_gold_key_four);
  SDL_FreeSurface(surface_gold_key_four);

  // Vertical Flamethrower!

  SDL_Surface* surface_vertical_flamethrower_one = IMG_Load("design/FlameThrowerVerticalOne.png"); 
  SDL_Texture* texture_vertical_flamethrower_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_vertical_flamethrower_one);
  SDL_FreeSurface(surface_vertical_flamethrower_one);

  SDL_Surface* surface_vertical_flamethrower_two = IMG_Load("design/FlameThrowerVerticalTwo.png"); 
  SDL_Texture* texture_vertical_flamethrower_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_vertical_flamethrower_two);
  SDL_FreeSurface(surface_vertical_flamethrower_two);

  SDL_Surface* surface_vertical_flamethrower_three = IMG_Load("design/FlameThrowerVerticalThree.png"); 
  SDL_Texture* texture_vertical_flamethrower_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_vertical_flamethrower_three);
  SDL_FreeSurface(surface_vertical_flamethrower_three);

  SDL_Surface* surface_vertical_flamethrower_four = IMG_Load("design/FlameThrowerVerticalFour.png"); 
  SDL_Texture* texture_vertical_flamethrower_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_vertical_flamethrower_four);
  SDL_FreeSurface(surface_vertical_flamethrower_four);


  // Horizontal Flamethrower! 

  SDL_Surface* surface_horizontal_flamethrower_one = IMG_Load("design/FlameThrowerHorizontalOne.png"); 
  SDL_Texture* texture_horizontal_flamethrower_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_flamethrower_one);
  SDL_FreeSurface(surface_horizontal_flamethrower_one);

  SDL_Surface* surface_horizontal_flamethrower_two = IMG_Load("design/FlameThrowerHorizontalTwo.png"); 
  SDL_Texture* texture_horizontal_flamethrower_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_flamethrower_two);
  SDL_FreeSurface(surface_horizontal_flamethrower_two);

  SDL_Surface* surface_horizontal_flamethrower_three = IMG_Load("design/FlameThrowerHorizontalThree.png"); 
  SDL_Texture* texture_horizontal_flamethrower_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_flamethrower_three);
  SDL_FreeSurface(surface_horizontal_flamethrower_three);

  SDL_Surface* surface_horizontal_flamethrower_four = IMG_Load("design/FlameThrowerHorizontalFour.png"); 
  SDL_Texture* texture_horizontal_flamethrower_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_horizontal_flamethrower_four);
  SDL_FreeSurface(surface_horizontal_flamethrower_four);


  // Arrow Trap!

  SDL_Surface* surface_arrow_trap_one = IMG_Load("design/ArrowTrapOne.png"); 
  SDL_Texture* texture_arrow_trap_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_arrow_trap_one);
  SDL_FreeSurface(surface_arrow_trap_one);

  SDL_Surface* surface_arrow_trap_two = IMG_Load("design/ArrowTrapTwo.png"); 
  SDL_Texture* texture_arrow_trap_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_arrow_trap_two);
  SDL_FreeSurface(surface_arrow_trap_two);

  SDL_Surface* surface_arrow_trap_three = IMG_Load("design/ArrowTrapThree.png"); 
  SDL_Texture* texture_arrow_trap_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_arrow_trap_three);
  SDL_FreeSurface(surface_arrow_trap_three);

  SDL_Surface* surface_arrow_trap_four = IMG_Load("design/ArrowTrapFour.png"); 
  SDL_Texture* texture_arrow_trap_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_arrow_trap_four);
  SDL_FreeSurface(surface_arrow_trap_four);

  // Hourglass!

  SDL_Surface* surface_for_hourglass_one = IMG_Load("design/HourGlassOne.png");
  SDL_Texture* texture_for_hourglass_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_one);
  SDL_FreeSurface(surface_for_hourglass_one);

  SDL_Surface* surface_for_hourglass_two = IMG_Load("design/HourGlassTwo.png");
  SDL_Texture* texture_for_hourglass_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_two);
  SDL_FreeSurface(surface_for_hourglass_two);

  SDL_Surface* surface_for_hourglass_three = IMG_Load("design/HourGlassThree.png");
  SDL_Texture* texture_for_hourglass_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_three);
  SDL_FreeSurface(surface_for_hourglass_three);

  SDL_Surface* surface_for_hourglass_four = IMG_Load("design/HourGlassFour.png");
  SDL_Texture* texture_for_hourglass_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_four);
  SDL_FreeSurface(surface_for_hourglass_four);

  SDL_Surface* surface_for_hourglass_five = IMG_Load("design/HourGlassFive.png");
  SDL_Texture* texture_for_hourglass_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_five);
  SDL_FreeSurface(surface_for_hourglass_five);

  SDL_Surface* surface_for_hourglass_six = IMG_Load("design/HourGlassSix.png");
  SDL_Texture* texture_for_hourglass_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_six);
  SDL_FreeSurface(surface_for_hourglass_six);

  SDL_Surface* surface_for_hourglass_seven = IMG_Load("design/HourGlassSeven.png");
  SDL_Texture* texture_for_hourglass_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_seven);
  SDL_FreeSurface(surface_for_hourglass_seven);

  SDL_Surface* surface_for_hourglass_eight = IMG_Load("design/HourGlassEight.png");
  SDL_Texture* texture_for_hourglass_eight = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_eight);
  SDL_FreeSurface(surface_for_hourglass_eight);

  SDL_Surface* surface_for_hourglass_nine = IMG_Load("design/HourGlassNine.png");
  SDL_Texture* texture_for_hourglass_nine = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_nine);
  SDL_FreeSurface(surface_for_hourglass_nine);

  SDL_Surface* surface_for_hourglass_ten = IMG_Load("design/HourGlassTen.png");
  SDL_Texture* texture_for_hourglass_ten = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_ten);
  SDL_FreeSurface(surface_for_hourglass_ten);

  SDL_Surface* surface_for_hourglass_eleven = IMG_Load("design/HourGlassEleven.png");
  SDL_Texture* texture_for_hourglass_eleven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_eleven);
  SDL_FreeSurface(surface_for_hourglass_eleven);

  SDL_Surface* surface_for_hourglass_twelve = IMG_Load("design/HourGlassTwelve.png");
  SDL_Texture* texture_for_hourglass_twelve = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twelve);
  SDL_FreeSurface(surface_for_hourglass_twelve);

  SDL_Surface* surface_for_hourglass_thirteen = IMG_Load("design/HourGlassThirteen.png");
  SDL_Texture* texture_for_hourglass_thirteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_thirteen);
  SDL_FreeSurface(surface_for_hourglass_thirteen);

  SDL_Surface* surface_for_hourglass_fourteen = IMG_Load("design/HourGlassFourteen.png");
  SDL_Texture* texture_for_hourglass_fourteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_fourteen);
  SDL_FreeSurface(surface_for_hourglass_fourteen);

  SDL_Surface* surface_for_hourglass_fifteen = IMG_Load("design/HourGlassFifteen.png");
  SDL_Texture* texture_for_hourglass_fifteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_fifteen);
  SDL_FreeSurface(surface_for_hourglass_fifteen);

  SDL_Surface* surface_for_hourglass_sixteen = IMG_Load("design/HourGlassSixteen.png");
  SDL_Texture* texture_for_hourglass_sixteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_sixteen);
  SDL_FreeSurface(surface_for_hourglass_sixteen);

  SDL_Surface* surface_for_hourglass_seventeen = IMG_Load("design/HourGlassSeventeen.png");
  SDL_Texture* texture_for_hourglass_seventeen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_seventeen);
  SDL_FreeSurface(surface_for_hourglass_seventeen);

  SDL_Surface* surface_for_hourglass_eighteen = IMG_Load("design/HourGlassEighteen.png");
  SDL_Texture* texture_for_hourglass_eighteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_eighteen);
  SDL_FreeSurface(surface_for_hourglass_eighteen);

  SDL_Surface* surface_for_hourglass_nineteen = IMG_Load("design/HourGlassNineteen.png");
  SDL_Texture* texture_for_hourglass_nineteen = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_nineteen);
  SDL_FreeSurface(surface_for_hourglass_nineteen);

  SDL_Surface* surface_for_hourglass_twenty = IMG_Load("design/HourGlassTwenty.png");
  SDL_Texture* texture_for_hourglass_twenty = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty);
  SDL_FreeSurface(surface_for_hourglass_twenty);

  SDL_Surface* surface_for_hourglass_twenty_one = IMG_Load("design/HourGlassTwentyOne.png");
  SDL_Texture* texture_for_hourglass_twenty_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_one);
  SDL_FreeSurface(surface_for_hourglass_twenty_one);

  SDL_Surface* surface_for_hourglass_twenty_two = IMG_Load("design/HourGlassTwentyTwo.png");
  SDL_Texture* texture_for_hourglass_twenty_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_two);
  SDL_FreeSurface(surface_for_hourglass_twenty_two);

  SDL_Surface* surface_for_hourglass_twenty_three = IMG_Load("design/HourGlassTwentyThree.png");
  SDL_Texture* texture_for_hourglass_twenty_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_three);
  SDL_FreeSurface(surface_for_hourglass_twenty_three);

  SDL_Surface* surface_for_hourglass_twenty_four = IMG_Load("design/HourGlassTwentyFour.png");
  SDL_Texture* texture_for_hourglass_twenty_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_four);
  SDL_FreeSurface(surface_for_hourglass_twenty_four);

  SDL_Surface* surface_for_hourglass_twenty_five = IMG_Load("design/HourGlassTwentyFive.png");
  SDL_Texture* texture_for_hourglass_twenty_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_five);
  SDL_FreeSurface(surface_for_hourglass_twenty_five);

  SDL_Surface* surface_for_hourglass_twenty_six = IMG_Load("design/HourGlassTwentySix.png");
  SDL_Texture* texture_for_hourglass_twenty_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_six);
  SDL_FreeSurface(surface_for_hourglass_twenty_six);

  SDL_Surface* surface_for_hourglass_twenty_seven = IMG_Load("design/HourGlassTwentySeven.png");
  SDL_Texture* texture_for_hourglass_twenty_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_hourglass_twenty_seven);
  SDL_FreeSurface(surface_for_hourglass_twenty_seven);



  // Orc Plated

  // Idle

  SDL_Surface* orc_plated_idle_one = IMG_Load("design/OrcPlatedIdleOne.png");
  SDL_Texture* texture_orc_plated_idle_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_one);
  SDL_FreeSurface(orc_plated_idle_one);

  SDL_Surface* orc_plated_idle_two = IMG_Load("design/OrcPlatedIdleTwo.png");
  SDL_Texture* texture_orc_plated_idle_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_two);
  SDL_FreeSurface(orc_plated_idle_two);

  SDL_Surface* orc_plated_idle_three = IMG_Load("design/OrcPlatedIdleThree.png");
  SDL_Texture* texture_orc_plated_idle_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_three);
  SDL_FreeSurface(orc_plated_idle_three);

  SDL_Surface* orc_plated_idle_four = IMG_Load("design/OrcPlatedIdleFour.png");
  SDL_Texture* texture_orc_plated_idle_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_four);
  SDL_FreeSurface(orc_plated_idle_four);

  SDL_Surface* orc_plated_idle_five = IMG_Load("design/OrcPlatedIdleFive.png");
  SDL_Texture* texture_orc_plated_idle_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_five);
  SDL_FreeSurface(orc_plated_idle_five);

  SDL_Surface* orc_plated_idle_six = IMG_Load("design/OrcPlatedIdleSix.png");
  SDL_Texture* texture_orc_plated_idle_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_idle_six);
  SDL_FreeSurface(orc_plated_idle_six);

  // Walk!

  SDL_Surface* orc_plated_walk_one = IMG_Load("design/OrcPlatedWalkOne.png");
  SDL_Texture* texture_orc_plated_walk_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_one);
  SDL_FreeSurface(orc_plated_walk_one);

  SDL_Surface* orc_plated_walk_two = IMG_Load("design/OrcPlatedWalkTwo.png");
  SDL_Texture* texture_orc_plated_walk_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_two);
  SDL_FreeSurface(orc_plated_walk_two);

  SDL_Surface* orc_plated_walk_three = IMG_Load("design/OrcPlatedWalkThree.png");
  SDL_Texture* texture_orc_plated_walk_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_three);
  SDL_FreeSurface(orc_plated_walk_three);

  SDL_Surface* orc_plated_walk_four = IMG_Load("design/OrcPlatedWalkFour.png");
  SDL_Texture* texture_orc_plated_walk_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_four);
  SDL_FreeSurface(orc_plated_walk_four);

  SDL_Surface* orc_plated_walk_five = IMG_Load("design/OrcPlatedWalkFive.png");
  SDL_Texture* texture_orc_plated_walk_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_five);
  SDL_FreeSurface(orc_plated_walk_five);

  SDL_Surface* orc_plated_walk_six = IMG_Load("design/OrcPlatedWalkSix.png");
  SDL_Texture* texture_orc_plated_walk_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_six);
  SDL_FreeSurface(orc_plated_walk_six);

  SDL_Surface* orc_plated_walk_seven = IMG_Load("design/OrcPlatedWalkSeven.png");
  SDL_Texture* texture_orc_plated_walk_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_seven);
  SDL_FreeSurface(orc_plated_walk_seven);

  SDL_Surface* orc_plated_walk_eight = IMG_Load("design/OrcPlatedWalkEight.png");
  SDL_Texture* texture_orc_plated_walk_eight = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_walk_eight);
  SDL_FreeSurface(orc_plated_walk_eight);

  // Attack !

  SDL_Surface* orc_plated_attack_one = IMG_Load("design/OrcPlatedAttackOne.png");
  SDL_Texture* texture_orc_plated_attack_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_one);
  SDL_FreeSurface(orc_plated_attack_one);

  SDL_Surface* orc_plated_attack_two = IMG_Load("design/OrcPlatedAttackTwo.png");
  SDL_Texture* texture_orc_plated_attack_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_two);
  SDL_FreeSurface(orc_plated_attack_two);

  SDL_Surface* orc_plated_attack_three = IMG_Load("design/OrcPlatedAttackThree.png");
  SDL_Texture* texture_orc_plated_attack_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_three);
  SDL_FreeSurface(orc_plated_attack_three);

  SDL_Surface* orc_plated_attack_four = IMG_Load("design/OrcPlatedAttackFour.png");
  SDL_Texture* texture_orc_plated_attack_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_four);
  SDL_FreeSurface(orc_plated_attack_four);

  SDL_Surface* orc_plated_attack_five = IMG_Load("design/OrcPlatedAttackFive.png");
  SDL_Texture* texture_orc_plated_attack_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_five);
  SDL_FreeSurface(orc_plated_attack_five);

  SDL_Surface* orc_plated_attack_six = IMG_Load("design/OrcPlatedAttackSix.png");
  SDL_Texture* texture_orc_plated_attack_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_six);
  SDL_FreeSurface(orc_plated_attack_six);

  SDL_Surface* orc_plated_attack_seven = IMG_Load("design/OrcPlatedAttackSeven.png");
  SDL_Texture* texture_orc_plated_attack_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_seven);
  SDL_FreeSurface(orc_plated_attack_seven);

  SDL_Surface* orc_plated_attack_eight = IMG_Load("design/OrcPlatedAttackEight.png");
  SDL_Texture* texture_orc_plated_attack_eight = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_attack_eight);
  SDL_FreeSurface(orc_plated_attack_eight);

  // Hurt!

  SDL_Surface* orc_plated_hurt_one = IMG_Load("design/OrcPlatedHurtOne.png");
  SDL_Texture* texture_orc_plated_hurt_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_hurt_one);
  SDL_FreeSurface(orc_plated_hurt_one);

  SDL_Surface* orc_plated_hurt_two = IMG_Load("design/OrcPlatedHurtTwo.png");
  SDL_Texture* texture_orc_plated_hurt_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_hurt_two);
  SDL_FreeSurface(orc_plated_hurt_two);

  SDL_Surface* orc_plated_hurt_three = IMG_Load("design/OrcPlatedHurtThree.png");
  SDL_Texture* texture_orc_plated_hurt_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_hurt_three);
  SDL_FreeSurface(orc_plated_hurt_three);

  SDL_Surface* orc_plated_hurt_four = IMG_Load("design/OrcPlatedHurtFour.png");
  SDL_Texture* texture_orc_plated_hurt_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_hurt_four);
  SDL_FreeSurface(orc_plated_hurt_four);



  SDL_Surface* orc_plated_death_one = IMG_Load("design/OrcPlatedDeathOne.png");
  SDL_Texture* texture_orc_plated_death_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_death_one);
  SDL_FreeSurface(orc_plated_death_one);

  SDL_Surface* orc_plated_death_two = IMG_Load("design/OrcPlatedDeathTwo.png");
  SDL_Texture* texture_orc_plated_death_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_death_two);
  SDL_FreeSurface(orc_plated_death_two);

  SDL_Surface* orc_plated_death_three = IMG_Load("design/OrcPlatedDeathThree.png");
  SDL_Texture* texture_orc_plated_death_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_death_three);
  SDL_FreeSurface(orc_plated_death_three);

  SDL_Surface* orc_plated_death_four = IMG_Load("design/OrcPlatedDeathFour.png");
  SDL_Texture* texture_orc_plated_death_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_plated_death_four);
  SDL_FreeSurface(orc_plated_death_four);


  // Soldier Death

  SDL_Surface* soldier_death_one = IMG_Load("design/SoldierDeathOne.png");
  SDL_Texture* texture_soldier_death_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), soldier_death_one);
  SDL_FreeSurface(soldier_death_one);

  SDL_Surface* soldier_death_two = IMG_Load("design/SoldierDeathTwo.png");
  SDL_Texture* texture_soldier_death_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), soldier_death_two);
  SDL_FreeSurface(soldier_death_two);

  SDL_Surface* soldier_death_three = IMG_Load("design/SoldierDeathThree.png");
  SDL_Texture* texture_soldier_death_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), soldier_death_three);
  SDL_FreeSurface(soldier_death_three);

  SDL_Surface* soldier_death_four = IMG_Load("design/SoldierDeathFour.png");
  SDL_Texture* texture_soldier_death_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), soldier_death_four);
  SDL_FreeSurface(soldier_death_four);


  // Orc Elite (Boss)

  // Idle

  SDL_Surface* orc_elite_idle_one = IMG_Load("design/OrcEliteIdleOne.png");
  SDL_Texture* texture_orc_elite_idle_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_one);
  SDL_FreeSurface(orc_elite_idle_one);

  SDL_Surface* orc_elite_idle_two = IMG_Load("design/OrcEliteIdleTwo.png");
  SDL_Texture* texture_orc_elite_idle_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_two);
  SDL_FreeSurface(orc_elite_idle_two);

  SDL_Surface* orc_elite_idle_three = IMG_Load("design/OrcEliteIdleThree.png");
  SDL_Texture* texture_orc_elite_idle_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_three);
  SDL_FreeSurface(orc_elite_idle_three);

  SDL_Surface* orc_elite_idle_four = IMG_Load("design/OrcEliteIdleFour.png");
  SDL_Texture* texture_orc_elite_idle_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_four);
  SDL_FreeSurface(orc_elite_idle_four);

  SDL_Surface* orc_elite_idle_five = IMG_Load("design/OrcEliteIdleFive.png");
  SDL_Texture* texture_orc_elite_idle_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_five);
  SDL_FreeSurface(orc_elite_idle_five);

  SDL_Surface* orc_elite_idle_six = IMG_Load("design/OrcEliteIdleSix.png");
  SDL_Texture* texture_orc_elite_idle_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_idle_six);
  SDL_FreeSurface(orc_elite_idle_six);

  // Walk

  SDL_Surface* orc_elite_walk_one = IMG_Load("design/OrcEliteWalkOne.png");
  SDL_Texture* texture_orc_elite_walk_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_one);
  SDL_FreeSurface(orc_elite_walk_one);

  SDL_Surface* orc_elite_walk_two = IMG_Load("design/OrcEliteWalkTwo.png");
  SDL_Texture* texture_orc_elite_walk_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_two);
  SDL_FreeSurface(orc_elite_walk_two);

  SDL_Surface* orc_elite_walk_three = IMG_Load("design/OrcEliteWalkThree.png");
  SDL_Texture* texture_orc_elite_walk_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_three);
  SDL_FreeSurface(orc_elite_walk_three);

  SDL_Surface* orc_elite_walk_four = IMG_Load("design/OrcEliteWalkFour.png");
  SDL_Texture* texture_orc_elite_walk_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_four);
  SDL_FreeSurface(orc_elite_walk_four);

  SDL_Surface* orc_elite_walk_five = IMG_Load("design/OrcEliteWalkFive.png");
  SDL_Texture* texture_orc_elite_walk_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_five);
  SDL_FreeSurface(orc_elite_walk_five);

  SDL_Surface* orc_elite_walk_six = IMG_Load("design/OrcEliteWalkSix.png");
  SDL_Texture* texture_orc_elite_walk_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_six);
  SDL_FreeSurface(orc_elite_walk_six);

  SDL_Surface* orc_elite_walk_seven = IMG_Load("design/OrcEliteWalkSeven.png");
  SDL_Texture* texture_orc_elite_walk_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_seven);
  SDL_FreeSurface(orc_elite_walk_seven);

  SDL_Surface* orc_elite_walk_eight = IMG_Load("design/OrcEliteWalkEight.png");
  SDL_Texture* texture_orc_elite_walk_eight = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_walk_eight);
  SDL_FreeSurface(orc_elite_walk_eight);

  // Hurt

  SDL_Surface* orc_elite_hurt_one = IMG_Load("design/OrcEliteHurtOne.png");
  SDL_Texture* texture_orc_elite_hurt_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_hurt_one);
  SDL_FreeSurface(orc_elite_hurt_one);

  SDL_Surface* orc_elite_hurt_two = IMG_Load("design/OrcEliteHurtTwo.png");
  SDL_Texture* texture_orc_elite_hurt_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_hurt_two);
  SDL_FreeSurface(orc_elite_hurt_two);

  SDL_Surface* orc_elite_hurt_three = IMG_Load("design/OrcEliteHurtThree.png");
  SDL_Texture* texture_orc_elite_hurt_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_hurt_three);
  SDL_FreeSurface(orc_elite_hurt_three);

  SDL_Surface* orc_elite_hurt_four = IMG_Load("design/OrcEliteHurtFour.png");
  SDL_Texture* texture_orc_elite_hurt_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_hurt_four);
  SDL_FreeSurface(orc_elite_hurt_four);

  // Death

  SDL_Surface* orc_elite_death_one = IMG_Load("design/OrcEliteDeathOne.png");
  SDL_Texture* texture_orc_elite_death_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_death_one);
  SDL_FreeSurface(orc_elite_death_one);

  SDL_Surface* orc_elite_death_two = IMG_Load("design/OrcEliteDeathTwo.png");
  SDL_Texture* texture_orc_elite_death_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_death_two);
  SDL_FreeSurface(orc_elite_death_two);

  SDL_Surface* orc_elite_death_three = IMG_Load("design/OrcEliteDeathThree.png");
  SDL_Texture* texture_orc_elite_death_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_death_three);
  SDL_FreeSurface(orc_elite_death_three);

  SDL_Surface* orc_elite_death_four = IMG_Load("design/OrcEliteDeathFour.png");
  SDL_Texture* texture_orc_elite_death_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_death_four);
  SDL_FreeSurface(orc_elite_death_four);

  // First Attack Animation

  SDL_Surface* orc_elite_first_attack_one = IMG_Load("design/OrcEliteFirstAttackOne.png");
  SDL_Texture* texture_orc_elite_first_attack_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_one);
  SDL_FreeSurface(orc_elite_first_attack_one);

  SDL_Surface* orc_elite_first_attack_two = IMG_Load("design/OrcEliteFirstAttackTwo.png");
  SDL_Texture* texture_orc_elite_first_attack_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_two);
  SDL_FreeSurface(orc_elite_first_attack_two);

  SDL_Surface* orc_elite_first_attack_three = IMG_Load("design/OrcEliteFirstAttackThree.png");
  SDL_Texture* texture_orc_elite_first_attack_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_three);
  SDL_FreeSurface(orc_elite_first_attack_three);

  SDL_Surface* orc_elite_first_attack_four = IMG_Load("design/OrcEliteFirstAttackFour.png");
  SDL_Texture* texture_orc_elite_first_attack_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_four);
  SDL_FreeSurface(orc_elite_first_attack_four);

  SDL_Surface* orc_elite_first_attack_five = IMG_Load("design/OrcEliteFirstAttackFive.png");
  SDL_Texture* texture_orc_elite_first_attack_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_five);
  SDL_FreeSurface(orc_elite_first_attack_five);

  SDL_Surface* orc_elite_first_attack_six = IMG_Load("design/OrcEliteFirstAttackSix.png");
  SDL_Texture* texture_orc_elite_first_attack_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_six);
  SDL_FreeSurface(orc_elite_first_attack_six);

  SDL_Surface* orc_elite_first_attack_seven = IMG_Load("design/OrcEliteFirstAttackSeven.png");
  SDL_Texture* texture_orc_elite_first_attack_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_first_attack_seven);
  SDL_FreeSurface(orc_elite_first_attack_seven);

  // Second Attack

  SDL_Surface* orc_elite_second_attack_one = IMG_Load("design/OrcEliteSecondAttackOne.png");
  SDL_Texture* texture_orc_elite_second_attack_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_one);
  SDL_FreeSurface(orc_elite_second_attack_one);

  SDL_Surface* orc_elite_second_attack_two = IMG_Load("design/OrcEliteSecondAttackTwo.png");
  SDL_Texture* texture_orc_elite_second_attack_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_two);
  SDL_FreeSurface(orc_elite_second_attack_two);

  SDL_Surface* orc_elite_second_attack_three = IMG_Load("design/OrcEliteSecondAttackThree.png");
  SDL_Texture* texture_orc_elite_second_attack_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_three);
  SDL_FreeSurface(orc_elite_second_attack_three);

  SDL_Surface* orc_elite_second_attack_four = IMG_Load("design/OrcEliteSecondAttackFour.png");
  SDL_Texture* texture_orc_elite_second_attack_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_four);
  SDL_FreeSurface(orc_elite_second_attack_four);

  SDL_Surface* orc_elite_second_attack_five = IMG_Load("design/OrcEliteSecondAttackFive.png");
  SDL_Texture* texture_orc_elite_second_attack_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_five);
  SDL_FreeSurface(orc_elite_second_attack_five);

  SDL_Surface* orc_elite_second_attack_six = IMG_Load("design/OrcEliteSecondAttackSix.png");
  SDL_Texture* texture_orc_elite_second_attack_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_six);
  SDL_FreeSurface(orc_elite_second_attack_six);

  SDL_Surface* orc_elite_second_attack_seven = IMG_Load("design/OrcEliteSecondAttackSeven.png");
  SDL_Texture* texture_orc_elite_second_attack_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_second_attack_seven);
  SDL_FreeSurface(orc_elite_second_attack_seven);


  SDL_Surface* orc_elite_third_attack_one = IMG_Load("design/OrcEliteThirdAttackOne.png");
  SDL_Texture* texture_orc_elite_third_attack_one = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_one);
  SDL_FreeSurface(orc_elite_third_attack_one);

  SDL_Surface* orc_elite_third_attack_two = IMG_Load("design/OrcEliteThirdAttackTwo.png");
  SDL_Texture* texture_orc_elite_third_attack_two = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_two);
  SDL_FreeSurface(orc_elite_third_attack_two);

  SDL_Surface* orc_elite_third_attack_three = IMG_Load("design/OrcEliteThirdAttackThree.png");
  SDL_Texture* texture_orc_elite_third_attack_three = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_three);
  SDL_FreeSurface(orc_elite_third_attack_three);

  SDL_Surface* orc_elite_third_attack_four = IMG_Load("design/OrcEliteThirdAttackFour.png");
  SDL_Texture* texture_orc_elite_third_attack_four = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_four);
  SDL_FreeSurface(orc_elite_third_attack_four);

  SDL_Surface* orc_elite_third_attack_five = IMG_Load("design/OrcEliteThirdAttackFive.png");
  SDL_Texture* texture_orc_elite_third_attack_five = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_five);
  SDL_FreeSurface(orc_elite_third_attack_five);

  SDL_Surface* orc_elite_third_attack_six = IMG_Load("design/OrcEliteThirdAttackSix.png");
  SDL_Texture* texture_orc_elite_third_attack_six = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_six);
  SDL_FreeSurface(orc_elite_third_attack_six);

  SDL_Surface* orc_elite_third_attack_seven = IMG_Load("design/OrcEliteThirdAttackSeven.png");
  SDL_Texture* texture_orc_elite_third_attack_seven = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_seven);
  SDL_FreeSurface(orc_elite_third_attack_seven);

  SDL_Surface* orc_elite_third_attack_eight = IMG_Load("design/OrcEliteThirdAttackEight.png");
  SDL_Texture* texture_orc_elite_third_attack_eight = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), orc_elite_third_attack_eight);
  SDL_FreeSurface(orc_elite_third_attack_eight);

  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK].resize(8);

  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][0] = texture_orc_elite_third_attack_one;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][1] = texture_orc_elite_third_attack_two;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][2] = texture_orc_elite_third_attack_three;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][3] = texture_orc_elite_third_attack_four;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][4] = texture_orc_elite_third_attack_five;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][5] = texture_orc_elite_third_attack_six;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][6] = texture_orc_elite_third_attack_seven;
  textures_for_animations[AnimationState::ORC_ELITE_THIRD_ATTACK][7] = texture_orc_elite_third_attack_eight;


  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK].resize(11);

  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][0]  = texture_orc_elite_second_attack_one;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][1]  = texture_orc_elite_second_attack_two;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][2]  = texture_orc_elite_second_attack_three;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][3]  = texture_orc_elite_second_attack_four;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][4]  = texture_orc_elite_second_attack_five;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][5]  = texture_orc_elite_second_attack_six;

  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][6]  = texture_orc_elite_second_attack_three;
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][7]  = texture_orc_elite_second_attack_four;  
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][8]  = texture_orc_elite_second_attack_five; 
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][9]  = texture_orc_elite_second_attack_six;   
  textures_for_animations[AnimationState::ORC_ELITE_SECOND_ATTACK][10] = texture_orc_elite_second_attack_seven;



  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK].resize(7);

  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][0] = texture_orc_elite_first_attack_one;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][1] = texture_orc_elite_first_attack_two;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][2] = texture_orc_elite_first_attack_three;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][3] = texture_orc_elite_first_attack_four;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][4] = texture_orc_elite_first_attack_five;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][5] = texture_orc_elite_first_attack_six;
  textures_for_animations[AnimationState::ORC_ELITE_FIRST_ATTACK][6] = texture_orc_elite_first_attack_seven;



  textures_for_animations[AnimationState::ORC_ELITE_DEATH].resize(4);

  textures_for_animations[AnimationState::ORC_ELITE_DEATH][0] = texture_orc_elite_death_one;
  textures_for_animations[AnimationState::ORC_ELITE_DEATH][1] = texture_orc_elite_death_two;
  textures_for_animations[AnimationState::ORC_ELITE_DEATH][2] = texture_orc_elite_death_three;
  textures_for_animations[AnimationState::ORC_ELITE_DEATH][3] = texture_orc_elite_death_four;



  textures_for_animations[AnimationState::ORC_ELITE_HURT].resize(4);

  textures_for_animations[AnimationState::ORC_ELITE_HURT][0] = texture_orc_elite_hurt_one;
  textures_for_animations[AnimationState::ORC_ELITE_HURT][1] = texture_orc_elite_hurt_two;
  textures_for_animations[AnimationState::ORC_ELITE_HURT][2] = texture_orc_elite_hurt_three;
  textures_for_animations[AnimationState::ORC_ELITE_HURT][3] = texture_orc_elite_hurt_four;




  textures_for_animations[AnimationState::ORC_ELITE_WALK].resize(8);

  textures_for_animations[AnimationState::ORC_ELITE_WALK][0] = texture_orc_elite_walk_one;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][1] = texture_orc_elite_walk_two;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][2] = texture_orc_elite_walk_three;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][3] = texture_orc_elite_walk_four;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][4] = texture_orc_elite_walk_five;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][5] = texture_orc_elite_walk_six;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][6] = texture_orc_elite_walk_seven;
  textures_for_animations[AnimationState::ORC_ELITE_WALK][7] = texture_orc_elite_walk_eight;





  textures_for_animations[AnimationState::ORC_ELITE_IDLE].resize(6);

  textures_for_animations[AnimationState::ORC_ELITE_IDLE][0] = texture_orc_elite_idle_one;
  textures_for_animations[AnimationState::ORC_ELITE_IDLE][1] = texture_orc_elite_idle_two;
  textures_for_animations[AnimationState::ORC_ELITE_IDLE][2] = texture_orc_elite_idle_three;
  textures_for_animations[AnimationState::ORC_ELITE_IDLE][3] = texture_orc_elite_idle_four;
  textures_for_animations[AnimationState::ORC_ELITE_IDLE][4] = texture_orc_elite_idle_five;
  textures_for_animations[AnimationState::ORC_ELITE_IDLE][5] = texture_orc_elite_idle_six;



  textures_for_animations[AnimationState::SOLDIER_DEATH].resize(4);

  textures_for_animations[AnimationState::SOLDIER_DEATH][0] = texture_soldier_death_one;
  textures_for_animations[AnimationState::SOLDIER_DEATH][1] = texture_soldier_death_two;
  textures_for_animations[AnimationState::SOLDIER_DEATH][2] = texture_soldier_death_three;
  textures_for_animations[AnimationState::SOLDIER_DEATH][3] = texture_soldier_death_four;



  textures_for_animations[AnimationState::ORC_PLATED_DEATH].resize(4);

  textures_for_animations[AnimationState::ORC_PLATED_DEATH][0] = texture_orc_plated_death_one;
  textures_for_animations[AnimationState::ORC_PLATED_DEATH][1] = texture_orc_plated_death_two;
  textures_for_animations[AnimationState::ORC_PLATED_DEATH][2] = texture_orc_plated_death_three;
  textures_for_animations[AnimationState::ORC_PLATED_DEATH][3] = texture_orc_plated_death_four;

  textures_for_animations[AnimationState::ORC_PLATED_HURT].resize(4);

  textures_for_animations[AnimationState::ORC_PLATED_HURT][0] = texture_orc_plated_hurt_one;
  textures_for_animations[AnimationState::ORC_PLATED_HURT][1] = texture_orc_plated_hurt_two;
  textures_for_animations[AnimationState::ORC_PLATED_HURT][2] = texture_orc_plated_hurt_three;
  textures_for_animations[AnimationState::ORC_PLATED_HURT][3] = texture_orc_plated_hurt_four;

  textures_for_animations[AnimationState::ORC_PLATED_ATTACK].resize(8);

  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][0] = texture_orc_plated_attack_one;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][1] = texture_orc_plated_attack_two;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][2] = texture_orc_plated_attack_three;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][3] = texture_orc_plated_attack_four;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][4] = texture_orc_plated_attack_five;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][5] = texture_orc_plated_attack_six;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][6] = texture_orc_plated_attack_seven;
  textures_for_animations[AnimationState::ORC_PLATED_ATTACK][7] = texture_orc_plated_attack_eight;

  textures_for_animations[AnimationState::ORC_PLATED_WALK].resize(8);

  textures_for_animations[AnimationState::ORC_PLATED_WALK][0] = texture_orc_plated_walk_one;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][1] = texture_orc_plated_walk_two;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][2] = texture_orc_plated_walk_three;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][3] = texture_orc_plated_walk_four;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][4] = texture_orc_plated_walk_five;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][5] = texture_orc_plated_walk_six;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][6] = texture_orc_plated_walk_seven;
  textures_for_animations[AnimationState::ORC_PLATED_WALK][7] = texture_orc_plated_walk_eight;

  textures_for_animations[AnimationState::ORC_PLATED_IDLE].resize(6);
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][0] = texture_orc_plated_idle_one;
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][1] = texture_orc_plated_idle_two;
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][2] = texture_orc_plated_idle_three;
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][3] = texture_orc_plated_idle_four;
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][4] = texture_orc_plated_idle_five;
  textures_for_animations[AnimationState::ORC_PLATED_IDLE][5] = texture_orc_plated_idle_six;




  textures_for_animations[AnimationState::HOURGLASS_ROTATING].resize(27);

  textures_for_animations[AnimationState::HOURGLASS_ROTATING][0]  = texture_for_hourglass_twenty_seven;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][1]  = texture_for_hourglass_twenty_six;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][2]  = texture_for_hourglass_twenty_five;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][3]  = texture_for_hourglass_twenty_four;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][4]  = texture_for_hourglass_twenty_three;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][5]  = texture_for_hourglass_twenty_two;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][6]  = texture_for_hourglass_twenty_one;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][7]  = texture_for_hourglass_twenty;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][8]  = texture_for_hourglass_nineteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][9]  = texture_for_hourglass_eighteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][10] = texture_for_hourglass_seventeen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][11] = texture_for_hourglass_sixteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][12] = texture_for_hourglass_fifteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][13] = texture_for_hourglass_fourteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][14] = texture_for_hourglass_thirteen;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][15] = texture_for_hourglass_twelve;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][16] = texture_for_hourglass_eleven;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][17] = texture_for_hourglass_ten;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][18] = texture_for_hourglass_nine;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][19] = texture_for_hourglass_eight;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][20] = texture_for_hourglass_seven;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][21] = texture_for_hourglass_six;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][22] = texture_for_hourglass_five;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][23] = texture_for_hourglass_four;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][24] = texture_for_hourglass_three;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][25] = texture_for_hourglass_two;
  textures_for_animations[AnimationState::HOURGLASS_ROTATING][26] = texture_for_hourglass_one;




  textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION].resize(4);

  textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION][0] = texture_arrow_trap_one;
  textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION][1] = texture_arrow_trap_two;
  textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION][2] = texture_arrow_trap_three;
  textures_for_animations[AnimationState::ARROW_TRAP_ANIMATION][3] = texture_arrow_trap_four;

  textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER].resize(4);

  textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER][0] = texture_horizontal_flamethrower_one;
  textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER][1] = texture_horizontal_flamethrower_two;
  textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER][2] = texture_horizontal_flamethrower_three;
  textures_for_animations[AnimationState::HORIZONTAL_FLAMETHROWER][3] = texture_horizontal_flamethrower_four;

  textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER].resize(4);

  textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER][0] = texture_vertical_flamethrower_one;
  textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER][1] = texture_vertical_flamethrower_two;
  textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER][2] = texture_vertical_flamethrower_three;
  textures_for_animations[AnimationState::VERTICAL_FLAMETHROWER][3] = texture_vertical_flamethrower_four;



  textures_for_animations[AnimationState::GOLD_KEY].resize(4);

  textures_for_animations[AnimationState::GOLD_KEY][0] = texture_gold_key_one;
  textures_for_animations[AnimationState::GOLD_KEY][1] = texture_gold_key_two;
  textures_for_animations[AnimationState::GOLD_KEY][2] = texture_gold_key_three;
  textures_for_animations[AnimationState::GOLD_KEY][3] = texture_gold_key_four;

  textures_for_animations[AnimationState::SILVER_KEY].resize(4);

  textures_for_animations[AnimationState::SILVER_KEY][0] = texture_silver_key_one;
  textures_for_animations[AnimationState::SILVER_KEY][1] = texture_silver_key_two;
  textures_for_animations[AnimationState::SILVER_KEY][2] = texture_silver_key_three;
  textures_for_animations[AnimationState::SILVER_KEY][3] = texture_silver_key_four;

  textures_for_animations[AnimationState::BOX_BIG_IRON].resize(4);

  textures_for_animations[AnimationState::BOX_BIG_IRON][0] = texture_big_iron_box_one;
  textures_for_animations[AnimationState::BOX_BIG_IRON][1] = texture_big_iron_box_two;
  textures_for_animations[AnimationState::BOX_BIG_IRON][2] = texture_big_iron_box_three;
  textures_for_animations[AnimationState::BOX_BIG_IRON][3] = texture_big_iron_box_four;

  textures_for_animations[AnimationState::BOX_BIG_WOOD].resize(4);

  textures_for_animations[AnimationState::BOX_BIG_WOOD][0] = texture_big_wood_box_one;
  textures_for_animations[AnimationState::BOX_BIG_WOOD][1] = texture_big_wood_box_two;
  textures_for_animations[AnimationState::BOX_BIG_WOOD][2] = texture_big_wood_box_three;
  textures_for_animations[AnimationState::BOX_BIG_WOOD][3] = texture_big_wood_box_four;

  textures_for_animations[AnimationState::BOX_SMALL_WOOD].resize(4);

  textures_for_animations[AnimationState::BOX_SMALL_WOOD][0] = texture_small_wood_box_one;
  textures_for_animations[AnimationState::BOX_SMALL_WOOD][1] = texture_small_wood_box_two;
  textures_for_animations[AnimationState::BOX_SMALL_WOOD][2] = texture_small_wood_box_three;
  textures_for_animations[AnimationState::BOX_SMALL_WOOD][3] = texture_small_wood_box_four;


  textures_for_animations[AnimationState::BOX_SMALL_IRON].resize(4);

  textures_for_animations[AnimationState::BOX_SMALL_IRON][0] = texture_small_iron_box_one;
  textures_for_animations[AnimationState::BOX_SMALL_IRON][1] = texture_small_iron_box_two;
  textures_for_animations[AnimationState::BOX_SMALL_IRON][2] = texture_small_iron_box_three;
  textures_for_animations[AnimationState::BOX_SMALL_IRON][3] = texture_small_iron_box_four;


  textures_for_animations[AnimationState::CHEST_BIG_ANIM].resize(4);

  textures_for_animations[AnimationState::CHEST_BIG_ANIM][0] = texture_big_chest_one;
  textures_for_animations[AnimationState::CHEST_BIG_ANIM][1] = texture_big_chest_two;
  textures_for_animations[AnimationState::CHEST_BIG_ANIM][2] = texture_big_chest_three;
  textures_for_animations[AnimationState::CHEST_BIG_ANIM][3] = texture_big_chest_four;

  textures_for_animations[AnimationState::CHEST_BIG_OPENINIG].resize(4);

  textures_for_animations[AnimationState::CHEST_BIG_OPENINIG][0] = texture_big_chest_opening_one;
  textures_for_animations[AnimationState::CHEST_BIG_OPENINIG][1] = texture_big_chest_opening_two;
  textures_for_animations[AnimationState::CHEST_BIG_OPENINIG][2] = texture_big_chest_opening_three;
  textures_for_animations[AnimationState::CHEST_BIG_OPENINIG][3] = texture_big_chest_opening_four;



  textures_for_animations[AnimationState::CHEST_MINI_OPENING].resize(4);

  textures_for_animations[AnimationState::CHEST_MINI_OPENING][0] = texture_mini_chest_opening_one;
  textures_for_animations[AnimationState::CHEST_MINI_OPENING][1] = texture_mini_chest_opening_two;
  textures_for_animations[AnimationState::CHEST_MINI_OPENING][2] = texture_mini_chest_opening_three;
  textures_for_animations[AnimationState::CHEST_MINI_OPENING][3] = texture_mini_chest_opening_four;

  textures_for_animations[AnimationState::CHEST_MINI_ANIM].resize(4);

  textures_for_animations[AnimationState::CHEST_MINI_ANIM][0] = texture_mini_chest_one;
  textures_for_animations[AnimationState::CHEST_MINI_ANIM][1] = texture_mini_chest_two;
  textures_for_animations[AnimationState::CHEST_MINI_ANIM][2] = texture_mini_chest_three;
  textures_for_animations[AnimationState::CHEST_MINI_ANIM][3] = texture_mini_chest_four;

  textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL].resize(4);

  textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][0] = texture_for_torch_vertical_one;
  textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][1] = texture_for_torch_vertical_two;
  textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][2] = texture_for_torch_vertical_three;
  textures_for_animations[AnimationState::TORCHES_VERTICAL_WALL][3] = texture_for_torch_vertical_four;

  textures_for_animations[AnimationState::BANNER].resize(4);

  textures_for_animations[AnimationState::BANNER][0] = texture_banner_one;
  textures_for_animations[AnimationState::BANNER][1] = texture_banner_two;
  textures_for_animations[AnimationState::BANNER][2] = texture_banner_three;
  textures_for_animations[AnimationState::BANNER][3] = texture_banner_four;

  textures_for_animations[AnimationState::SHOP_KEEPER_IDLE].resize(4);

  textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][0] = texture_shopkeeper_one;
  textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][1] = texture_shopkeeper_two;
  textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][2] = texture_shopkeeper_three;
  textures_for_animations[AnimationState::SHOP_KEEPER_IDLE][3] = texture_shopkeeper_four;

  textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL].resize(4);

  textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][0] = texture_for_torch_horizontal_one;
  textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][1] = texture_for_torch_horizontal_two;
  textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][2] = texture_for_torch_horizontal_three;
  textures_for_animations[AnimationState::TORCHES_FLAME_HORIZONTAL_WALL][3] = texture_for_torch_horizontal_four;

  textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND].resize(4);

  textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][0] = texture_for_needles_first;
  textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][1] = texture_for_needles_second;
  textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][2] = texture_for_needles_third;
  textures_for_animations[AnimationState::NEEDLES_MOVING_FROM_GROUND][3] = texture_for_needles_fourth;


  textures_for_animations[AnimationState::LADDERS_ARROW_MOVING].resize(1);
  textures_for_animations[AnimationState::LADDERS_ARROW_MOVING][0] = texture_for_ladders;



  textures_for_animations[AnimationState::CANDLESTICK_BURNING].resize(4);

  textures_for_animations[AnimationState::CANDLESTICK_BURNING][0] = texture_for_candlestick_first;
  textures_for_animations[AnimationState::CANDLESTICK_BURNING][1] = texture_for_candlestick_second;
  textures_for_animations[AnimationState::CANDLESTICK_BURNING][2] = texture_for_candlestick_third;
  textures_for_animations[AnimationState::CANDLESTICK_BURNING][3] = texture_for_candlestick_fourth;


  textures_for_animations[AnimationState::SOLDIER_IDLE].resize(6);
  textures_for_animations[AnimationState::ORC_IDLE].resize(6);

  textures_for_animations[AnimationState::SOLDIER_IDLE][0] = texture_for_soldier_idle_one;
  textures_for_animations[AnimationState::SOLDIER_IDLE][1] = texture_for_soldier_idle_two;
  textures_for_animations[AnimationState::SOLDIER_IDLE][2] = texture_for_soldier_idle_three;
  textures_for_animations[AnimationState::SOLDIER_IDLE][3] = texture_for_soldier_idle_four;
  textures_for_animations[AnimationState::SOLDIER_IDLE][4] = texture_for_soldier_idle_five;
  textures_for_animations[AnimationState::SOLDIER_IDLE][5] = texture_for_soldier_idle_six;

  textures_for_animations[AnimationState::ORC_IDLE][0] = texture_for_orc_idle_one;
  textures_for_animations[AnimationState::ORC_IDLE][1] = texture_for_orc_idle_two;
  textures_for_animations[AnimationState::ORC_IDLE][2] = texture_for_orc_idle_three;
  textures_for_animations[AnimationState::ORC_IDLE][3] = texture_for_orc_idle_four;
  textures_for_animations[AnimationState::ORC_IDLE][4] = texture_for_orc_idle_five;
  textures_for_animations[AnimationState::ORC_IDLE][5] = texture_for_orc_idle_six;


  textures_for_animations[AnimationState::SOLDIER_ATTACK].resize(5);
  textures_for_animations[AnimationState::ORC_ATTACKING].resize(5);

  textures_for_animations[AnimationState::SOLDIER_ATTACK][0] = texture_for_soldier_attack_first_anim;
  textures_for_animations[AnimationState::SOLDIER_ATTACK][1] = texture_for_soldier_attack_second_anim;
  textures_for_animations[AnimationState::SOLDIER_ATTACK][2] = texture_for_soldier_attack_third_anim;
  textures_for_animations[AnimationState::SOLDIER_ATTACK][3] = texture_for_soldier_attack_fourth_anim;
  textures_for_animations[AnimationState::SOLDIER_ATTACK][4] = texture_for_soldier_attack_fifth_anim;

  textures_for_animations[AnimationState::ORC_ATTACKING][0] = texture_for_orc_attacking_first_anim;
  textures_for_animations[AnimationState::ORC_ATTACKING][1] = texture_for_orc_attacking_second_anim;
  textures_for_animations[AnimationState::ORC_ATTACKING][2] = texture_for_orc_attacking_three_anim;
  textures_for_animations[AnimationState::ORC_ATTACKING][3] = texture_for_orc_attacking_four_anim;
  textures_for_animations[AnimationState::ORC_ATTACKING][4] = texture_for_orc_attacking_five_anim;



  textures_for_animations[AnimationState::SOLDIER_WALKING].resize(7);
  textures_for_animations[AnimationState::ORC_WALKING].resize(7);
  
  textures_for_animations[AnimationState::SOLDIER_WALKING][0] = texture_for_soldier_walking_first_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][1] = texture_for_soldier_walking_second_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][2] = texture_for_soldier_walking_third_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][3] = texture_for_soldier_walking_fourth_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][4] = texture_for_soldier_walking_fifth_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][5] = texture_for_soldier_walking_sixth_anim;
  textures_for_animations[AnimationState::SOLDIER_WALKING][6] = texture_for_soldier_walking_seventh_anim;

  textures_for_animations[AnimationState::ORC_WALKING][0] = texture_for_orc_walking_first_anim;
  textures_for_animations[AnimationState::ORC_WALKING][1] = texture_for_orc_walking_second_anim;
  textures_for_animations[AnimationState::ORC_WALKING][2] = texture_for_orc_walking_three_anim;
  textures_for_animations[AnimationState::ORC_WALKING][3] = texture_for_orc_walking_four_anim;
  textures_for_animations[AnimationState::ORC_WALKING][4] = texture_for_orc_walking_five_anim;
  textures_for_animations[AnimationState::ORC_WALKING][5] = texture_for_orc_walking_six_anim;
  textures_for_animations[AnimationState::ORC_WALKING][6] = texture_for_orc_walking_seven_anim;

  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY].resize(6);

  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][0] = texture_for_soldier_special_attack_one;
  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][1] = texture_for_soldier_special_attack_two;
  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][2] = texture_for_soldier_special_attack_three;
  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][3] = texture_for_soldier_special_attack_four;
  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][4] = texture_for_soldier_special_attack_five;
  textures_for_animations[AnimationState::SOLDIER_SPECIAL_ABILITY][5] = texture_for_soldier_special_attack_six;

  textures_for_animations[AnimationState::SOLDIER_HURT].resize(4);
  textures_for_animations[AnimationState::ORC_HURT].resize(4);

  textures_for_animations[AnimationState::SOLDIER_HURT][0] = texture_for_soldier_hurt_first_anim;
  textures_for_animations[AnimationState::SOLDIER_HURT][1] = texture_for_soldier_hurt_second_anim;
  textures_for_animations[AnimationState::SOLDIER_HURT][2] = texture_for_soldier_hurt_third_anim;
  textures_for_animations[AnimationState::SOLDIER_HURT][3] = texture_for_soldier_hurt_four_anim;

  textures_for_animations[AnimationState::ORC_HURT][0] = texture_for_orc_hurt_first_anim;
  textures_for_animations[AnimationState::ORC_HURT][1] = texture_for_orc_hurt_second_anim;
  textures_for_animations[AnimationState::ORC_HURT][2] = texture_for_orc_hurt_third_anim;
  textures_for_animations[AnimationState::ORC_HURT][3] = texture_for_orc_hurt_fourth_anim;

  textures_for_animations[AnimationState::ORC_DEATH].resize(4);

  textures_for_animations[AnimationState::ORC_DEATH][0] = texture_for_orc_death_first_anim;
  textures_for_animations[AnimationState::ORC_DEATH][1] = texture_for_orc_death_second_anim;
  textures_for_animations[AnimationState::ORC_DEATH][2] = texture_for_orc_death_third_anim;
  textures_for_animations[AnimationState::ORC_DEATH][3] = texture_for_orc_death_fourth_anim;


  //UI(Textures)
  std::string player_health_str = "Player: ";
  std::string enemy_health_str = "Enemy: ";

 


  // Inventory 
  std::string inventory_declaration = "Inventory:";
  std::string inventory_player_hp = "Base HP: ";
  std::string inventory_player_money = "Money: ";
  std::string inventory_player_attack = "Base AP: ";

  // Shop

  std::string shop_players_inventory = "(Click To Sell)"; 
  std::string shop_price_potion = std::to_string(static_cast<int>(Values::POTION) * SCALING_FACTOR_FOUR);
  std::string shop_price_mushroom = std::to_string(static_cast<int>(Values::MUSHROOM) * SCALING_FACTOR_FOUR);
  std::string shop_price_ruby_ring = std::to_string(static_cast<int>(Values::RING) * SCALING_FACTOR_TWO); 
  std::string shop_price_sapphire_ring = std::to_string(static_cast<int>(Values::RING) * SCALING_FACTOR_THREE); 
  std::string shop_price_gold_sapphire_ring = std::to_string(static_cast<int>(Values::RING) * SCALING_FACTOR_FOUR);
  std::string shop_price_gold_sword = std::to_string(static_cast<int>(Values::SWORD) * SCALING_FACTOR_THREE);
  std::string shop_price_big_gold_sword = std::to_string(static_cast<int>(Values::SWORD) * SCALING_FACTOR_FOUR); 


  SDL_Surface* surface_for_inventory_declaration = TTF_RenderText_Blended(main_tools->getMainFont(), inventory_declaration.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_for_inventory_declaration = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_inventory_declaration);
  SDL_FreeSurface(surface_for_inventory_declaration);

  SDL_Surface* surface_for_inventory_hp = TTF_RenderText_Blended(main_tools->getMainFont(), inventory_player_hp.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_for_inventory_hp = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_inventory_hp);
  SDL_FreeSurface(surface_for_inventory_hp);

  SDL_Surface* surface_for_inventory_ap = TTF_RenderText_Blended(main_tools->getMainFont(), inventory_player_attack.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_for_inventory_ap = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_inventory_ap);
  SDL_FreeSurface(surface_for_inventory_ap);

  SDL_Surface* surface_for_inventory_money = TTF_RenderText_Blended(main_tools->getMainFont(), inventory_player_money.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_for_inventory_money = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_inventory_money);
  SDL_FreeSurface(surface_for_inventory_money);

  textures_for_UI[UI::INVENTORY_TEXT_FOR_ATTACK] = texture_for_inventory_ap;
  textures_for_UI[UI::INVENTORY_TEXT_FOR_HP] = texture_for_inventory_hp;
  textures_for_UI[UI::INVENTORY_TEXT_FOR_INVENTORY_DECLARATION] = texture_for_inventory_declaration;
  textures_for_UI[UI::INVENTORY_TEXT_FOR_MONEY] = texture_for_inventory_money;

  SDL_Surface* title_player_hp_surface = TTF_RenderText_Blended(main_tools->getMainFont(), player_health_str.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_for_player_hp = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), title_player_hp_surface);
  SDL_FreeSurface(title_player_hp_surface);



  // Shop Texts

  SDL_Surface* surface_for_inventory_shop_player = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_players_inventory.c_str(), main_tools->getTextColour()); 
  SDL_Texture* texture_for_inventory_shop_player = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_for_inventory_shop_player);
  SDL_FreeSurface(surface_for_inventory_shop_player);

  SDL_Surface* surface_price_pot = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_potion.c_str(), main_tools->getTextColour()); 
  SDL_Texture* texture_price_pot = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_pot);
  SDL_FreeSurface(surface_price_pot);

  SDL_Surface* surface_price_mushroom = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_mushroom.c_str(), main_tools->getTextColour()); 
  SDL_Texture* texture_price_mushroom = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_mushroom);
  SDL_FreeSurface(surface_price_mushroom);
  
  SDL_Surface* surface_price_ruby_ring = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_ruby_ring.c_str(), main_tools->getTextColour()); 
  SDL_Texture* texture_price_ruby_ring = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_ruby_ring);
  SDL_FreeSurface(surface_price_ruby_ring);

  SDL_Surface* surface_price_sapphire_ring = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_sapphire_ring.c_str(), main_tools->getTextColour());  
  SDL_Texture* texture_price_sapphire_ring = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_sapphire_ring);
  SDL_FreeSurface(surface_price_sapphire_ring);

  SDL_Surface* surface_price_gold_sword = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_gold_sword.c_str(), main_tools->getTextColour()); 
  SDL_Texture* texture_price_gold_sword = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_gold_sword);
  SDL_FreeSurface(surface_price_gold_sword);

  SDL_Surface* surface_price_big_gold_sword = TTF_RenderText_Blended(main_tools->getMainFontSmallerFontSize(), shop_price_big_gold_sword.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_price_big_gold_sword = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), surface_price_big_gold_sword);
  SDL_FreeSurface(surface_price_big_gold_sword);

  textures_for_UI[UI::SHOP_INVENTORY_PLAYER_TEXT] = texture_for_inventory_shop_player;
  textures_for_UI[UI::SHOP_PRICE_POT] = texture_price_pot;
  textures_for_UI[UI::SHOP_PRICE_MUSHROOM] = texture_price_mushroom;
  textures_for_UI[UI::SHOP_PRICE_RUBY_RING] = texture_price_ruby_ring;
  textures_for_UI[UI::SHOP_PRICE_SAPPHIRE_RING] = texture_price_sapphire_ring;
  textures_for_UI[UI::SHOP_PRICE_GOLD_SWORD] = texture_price_gold_sword;
  textures_for_UI[UI::SHOP_PRICE_BIG_GOLD_SWORD] = texture_price_big_gold_sword;
  // OVDE SI STAO TREBAS URADITI DIZAJN SA SHOP I LOGIKU SA LOOP DA AKO JE NESTO KUPLJNO DA NE RENDERA CJENU AKO NIJE RENDERAJ CJENU <3
  // jos to i memory errory errori!!!!!!!!!!!!! mozda nesto za charm na tabu 




  SDL_Surface* title_enemy_hp_surface = TTF_RenderText_Blended(main_tools->getMainFont(), enemy_health_str.c_str(), main_tools->getTextColour());
  SDL_Texture* texture_enemy_hp = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), title_enemy_hp_surface);
  SDL_FreeSurface(title_enemy_hp_surface);

  SDL_Surface* inventory_surface = IMG_Load("design/InventoryBackgroundFixed.png");
  SDL_Texture* inventory_texture = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), inventory_surface);
  SDL_FreeSurface(inventory_surface);

  SDL_Surface* shop_surface = IMG_Load("design/shop.png");
  SDL_Texture* shop_texture = SDL_CreateTextureFromSurface(main_tools->getMainRenderer(), shop_surface);
  SDL_FreeSurface(shop_surface);

  textures_for_UI[UI::PLAYER_HP] = texture_for_player_hp;
  textures_for_UI[UI::ENEMY_HP] = texture_enemy_hp;
  textures_for_UI[UI::INVENTORY] = inventory_texture;
  textures_for_UI[UI::SHOP] = shop_texture;
  textures_for_UI[UI::SHOP_INVENTORY_PLAYER_TEXT] = texture_for_inventory_shop_player;


  
  
}

void Game::setGameState(GameState x)
{
  this->current_state_ = x;
}

Game::Game()
{
  current_state_ = GameState::LOADING;
  this->enemies_on_level_.resize(10);
  for(int index = 0; index < 10; index++)
  {
    this->enemies_on_level_[index].resize(10);
  }
}

Game::~Game()
{
  if(this->soldier_ != nullptr)
  {
    delete this->soldier_;
    this->soldier_ = nullptr;
  }

  for(auto& each : this->maps_)
  {
    if(each != nullptr)
    {
      delete each;
      each = nullptr;
    }
  }
}

void Game::checkingOrcsTargetLocked(Tools* main_tools, float delta_time) noexcept
{
  Soldier* player = dynamic_cast<Soldier*>(soldier_);
  int level = player->getCurrentLevel() - 1;
  Map* current_level_map = this->getMaps()[level];

  for(int index = 0; index < this->getEnemiesOnLevel()[level].size(); index++)
  {
    Orc* placeholder = dynamic_cast<Orc*>(this->getEnemiesOnLevel()[level][index]);
    if(placeholder == nullptr) { continue; }

    if(placeholder->isTargetLocked())
    {
      placeholder->moveOrcAcrossMapUsingActualPath(main_tools, current_level_map, delta_time);
      Detection direction = Detection::NOTHING_DETECTED;
      placeholder->enemyInRange(current_level_map, direction);

      if(direction != Detection::NOTHING_DETECTED)
      {

        if(!placeholder->canAttack() || placeholder->isDead() || placeholder->getAnimationState() == AnimationState::ORC_WALKING || 
        placeholder->getAnimationState() == AnimationState::ORC_PLATED_WALK || placeholder->getAnimationState() == AnimationState::ORC_ELITE_WALK) 
        { 
          continue; // was retrun!
        } 
        
        if(placeholder->getAnimationState() == AnimationState::ORC_IDLE)
        { 
          placeholder->setAnimationState(AnimationState::ORC_ATTACKING);
        }
        else if(placeholder->getAnimationState() == AnimationState::ORC_PLATED_IDLE)
        { 
          placeholder->setAnimationState(AnimationState::ORC_PLATED_ATTACK);
        }
        else if(placeholder->getAnimationState() == AnimationState::ORC_ELITE_IDLE) 
        {
          placeholder->handleAttackAnimationLogicForEliteOrcs();
        }

        
        player->setCurrentHealth(player->getCurrentHealth() - placeholder->getCurrentDamage());
        //std::cout << " [Game.cpp] checkingOrcsTargetLocked" << std::endl;
        if(player->getCurrentHealth() <= 0) 
        { 
          player->setAnimationState(AnimationState::SOLDIER_DEATH);
        }
        else
        {
          player->setAnimationState(AnimationState::SOLDIER_HURT);
        }



        placeholder->setAttackingStatus(false);
        placeholder->setCooldownForAttacking();
      }
    }
  }
}
