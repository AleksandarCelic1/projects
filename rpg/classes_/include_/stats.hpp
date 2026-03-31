#ifndef STATS_HPP
#define STATS_HPP

#include "../../constants_/constants.hpp"
#include "../../constants_/enums.hpp"

class Stats
{
  private:
    int base_health_;
    int base_damage_;

    int base_mana_;
    int current_mana_;

    float physical_attack_speed_; // FORMULA 1/ attack speed to achieve 
    float magic_attack_speed_;
    
    float hit_rating_;

    float physical_crit_chance_;
    float magic_crit_chance_;




    

};


#endif