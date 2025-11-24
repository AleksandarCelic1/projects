#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "SDL.h"
#include "../enums.hpp"

class Map;
class Tools;
class Game;
class Inventory;
class Armor;

class Character
{
  protected:
    int base_health_;
    int base_damage_;
    int current_health_;
    int current_damage_;
    int money_;


    int current_level_;
    int last_level_visited_;
    int idle_zone_index_;
    bool can_attack_;
    bool can_move_;

    int previous_tile_tag_;
    int current_tile_tag_;

    // Delta Time Variables

    AnimationState animation_state_;
    int current_frame_;
    float animation_timer_;
    float frame_duration_;
    int total_frames_;
    bool is_animating_frame_;



    // Coordinates
    int x_;
    int y_;
    int target_x_;
    int target_y_;
    float x_axis_;
    float y_axis_;
    float target_x_axis;
    float target_y_axis;


    Inventory* items_;
    Armor* armor_;

    SDL_Texture* chars_texture_;
    SDL_Rect chars_box;
    // Inventory class that contains itself of a vector of item*

    bool looking_up_;
    bool looking_down_;
    bool looking_right_;
    bool looking_left_;

    bool is_in_shop_;

    bool is_dead_;
    bool ready_to_be_removed_;
    float death_timer_;
  public:

    Character() = default;
    Character(const Character& copy) = delete;
    virtual ~Character() = default; 
    


    //  Special Ability
    virtual void ability(Game* game) = 0;

    // Getters :)
    int getBaseHealth() const {return this->base_health_;}
    int getBaseDamage() const {return this->base_damage_;}
    int getCurrentHealth() const {return this->current_health_;}
    int getCurrentDamage() const {return this->current_damage_;}
    int getMoney() const {return this->money_;}
    int getCurrentLevel() const {return this->current_level_;}
    int getCurrentTileTag() const { return this->current_tile_tag_;}
    int getLastTileTag() const { return this->previous_tile_tag_;}
    int getIdleZoneIndex() const { return this->idle_zone_index_;}
    int getLastLevelVisited() const { return this->last_level_visited_;}

    SDL_Texture* getSDLTexture() const {return this->chars_texture_;}
    SDL_Rect& getSDLRect() {return this->chars_box;}

    Detection getLookingDireciton() noexcept;
    bool isLookingDown() { return this->looking_down_;}
    bool isLookingUp() { return this->looking_up_;}
    bool isLookingRight() {return this->looking_right_;}
    bool isLookingLeft() {return this->looking_left_;}
    bool canAttack() const { return this->can_attack_;}
    bool canMove() const { return this->can_move_;}
    bool isDead() const { return this->is_dead_;}
    bool isInShop() const { return this->is_in_shop_;}
    bool isFullyDead() const { return this->ready_to_be_removed_;}

    int getXcoordinate() const { return this->x_;}
    int getYcoordinate() const { return this->y_;}
    int getTargetXGridCoord() const { return this->target_x_;}
    int getTargetYGridCoord() const { return this->target_y_;}

    float getXAxisCoordinate() const { return this->x_axis_;}
    float getYAxisCoordinate() const { return this->y_axis_;}

    float getTargetXCoord() const { return this->target_x_axis;}
    float getTargetYCoord() const { return this->target_y_axis;}
    Armor* getArmor() const { return this->armor_;}

    Inventory* getInventory() const { return this->items_;}

    int getCurrentFrame() const { return this->current_frame_;}
    AnimationState getAnimationState() const { return this->animation_state_;}



    // Setters :)

    void setBaseHealth(int new_health) { this->base_health_ = new_health;}
    void setBaseDamage(int new_damage) { this->base_damage_ = new_damage; this->current_damage_ = base_damage_;}
    void setCurrentHealth(int new_health_curr) { this->current_health_ = new_health_curr;}
    void setCurrentDamage(int new_damage_curr) { this->current_damage_ = new_damage_curr;}
    void setMoney(int new_money) { this->money_ = new_money;}
    void setCurrentLevel(int new_level) {this->last_level_visited_ = current_level_; this->current_level_ = new_level;}
    void setAttackingStatus(bool x ) { this->can_attack_ = x;}
    void setMovingStatus(bool x) { this->can_move_ = x;}
    void setXaxisCoords(int new_x_axis) { this->x_axis_ = new_x_axis;}
    void setYaxisCoords(int new_y_axis) { this->y_axis_ = new_y_axis;}
    void setCurrentTileTag(int new_tile_tag)  { this->current_tile_tag_ = new_tile_tag;}
    void setPreviousTileTag(int new_tile_tag) { this->previous_tile_tag_ = new_tile_tag;}
    void setIdleZoneIndex(int new_index) { this->idle_zone_index_ = new_index;}
    void setLastLevelVisited(int last_level_visited) {this->last_level_visited_ = last_level_visited;}
    void setTotalFrames(int total_frames_new) { this->total_frames_ = total_frames_new;}
    void setTargetXAxis(float new_x) { this->target_x_axis = new_x;}
    void setTargetYAxis(float new_y) { this->target_y_axis = new_y;}
    void setShopStatus(bool x ) { this->is_in_shop_ = x;}
    void setTargetXGridCoord(int new_x) { this->target_x_ = new_x;}
    void setTargetYGridCoord(int new_y) { this->target_y_ = new_y;}
    
    void setSDLTexture(SDL_Texture* assign_this) { this->chars_texture_ = assign_this;}
    void setSDLRect(SDL_Rect& new_rect) {this->chars_box = new_rect;}

    void setLookingDirection(Movement direction) noexcept;

    void setXcoordinate(int x ) { this->x_ = x;}
    void setYcoordinate(int y) { this->y_ = y;}

    void setInventory(Inventory* new_inv) { this->items_ = new_inv;}
    void setArmor(Armor* new_armor) {this->armor_ = new_armor;}

    void setDead() { this->is_dead_ = true;}
    void findCoordsLevelStart(Game* game);

    
    void enemyInRange(Map* current_level, Detection& direction_where_orc);
    void setAnimationState(AnimationState new_state) noexcept;
    void updateAnimation(float delta_time) noexcept;
    bool isDeathAnimationFinished();
    void updateDeathTimerCooldown(float& delta_time) noexcept;

    void calculateTargetCoordsForLerp(Tools* tool,Movement direction, float delta_time);
    void updateLerp(Tools* main_tools, Map* current_level, float delta_time);
    
    
};





#endif