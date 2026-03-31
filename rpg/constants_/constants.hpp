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

inline const int AMOUNT_OF_PLAYERS_PER_GAME = 3;



#endif