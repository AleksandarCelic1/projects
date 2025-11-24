#ifndef BANNER_HPP
#define BANNER_HPP


#include "mapObjects.hpp"

class Banner : virtual public MapObjects
{
  public:
    Banner();
    Banner(const Banner& copy ) = delete;
    ~Banner() = default;

    void updateAnimation(float delta_time) override;
};


#endif