#ifndef TILE_HPP
#define TILE_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"

class Tile
{
  private: 
    FloorType type_;

    // Grid Coords arent necessary as they are precomputed from accessing specific tile
    int world_x_; 
    int world_y_;

  public:
    // Constructor Copy Constructor Desctructor
    Tile() = default; // Not Used 
    Tile(FloorType new_type, int world_x, int world_y);
    Tile(const Tile& copy) = delete;
    ~Tile() = default;

    // Getters

    FloorType getFloorType() const { return this->type_; }
    int getWorldX() const { return this->world_x_; }
    int getWorldY() const { return this->world_y_; }

    // Setters -- Not sure if those are going to be needed << !

    void setFloorType(FloorType& new_type) noexcept { this->type_ = new_type; }
    void setWorldX(int& new_x) noexcept { this->world_x_ = new_x; }
    void setWorldY(int& new_y) noexcept { this->world_y_ = new_y; }

    // Functions

    void render(SDL_Renderer* renderer) noexcept;
};



#endif