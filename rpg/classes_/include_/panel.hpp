#ifndef PANEL_HPP
#define PANEL_HPP

#include "elementUI.hpp"

/*
  When virtually inheriting a class, any ctor calls in this case from Panel to ElementUI,
  are completely ignored, and the Panel is entirely responsible for constructing the 
  virtual base class
*/
class Panel : public ElementUI
{
  private:
    // Panel Delay < ! > 
    float time_passed_;
    float panel_delay_;
    float smooth_duration_;

  protected:

    /* This is done to avoid having pure virtual class */
    Panel() = default;
    Panel(const TextureAsset& asset, int scaling_factor, float time_passed, float panel_delay, float smooth_duration);

  public:
    // Copy Constructor Destructor 
    Panel(const Panel& copy) = delete;
    virtual ~Panel();

    // Getters
    float getTimePassed() const noexcept { return this->time_passed_; }
    float getPanelDelay() const noexcept { return this->panel_delay_; }
    float getSmoothDuration() const noexcept { return this->smooth_duration_; }


    // Setters
    void setTimePassed(float new_time_passed) noexcept { this->time_passed_ = new_time_passed; } 
    void setPanelDelay(float new_panel_delay)  noexcept { this->panel_delay_ = new_panel_delay; }
    void setSmoothDuration(float new_smooth_duration) noexcept { this->smooth_duration_ = new_smooth_duration; }

    // Pure Virtual
    virtual void renderPanel(Game& game) noexcept;
};


#endif