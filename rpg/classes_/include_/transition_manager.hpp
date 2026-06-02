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
    bool fading_in_;
    bool fading_out_;

    float fade_alpha_;
    float fade_speed_;

    GameState target_state_;



  public:
    TransitionManager() = default;
    TransitionManager(const TransitionManager& copy) = delete;
    ~TransitionManager() = default;

    // Getters
    bool& getTransitionStatus() noexcept { return this->transition_; }
    bool& getFadingInStatus() noexcept { return this->fading_in_; }
    bool& getFadingOutStatus() noexcept { return this->fading_out_; }
    float& getFadeAlpha() noexcept { return this->fade_alpha_; }
    float& getFadeSpeed() noexcept { return this->fade_speed_; }
    GameState& getTragetState() noexcept { return this->target_state_; }

    // Setters
    void setTransitionStatus(bool new_status) noexcept { this->transition_ = new_status; }
    void setFadingInStatus(bool new_status) noexcept { this->fading_in_ = new_status; }
    void setFadingOutStatus(bool new_status) noexcept { this->fading_out_ = new_status; }
    void setFadeAlpha(float new_alpha) noexcept { this->fade_alpha_ = new_alpha; }
    void setFadeSpeed(float new_speed) noexcept { this->fade_speed_ = new_speed; }
    void setTargetState(GameState new_state) noexcept { this->target_state_ = new_state; }


    // Methods
    void transition(Game& game) noexcept;
    void changeStates(Game& game) noexcept;

};


#endif