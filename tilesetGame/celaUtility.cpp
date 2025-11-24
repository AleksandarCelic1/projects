#include "celaUtility.hpp"

std::unordered_map<Grid, SDL_Texture*> textures_for_map;
std::unordered_map<UI, SDL_Texture*> textures_for_UI;
std::unordered_map<AnimationState, std::vector<SDL_Texture*>> textures_for_animations;

void Tools::setMainRenderer(SDL_Renderer* new_renderer)
{
  this->main_renderer_ = new_renderer;
}

void Tools::setMainWindow(SDL_Window* new_window)
{
  this->main_window_ = new_window;
}

Errors Tools::initializeTheWindowRendererFontImageColor() noexcept
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return Errors::E_SDL_INIT; // this is how you return when you have a pair of poiters to structs/classes
  }

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  window = SDL_CreateWindow("Currently Unknown", SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

  if(!window)
  {
    std::cout << "Window Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return Errors::E_SDL_WINDOW;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(!renderer)
  {
    std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return Errors::E_SDL_RENDERER;
  }

  TTF_Init(); // <--- font
  TTF_Font* font_smaller = TTF_OpenFont("design/Press_Start_2P/PressStart2P-Regular.ttf", 16);
  TTF_Font* font = TTF_OpenFont("design/Press_Start_2P/PressStart2P-Regular.ttf", 24);

  if(!font)
  {
    std::cout << "[ERROR] Font failed to load!";
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return Errors::E_FONT_LOAD_FAIL;
  }

  this->main_font_ = font;
  this->main_font_smaller_font_size = font_smaller;
  this->main_window_ = window;
  this->main_renderer_ = renderer;

  SDL_Color text_color_white = {255, 255, 255, 0};
  this->white_ = text_color_white;

  IMG_Init(IMG_INIT_PNG); // <--- images
  
  this->getDimensionsOfWholeScreen();
  this->initializeBackGround(); 
  // getting dimensions

  return Errors::SUCCESS;

}

void Tools::getDimensionsOfWholeScreen() noexcept
{
  SDL_GetRendererOutputSize(this->main_renderer_, &(this->width_window_), &(this->height_window_));
  // this gives us total width and total height of a screen
  // will be needing this since we are doing it full screen
}

void Tools::setIntroScreenInterface(SDL_Texture* new_texture) 
{
  this->introduction_screen_interface_ = new_texture;
}

void Tools::setFont(TTF_Font* new_font)
{
  this->main_font_ = new_font;
}

void Tools::setColour(SDL_Color& new_colour)
{
  this->white_ = new_colour;
}

Errors Tools::initializeBackGround() noexcept
{
  SDL_Surface* surface_ = IMG_Load("design/2dPixel/backgroundPhoto.png");
  SDL_Texture* texture_for_interface_opening = SDL_CreateTextureFromSurface(this->main_renderer_, surface_);
  SDL_FreeSurface(surface_);
  // put one check here if this fails; <------ !

  SDL_Surface* surface_tab_control_menu = IMG_Load("design/backgroundTABfinished.png");
  SDL_Texture* texture_tab_control_menu = SDL_CreateTextureFromSurface(this->main_renderer_, surface_tab_control_menu);
  SDL_FreeSurface(surface_tab_control_menu);

  SDL_Surface* surface_you_died_screen = IMG_Load("design/youdiedscreen.png");
  SDL_Texture* texture_you_died_screen = SDL_CreateTextureFromSurface(this->main_renderer_, surface_you_died_screen);
  SDL_FreeSurface(surface_you_died_screen);

  SDL_Surface* surface_you_won_screen = IMG_Load("design/youwonscreen.png");
  SDL_Texture* texture_you_won_screen = SDL_CreateTextureFromSurface(this->main_renderer_, surface_you_won_screen);
  SDL_FreeSurface(surface_you_won_screen);


  this->introduction_screen_interface_ = texture_for_interface_opening;
  this->background_tab_control_menu_ = texture_tab_control_menu;
  this->you_died_screen_ = texture_you_died_screen;
  this->you_won_screen_ = texture_you_won_screen;

  return Errors::SUCCESS;
}

void Tools::setGame(Game* new_game)
{
  this->game_ = new_game;
}

void Tools::renderUI() noexcept
{
  renderUIHealthBars();
}

void Tools::renderUIHealthBars() noexcept
{
  Soldier* player = dynamic_cast<Soldier*>(this->getGame()->getSoldier());
  Map* current_level = this->getGame()->getMaps()[player->getCurrentLevel() - 1];
  std::vector<Character*>& enemies_on_level = this->getGame()->getEnemiesOnLevel()[player->getCurrentLevel() - 1];

  int width_player_hp_text = 0;
  int height_player_hp_text = 0;

  int width_enemy_hp_text = 0;
  int height_enemy_hp_text = 0;

  SDL_QueryTexture(textures_for_UI[UI::PLAYER_HP], nullptr, nullptr, &width_player_hp_text, &height_player_hp_text);
  SDL_QueryTexture(textures_for_UI[UI::ENEMY_HP], nullptr, nullptr, &width_enemy_hp_text, &height_enemy_hp_text);

  SDL_Rect player_hp_text_box;
  player_hp_text_box.x = 50; // Top left corner
  player_hp_text_box.y = 50;
  player_hp_text_box.w = width_player_hp_text;
  player_hp_text_box.h = height_player_hp_text;

  SDL_Rect enemy_hp_text_box;
  // will define x later 
  enemy_hp_text_box.y = 50;
  enemy_hp_text_box.h = height_enemy_hp_text;
  enemy_hp_text_box.w = width_enemy_hp_text;

  SDL_RenderCopy(this->getMainRenderer(), textures_for_UI[UI::PLAYER_HP], nullptr, &player_hp_text_box);

  std::vector<SDL_Rect> current_hearths_of_player;
  std::vector<SDL_Rect> current_hearths_of_enemy;
  int gap_between_the_hearths = 14; // (pixels)

  SDL_Rect srcRect_hearth_box;
  srcRect_hearth_box.x = 0;
  srcRect_hearth_box.y = 0;
  srcRect_hearth_box.w = static_cast<int>(Grid::ALL_HEARTHS_W);
  srcRect_hearth_box.h = static_cast<int>(Grid::ALL_HEARTHS_H);


  for(int index = 0; index < player->getBaseHealth(); index++)
  {
    SDL_Rect dstRect_hearth_box;

    dstRect_hearth_box.x = player_hp_text_box.x + player_hp_text_box.w;

    if(index > 0)
    {
      dstRect_hearth_box.x = current_hearths_of_player[index - 1].x + 
      current_hearths_of_player[index - 1].w + gap_between_the_hearths;
    }
    


    dstRect_hearth_box.y = (player_hp_text_box.y + player_hp_text_box.h) / 2;
    dstRect_hearth_box.w = srcRect_hearth_box.w * 4; // 13 * 4
    dstRect_hearth_box.h = srcRect_hearth_box.h * 4; // 10 * 4

    current_hearths_of_player.push_back(dstRect_hearth_box);

    if(index < player->getCurrentHealth())
    {
      SDL_RenderCopy(this->getMainRenderer(), textures_for_map[Grid::HEARTH_FULL], &srcRect_hearth_box, &dstRect_hearth_box);
      // rendera puno srce
    }
    else
    {
      SDL_RenderCopy(this->getMainRenderer(), textures_for_map[Grid::HEARTH_EMPTY], &srcRect_hearth_box, &dstRect_hearth_box);
      // rendera prazno srce
    }

  }


  Detection orc_spotted = Detection::NOTHING_DETECTED;
  player->enemyInRange(current_level, orc_spotted);
  
  if(orc_spotted != Detection::NOTHING_DETECTED)
  {
    int index_of_detected_orc = getIndexFromOrc(*this, orc_spotted , player->getXcoordinate(), player->getYcoordinate());

    //std::cout << index_of_detected_orc;
    if(index_of_detected_orc == -1)
    {
      return;
    }

    Orc* found_orc = dynamic_cast<Orc*>(enemies_on_level[index_of_detected_orc]);
    int x_offset = this->getScreenWidth() - gap_between_the_hearths;

    for(int index = found_orc->getBaseHealth(); index > 0; index--)
    {
      //std::cout << index;
      SDL_Rect dstRect_hearth_box;

      dstRect_hearth_box.y = (enemy_hp_text_box.y + enemy_hp_text_box.h) / 2;
      dstRect_hearth_box.w = srcRect_hearth_box.w * 4; // 13 * 4
      dstRect_hearth_box.h = srcRect_hearth_box.h * 4; // 10 * 4    
      dstRect_hearth_box.x = x_offset - dstRect_hearth_box.w;

  
      current_hearths_of_enemy.push_back(dstRect_hearth_box);

      if(index > found_orc->getCurrentHealth())
      {
        SDL_RenderCopy(this->getMainRenderer(), textures_for_map[Grid::HEARTH_EMPTY], &srcRect_hearth_box, &dstRect_hearth_box);
      }
      else
      {
        SDL_RenderCopy(this->getMainRenderer(), textures_for_map[Grid::HEARTH_FULL], &srcRect_hearth_box, &dstRect_hearth_box);
      }

      x_offset -= (dstRect_hearth_box.w + gap_between_the_hearths);

      
    }

    if(!current_hearths_of_enemy.empty())
    {
      enemy_hp_text_box.x = current_hearths_of_enemy.back().x - enemy_hp_text_box.w - gap_between_the_hearths;
      SDL_RenderCopy(this->getMainRenderer(), textures_for_UI[UI::ENEMY_HP], nullptr, &enemy_hp_text_box);
    }
  }


}

Tools::~Tools()
{
  /*if(this->introduction_screen_interface_) 
  { 
    SDL_DestroyTexture(this->introduction_screen_interface_);
    this->introduction_screen_interface_ = nullptr;
  }

  if(this->background_screen_)
  {
    SDL_DestroyTexture(this->background_screen_);
    this->background_screen_ = nullptr;
  }

  if(this->background_tab_control_menu_)
  {
    SDL_DestroyTexture(this->background_tab_control_menu_);
    this->background_tab_control_menu_ = nullptr;
  }

  if(this->you_died_screen_)
  {
    SDL_DestroyTexture(this->you_died_screen_);
    this->you_died_screen_ = nullptr;
  }

  if(this->main_font_)
  {
    TTF_CloseFont(this->main_font_);
    this->main_font_ = nullptr;
  }

  if(this->main_renderer_)
  {
    SDL_DestroyRenderer(this->main_renderer_);
    this->main_renderer_ = nullptr;
  }

  if(this->main_window_)
  {
    SDL_DestroyWindow(this->main_window_);
    this->main_window_ = nullptr;
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();*/
}
