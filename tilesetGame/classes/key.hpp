#ifndef KEY_HPP
#define KEY_HPP


#include "mapObjects.hpp"

enum class KeyType
{
  SILVER_KEY,
  GOLD_KEY
};


class Key : virtual public MapObjects
{ // Dva tipa kljuca imaju sivi i zlatni
  private:
    KeyType type_;

  public:
    Key() = default;
    Key(KeyType new_type);
    Key(const Key& copy) = delete;
    ~Key() = default;


    void updateAnimation(float delta_time) override;

    KeyType getType() const { return this->type_;}
    void setType(KeyType new_type) { this->type_ = new_type;}
    

};




#endif