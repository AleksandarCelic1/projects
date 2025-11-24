#ifndef CELAUTILITY_HPP
#define CELAUTILITY_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <typeinfo>
#include "classes/map.hpp"
#include "classes/game.hpp"
#include "classes/character.hpp"
#include "classes/soldier.hpp"
#include "classes/orc.hpp"
#include "enums.hpp"
#include "gameFunctions.hpp"
#include "tabcontrolmenu.hpp"
#include "classes/inventory.hpp"
#include "classes/mushroom.hpp"
#include "classes/coin.hpp"
#include "classes/potion.hpp"
#include "classes/ring.hpp"
#include "classes/armory.hpp"
#include "classes/sword.hpp"
#include "classes/trinket.hpp"
#include "classes/stonesword.hpp"
#include "classes/goldsword.hpp"
#include "classes/biggoldsword.hpp"
#include "classes/rubyring.hpp"
#include "classes/sapphirering.hpp"
#include "classes/goldsapphirering.hpp"
#include "classes/candlestick.hpp"
#include "classes/mapObjects.hpp"
#include "classes/needles.hpp"
#include "classes/ladders.hpp"
#include "classes/doors.hpp"
#include "classes/torch.hpp"
#include "classes/shopkeeper.hpp"
#include "classes/banner.hpp"
#include "classes/chest.hpp"
#include "classes/box.hpp"
#include "classes/key.hpp"
#include "classes/flamethrower.hpp"
#include "classes/arrowtrap.hpp"
#include "classes/hourglass.hpp"


/*
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

// Make a rectangle matching where you'll draw the texture
SDL_Rect outlineRect = dstRect;

// Draw the outline
SDL_RenderDrawRect(renderer, &outlineRect);

// Now copy the texture
SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);*/


const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

class Tools
{
  private:
    SDL_Window* main_window_;
    SDL_Renderer* main_renderer_;
    SDL_Texture* introduction_screen_interface_;
    SDL_Texture* background_screen_;
    SDL_Texture* background_tab_control_menu_;
    SDL_Texture* you_died_screen_;
    SDL_Texture* you_won_screen_;
    TTF_Font* main_font_;
    TTF_Font* main_font_smaller_font_size;
    SDL_Color white_;
    Game* game_;


    int height_window_;
    int width_window_;

  public:

    Tools() = default;
    Tools(const Tools& copy) = delete;
    ~Tools(); // ovo pogledaj posto se sdl stvari drugcije free-aju

    SDL_Window* getMainWindow() const {return this->main_window_;}
    SDL_Renderer* getMainRenderer() const {return this->main_renderer_;}
    SDL_Texture* getIntroScreenInterface() const {return this->introduction_screen_interface_;}
    TTF_Font* getMainFont() const {return this->main_font_;}
    TTF_Font* getMainFontSmallerFontSize() const {return this->main_font_smaller_font_size;}
    SDL_Color& getTextColour() {return this->white_;}
    int getScreenHeight() const {return this->height_window_;}
    int getScreenWidth() const {return this->width_window_;}
    Game* getGame() const { return this->game_;}
    SDL_Texture* getTabTexture() const {return this->background_tab_control_menu_;}
    SDL_Texture* getDeathScreen() const { return this->you_died_screen_;}
    SDL_Texture* getWonScreen() const { return this->you_won_screen_;}
    
    


    void setMainWindow(SDL_Window* new_window);
    void setMainRenderer(SDL_Renderer* new_renderer);
    void setIntroScreenInterface(SDL_Texture* new_texture);
    void setFont(TTF_Font* new_font);
    void setColour(SDL_Color& new_colour);
    void setGame(Game* new_game);



    Errors initializeTheWindowRendererFontImageColor() noexcept;
    void getDimensionsOfWholeScreen() noexcept;
    Errors initializeBackGround() noexcept;
    void renderUI() noexcept;
    void renderUIHealthBars() noexcept;
    
    
};


extern std::unordered_map<Grid, SDL_Texture*> textures_for_map;
extern std::unordered_map<UI, SDL_Texture*> textures_for_UI;
extern std::unordered_map<AnimationState, std::vector<SDL_Texture*>> textures_for_animations;

#endif