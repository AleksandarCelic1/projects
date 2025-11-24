#ifndef SAPPHIRERING_HPP
#define SAPPHIRERING_HPP

#include "ring.hpp"

class SapphireRing : public Ring
{
  public:
    SapphireRing();
    SapphireRing(const SapphireRing& copy) = delete;
    ~SapphireRing() = default;
};

#endif
