#ifndef SHOPKEEPER_HPP
#define SHOPKEEPER_HPP

#include "inventory.hpp"
#include "../enums.hpp"
#include "mapObjects.hpp"


class Tools;

class Shopkeeper : virtual public MapObjects
{
  private:
    std::vector<Item*> items_to_sell_;
    std::vector<std::vector<Button>> buttons_;
    SDL_Rect coords_and_dimensions_;
    
  public:
    Shopkeeper();
    Shopkeeper(const Shopkeeper& copy) = delete;
    ~Shopkeeper() = default;

    void updateAnimation(float delta_time) override;
    void use(Tools& main_tools) noexcept;
    void initDimensionsForRendering(Tools* main_tools) noexcept;
    void printShopkeepersItemsToSell(Tools& main_tools) noexcept;
    void checkBoundsForBuy(Character* player, int mouse_x, int mouse_y);
    void renderPrices(Tools& main_tools, UI price_of_item, int x, int y) noexcept;
};

UI itemIdentifierForPrices(Item* item_to_identify);


#endif