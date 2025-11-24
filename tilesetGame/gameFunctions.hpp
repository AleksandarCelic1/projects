#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP

#include <SDL.h>
#include "celaUtility.hpp"



void controlFPS(Uint32& frame_start);
std::pair<std::vector<SDL_Texture*>, std::vector<SDL_Rect>> makeLoadingScreenText(Tools& tools) noexcept;
void moveChar(Tools& main_tools, Movement direction, float delta_time) noexcept;
bool checkCollisions(Map* current_level, Soldier* player, Movement direction) noexcept;
bool validCoordsForLocatingOrc(Map* current_map, int x, int y);
bool validateCoordsBounds(Map* current_level_map , int x, int y);
int validOrc(std::vector<Character*>& enemies, int x, int y) noexcept;
void attack(Tools& main_tools);
int getIndexFromOrc(Tools& main_tools, Detection orc_detected, int x, int y);
void dropLoot(Map* current_level_map, Character* enemy) noexcept;
void checkCollisionsWithItems(Map* current_level_map, Soldier* player, int x, int y) noexcept;
void enemySensorChecker(Soldier* player ,Map* current_level_map, std::vector<Character*>& current_level_enemies);
void breadthFirstSearch(Map* current_level_map, Orc* enemy) noexcept;
void handleDeathOfOrcs(Map* current_level, std::vector<Character*>& current_level_enemies) noexcept;
int findTargetOfMapObjects(std::vector<MapObjects*>& iterate_over, int x , int y) noexcept;
void handleEnterInput(Tools& main_tool, Game* game, bool& pump_events) noexcept;
void helperFunctionForCheckingCollisions(bool& placeholder, Map* current_level, int x, int y) noexcept;
bool resolvingBuggyCollisionWithEntities(std::vector<Character*>& current_level_enemies, int x, int y);
void doubleCheckingBFScallsWhileNotMoving(std::vector<Character*>& current_level_enemies, Soldier* player, Map* current_level);
void destroyAllTextures() noexcept;



#endif