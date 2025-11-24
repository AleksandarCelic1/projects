#ifndef RUBYRING_HPP
#define RUBYRING_HPP

#include "ring.hpp"

class RubyRing : public Ring
{
  public:
    RubyRing();
    RubyRing(const RubyRing& copy) = delete;
    ~RubyRing() = default;
};

#endif