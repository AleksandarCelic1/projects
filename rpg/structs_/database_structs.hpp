#ifndef DATABASE_STRUCTS_HPP
#define DATABASE_STRUCTS_HPP

#include "../constants_/constants.hpp"

struct LoadedCharValues 
{
  std::string name_;
  std::string character_id_;
  int location_;
  int world_x_;
  int world_y_;
  int level_;
  int class_;
  int anim_state_;
  int anim_index_;
};


#endif