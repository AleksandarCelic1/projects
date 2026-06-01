#ifndef TRANSITION_MANAGER_HPP
#define TRANSITION_MANAGER_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../namespaces_/namespaces.hpp"

class Game;

class TransitionManager
{
  private:
    bool transition_;
    GameState target_state_;



  public:
    TransitionManager() = default;
    TransitionManager(const TransitionManager& copy) = delete;
    ~TransitionManager();

    // Getters
    bool& getTransitionStatus() noexcept { return this->transition_; }
    GameState& getTragetState() noexcept { return this->target_state_; }

    // Setters
    void setTransitionStatus(bool new_status) noexcept { this->transition_ = new_status; }
    void setTargetState(GameState new_state) noexcept { this->target_state_ = new_state; }

    // Methods
    void transition(Game& game) noexcept;

};


#endif