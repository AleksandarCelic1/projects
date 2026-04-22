#ifndef STATE_HPP
#define STATE_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"


class Game;

class State
{
  private:
    SDL_Renderer* renderer_;

  public:
    // Constructor Copy Constructor Desctructor
    State() = default;
    State(SDL_Renderer* main_renderer);
    State(const State& copy) = delete;
    virtual ~State() = default;

    // Getters 
    SDL_Renderer* getRenderer() const { return this->renderer_; }

    // Setters
    void setRenderer(SDL_Renderer* new_rend) noexcept { this->renderer_ = new_rend; }

    // Functions
    int centerX(int x, int screen_width, int object_width);
    int centerY(int y, int screen_height, int object_height);



    virtual void dispatchKeyboardInput(Game& game) = 0;
    virtual void dispatchMouseInput(Game& game) = 0;
    virtual void render(Game& game) = 0;
    virtual void update(Game& game) = 0;
};

#endif