#ifndef TRINKET_HPP
#define TRINKET_HPP

#include "item.hpp"
class Soldier;

enum class TrinketType
{
  RUBY,
  GOLDRUBY,
  SAPPHIRE
};

class Trinket : virtual public Item
{
  private:
    TrinketType type_;
    bool equiped_;
    
  public:
    Trinket(TrinketType type);
    Trinket(const Trinket& copy) = delete;
    ~Trinket() = default;



    TrinketType getType() const { return this->type_;}
    void setType(TrinketType x ) { this->type_ = x;}
    void use(Character* player) override;

    void handleTrinketLogic(Soldier* player) noexcept;
};

#endif