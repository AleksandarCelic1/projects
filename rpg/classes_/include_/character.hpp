#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../../constants_/constants.hpp"
#include "../../constants_/enums.hpp"

class Character
{
  private:
    size_t gold_;
    size_t silver_;
    size_t bronze_;
    size_t level_;

    int base_health_;
    int current_health_;

    int base_attack_;
    int current_attack_;



    float attack_speed_;


    

};


#endif