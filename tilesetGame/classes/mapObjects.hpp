#ifndef MAPOBJECTS_HPP
#define MAPOBJECTS_HPP

#include "../enums.hpp"
#include <iostream>

class MapObjects 
{
  protected:
    AnimationState animation_state_;
    int current_frame_;
    float animation_timer_;
    float frame_duration_;
    int total_frames_;
    bool is_animating_frame_;

    //Coords
    int x_;
    int y_;
    int x_axis_;
    int y_axis_;
  public:
    MapObjects();
    MapObjects(const MapObjects& copy ) = delete;
    virtual ~MapObjects() = default;

    //Getters
    AnimationState getAnimationState() const { return this->animation_state_;}
    int getCurrentFrame() const { return this->current_frame_;}
    float getFrameDuration() const { return this->frame_duration_;}
    float getAnimationTimer() const { return this->animation_timer_;}
    int getTotalAmountOfFrames() const { return this->total_frames_;}
    bool getAnimatingStatus() const { return this->is_animating_frame_;}

    int getXCoord() const { return this->x_;}
    int getYCoord() const { return this->y_;}

    //Setters
    void setAnimationState(AnimationState new_state);
    void setCurrentFrame(int new_current_frame) { this->current_frame_ = new_current_frame;}
    void setFrameDuration(float new_frame_duration ) { this->frame_duration_ = new_frame_duration;}
    void setAnimatingStatus(bool x) { this->is_animating_frame_ = x;}
    void setTotalAmountOfFrames(int new_amount) { this->total_frames_ = new_amount;}
    void setAnimatingTimer(float new_anim_timer) { this->animation_timer_ = new_anim_timer;}

    void setXCoord(int new_x) { this->x_ = new_x;}
    void setYCoord(int new_y) { this->y_ = new_y;}

    // Everyone Updates Animation differently!
    virtual void updateAnimation(float delta_time) = 0;
};

#endif