#ifndef HOURGLASS_HPP
#define HOURGLASS_HPP

#include "../enums.hpp"

class Tools;


class Hourglass
{
  private:
    bool should_rotate_;


    AnimationState animation_state_;
    int current_frame_;
    float animation_timer_;
    float frame_duration_;
    int total_frames_;
    bool is_animating_frame_;


  public:
    Hourglass();
    Hourglass(const Hourglass& copy) = delete;
    ~Hourglass() = default;


    //Getters
    AnimationState getAnimationState() const { return this->animation_state_;}
    int getCurrentFrame() const { return this->current_frame_;}
    float getFrameDuration() const { return this->frame_duration_;}
    float getAnimationTimer() const { return this->animation_timer_;}
    int getTotalAmountOfFrames() const { return this->total_frames_;}
    bool getAnimatingStatus() const { return this->is_animating_frame_;}

    bool isRotating() const { return this->should_rotate_;}


    //Setters
    void setAnimationState(AnimationState new_state);
    void setCurrentFrame(int new_current_frame) { this->current_frame_ = new_current_frame;}
    void setFrameDuration(float new_frame_duration ) { this->frame_duration_ = new_frame_duration;}
    void setAnimatingStatus(bool x) { this->is_animating_frame_ = x;}
    void setTotalAmountOfFrames(int new_amount) { this->total_frames_ = new_amount;}
    void setAnimatingTimer(float new_anim_timer) { this->animation_timer_ = new_anim_timer;}

    void setRotatingStatus(bool x) { this->should_rotate_ = x;}


    void renderHourglass(Tools* main_tools) noexcept;
    void updateAnimation(float delta_time) noexcept;





};


#endif