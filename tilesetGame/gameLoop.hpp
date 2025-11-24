#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "gameFunctions.hpp"

Errors game_loop(Tools& main_tool);
void calculateDeltaTime(float& delta_time, Uint32 current_frame, Uint32 last_frame);
void updateDeltaTimesForEntities(std::vector<Character*>& current_level_enemies, Soldier* player, float& delta_time);
void handleDeathOfOrcs(Map* current_level, std::vector<Character*>& current_level_enemies) noexcept;
void updateDeltaTimesForMapObjects(Game* game, Soldier* player, float& delta_time);
void updateDeltaTimeForHourglass(Hourglass* hourglass, float delta_time) noexcept;

void handleTransitioning(Tools* main_tools, float& delta_time) noexcept;
void handlingStates(Tools& main_tool, float& delta_time ) noexcept;
void updateLerpForEnemiesOnCurrentLevel(Tools* main_tools, Map* current_level_map ,std::vector<Character*>& current_level_enemies, float& delta_time);





#endif