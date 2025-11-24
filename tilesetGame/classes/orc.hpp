#ifndef ORC_HPP
#define ORC_HPP

#include "character.hpp"

#include <set>
#include <map>
#include <queue>

class Map;
class Soldier;
class Tools;

enum class OrcType
{
  CLASSIC,
  PLATED,
  ELITE
};

enum class AttackVariationEliteOrcs
{
  BASIC = 1,
  WHIRLWIND = 2,
  SMASH = 3
};

const int MAX_AMOUNT_OF_ATTACK_VARIATIONS = 3;

class Orc : virtual public Character
{
  private:

    OrcType type_;
    float attack_cooldown_; 
    float time_since_last_attack_;
    float cooldown_for_bfs_;
    float time_since_last_bfs_;
    bool can_call_bfs_;

    std::pair<int,int> planned_goal_;
    Uint32 last_planned_goal_ms_;

    int which_attack_to_perform_;

    int current_index_;

    bool target_locked_;
    std::map<std::pair<int,int>, std::pair<int,int>> path_;
    std::set<std::pair<int,int>> visited_;
    std::vector<std::pair<int,int>> actual_path_;
    std::queue<std::pair<int,int>> queue_;
    std::pair<int,int> player_spotted_at_;
  public:
    
    Orc(OrcType type);
    Orc(const Orc& copy) = delete;
    ~Orc();

    void ability(Game* game) override;
    void detectEnemies(Map* current_level_map) noexcept;


    OrcType getOrcType() const { return this->type_;}
    bool canCallBFS() const { return this->can_call_bfs_;}

    std::map<std::pair<int,int>, std::pair<int,int>>& getPath() { return this->path_;}
    std::set<std::pair<int,int>>& getVisitedPaths() { return this->visited_;}
    std::vector<std::pair<int,int>>& getActualPath() { return this->actual_path_;}
    std::queue<std::pair<int,int>>& getQueue() { return this->queue_;}
    std::pair<int,int>& getPlayersCordsFromOrc() { return this->player_spotted_at_;}

    bool isTargetLocked() const { return this->target_locked_;}


    void setCooldownForBFS() { this->time_since_last_bfs_ = 0.0f;}
    void setPath(std::map<std::pair<int,int>, std::pair<int,int>>& x) { this->path_ = x;}
    void setVisitedPaths(std::set<std::pair<int,int>>& x) { this->visited_ = x;}
    void setActualPath(std::vector<std::pair<int,int>>& x) { this->actual_path_ = x;}
    void setQueue(std::queue<std::pair<int,int>>& x) { this->queue_ = x;}
    void setPlayerCoordsForOrc(std::pair<int,int>& x) { this->player_spotted_at_ = x;}
    void setCooldownForAttacking() {this->time_since_last_attack_ = 0.0f;}
    void setOrcType(OrcType x ) { this->type_ = x;}
    void setTargetLockedStatus(bool x ) { this->target_locked_ = x;}

    void handleAttackAnimationLogicForEliteOrcs();

    void moveOrcAcrossMapUsingActualPath(Tools* main_tool, Map* current_level_map, float delta_time) noexcept;
    void updateAttackCooldown(float& delta_time) noexcept;
    void updateBFSCooldown(float& delta_time) noexcept;


    Uint32& getReplanMS() { return this->last_planned_goal_ms_;}
    std::pair<int,int>& getPlannedGoal() { return this->planned_goal_;}
};

#endif