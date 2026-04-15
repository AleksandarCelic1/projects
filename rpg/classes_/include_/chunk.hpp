#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "tile.hpp"

class Chunk
{
  private:
    std::vector<std::vector<Tile>> tiles_; // Do i need Tile* ? 
    // You need a vector of Visual Effects << !


  public:
    // Constructor Copy Constructor Destructor

    Chunk() = default; 
    Chunk(const Chunk& copy) = delete;
    ~Chunk() = default;

    // Getters
    std::vector<std::vector<Tile>>& getTiles() noexcept { return this->tiles_; }

    // Setters

    // Functions


};


#endif