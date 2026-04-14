#ifndef ACCOUNT_STRUCTS_HPP
#define ACCOUNT_STRUCTS_HPP

typedef struct 
{
  int user_special_char = 0;
  int pass_special_char_ = 1;
  int pass_lowercase_letter_ = 1;
  int pass_uppercase_letter_ = 1;
  int pass_number_ = 1;

} UsernamePasswordConstraints;

typedef struct 
{
  int username_min_ = 4;
  int username_max_ = 16;
  int password_min_ = 8;
  int password_max_ = 16;
} UsernamePasswordSizes;



#endif