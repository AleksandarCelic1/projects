#ifndef GOLDSAPPHIRERING_HPP
#define GOLDSAPPHIRERING_HPP

#include "ring.hpp"

class GoldSapphireRing : public Ring
{
  public:
    GoldSapphireRing();
    GoldSapphireRing(const GoldSapphireRing& copy) = delete;
    ~GoldSapphireRing() = default;
};

#endif