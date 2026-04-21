#ifndef CONSTANTS__HPP
#define CONSTANTS__HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <typeinfo>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cctype>


inline const int INTERNAL_SCREEN_WIDTH = 1280; //   640 * 2
inline const int INTERNAL_SCRREN_HEIGHT = 720; //   360 * 2

inline const std::vector<std::pair<int, int>> RESOLUTIONS = 
{ {INTERNAL_SCREEN_WIDTH, INTERNAL_SCRREN_HEIGHT},
  {1920, 1080},
  {2560, 1440}
};

inline const int SCALING_FACTOR_TWO = 2;
inline const int SCALING_FACTOR_THREE = 3;
inline const int SCALING_FACTOR_FOUR = 4;

inline const int MAXIMUM_BRONZE_AND_SILVER = 99;
inline const int MAXIMUM_GOLD = 999999;

inline const int STARTING_CHARACTER_WORLD_X = 0;
inline const int STARTING_CHARACTER_WORLD_Y = 0;

inline const int FPS = 60;
inline const int FRAME_DELAY = 1000 / FPS;
inline const float ONE_SECOND = 1000.0f; 

extern std::map<std::pair<SDL_Keycode, bool>, char> SDL_KEYS;

#endif