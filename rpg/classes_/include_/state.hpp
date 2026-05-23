#ifndef STATE_HPP
#define STATE_HPP

#include "quadtree.hpp"

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"

class Game;

class State
{
  private:
    QuadTree* quad_tree_;
    SDL_Renderer* renderer_;
    std::unordered_map<Offsets, std::pair<int, int>> offsets_;

  public:
    // Constructor Copy Constructor Desctructor
    State() = default;
    State(SDL_Renderer* main_renderer, int window_width, int window_height);
    State(const State& copy) = delete;
    virtual ~State();

    // Getters 
    QuadTree* getQuadTree() noexcept { return this->quad_tree_; }
    SDL_Renderer* getRenderer() const { return this->renderer_; }
    std::unordered_map<Offsets, std::pair<int,int>>& getOffsetMap() noexcept { return this->offsets_; }
    const std::pair<int, int>& getOffset(Offsets key)  { return this->offsets_.at(key); } 

    // Setters
    void setRenderer(SDL_Renderer* new_rend) noexcept { this->renderer_ = new_rend; }
    void setQuadTree(QuadTree* new_quad_tree) noexcept { this->quad_tree_ = new_quad_tree; }

    // Functions
    int centerX(int x, int screen_width, int object_width);
    int centerY(int y, int screen_height, int object_height);



    virtual void dispatchKeyboardInput(Game& game) = 0;
    virtual void dispatchMouseInput(Game& game) = 0;
    virtual void render(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void initializeUIOffsets(Game& game) = 0;
    virtual void handleEnter(Game& game) = 0;
};

#endif