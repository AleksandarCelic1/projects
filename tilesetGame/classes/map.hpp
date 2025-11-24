#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <SDL.h>

class Tools;
class MapObjects;

class Map
{
  private:
    std::vector<std::vector<int>> grid_;
    std::vector<std::vector<SDL_Texture*>> textures_;
    std::vector<MapObjects*> current_object_on_this_level_;
    SDL_Rect maps_box_;

  public:
    Map();
    Map(std::vector<std::vector<int>> new_grid);
    Map(const Map& copy) = delete;
    ~Map();

    std::vector<std::vector<int>>& getGrid() {return this->grid_;}
    std::vector<MapObjects*>& getMapObjects() { return this->current_object_on_this_level_;}

    std::pair<SDL_Rect, SDL_Rect> getRightSrcAndDstRect(int x_axis, int y_axis, int tag, int x_off_set) noexcept;
    std::pair<SDL_Rect, SDL_Rect> getSrcAndDstRectForAnimations(int x_axis, int y_axis,SDL_Texture* current_frames_texture) noexcept;
    std::pair<SDL_Rect, SDL_Rect> findDimenstionsForMapObjects(int x_axis, int y_axis, SDL_Texture* texture_current, int x_off_set) noexcept;

    void renderMap(Tools* main_tools) noexcept;
    void renderHealth(Tools* main_tools) noexcept;
    void renderPlayer(Tools* main_tools) noexcept;
    void renderOrcs(Tools* main_tools) noexcept;
    void renderMapObjects(Tools* main_tools) noexcept;
    bool checkLastRenderedPieceIfVerticalWall(int x, int y);

    bool doTexturesMatch(SDL_Texture* texture_current, std::vector<SDL_Texture*>& vector_of_specific_animation);
    
};




#endif