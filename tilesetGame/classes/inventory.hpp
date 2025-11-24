#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <utility>
#include "button.hpp"
#include "../enums.hpp"

class Item;
class Tools;
class Soldier;



class Inventory
{
  private:
    std::vector<Item*> current_items_;
    std::vector<std::vector<Button>> buttons_;
    std::unordered_map<ArmorSlot, Button> players_armor_;

    SDL_Rect coords_dimensions;

  public:
    Inventory(Tools* main_tools);
    Inventory(const Inventory& copy) = delete;
    ~Inventory();

    std::vector<Item*>& getCurrentItems() {return this->current_items_;}
    std::vector<std::vector<Button>>& getButtons()  {return this->buttons_;}
    std::unordered_map<ArmorSlot, Button>& getArmorFromInventory() {return this->players_armor_;}
    SDL_Rect getRect() const { return this->coords_dimensions;}

    void addItem(Item* new_item);
    

    void renderInventory(Tools& main_tools) noexcept;
    void initButtons(Tools* main_tools) noexcept;
    void setRect( SDL_Rect& new_rect) { this->coords_dimensions = new_rect; }
    void checkBoundInventorySlots(Soldier* player, int x_mouse, int y_mouse) noexcept;
    void printItems(Tools& main_tools, int inventory_x, int inventory_y) noexcept;
    void printArmory(Tools& main_tools, int inventory_x, int inventory_y) noexcept;
    void printStats(Tools& main_tools, Soldier* player) noexcept;
    
};


bool isMouseInsideArmoryCheck(int x_mouse, int y_mouse, int x, int y, int w, int h);
std::tuple<Grid , Grid, Grid> getDimensionsOfItemAndTextureKey(Item* item_to_identify);
Item* identifyItem(Item* item_to_identify);

#endif