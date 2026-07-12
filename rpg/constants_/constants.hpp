#ifndef CONSTANTS__HPP
#define CONSTANTS__HPP

// To collapse all functions in a file in VsCode -> CTRL K, CTRL 0

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
#include <queue>
#include <libpq-fe.h>
#include <optional>

#include "../enums_/enums.hpp"



// Resolution - Scaling Factors
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

// In-game Currency
inline const int MAXIMUM_BRONZE_AND_SILVER = 99;
inline const int MAXIMUM_GOLD = 999999;

inline const int STARTING_CHARACTER_WORLD_X = 0;
inline const int STARTING_CHARACTER_WORLD_Y = 0;

// Delta Time
inline const int FPS = 60;
inline const int FRAME_DELAY = 1000 / FPS;
inline const float ONE_SECOND = 1000.0f; 

// UI Width x Height 
inline const int LOGIN_TEXT_PLACEHOLDER_WIDTH = 151;
inline const int LOGIN_TEXT_PLACEHOLDER_HEIGHT = 28;
inline const int TEXT_X_OFFSET = 10; 
inline const int LIMIT_LETTER_TEXT_PLACEHOLDER = 12;

inline const int INVALID_NUMBER = -1;

// QuadTree
inline const int QUADTREE_CAPACITY = 4;

// BitMap 
inline const int LETTER_WIDTH_AND_HEIGHT = 8;
inline const int AMOUNT_OF_LETTERS = 77;

// SDL_Keycode map -> char -> glyph
extern std::map<std::pair<SDL_Keycode, bool>, char> SDL_KEYS;

// Type of Placeholder -> its width-height
extern std::map<TextPlaceholderType, std::pair<int, int>> PLACEHOLDER_WIDTH_HEIGHT;



#endif