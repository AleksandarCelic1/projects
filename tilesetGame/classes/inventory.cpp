#include "inventory.hpp"
#include "../celaUtility.hpp"
#include "soldier.hpp"

void Inventory::renderInventory(Tools& main_tools) noexcept
{
  bool in_inventory = true;
  SDL_Event inventory_event;
  Soldier* player = dynamic_cast<Soldier*>(main_tools.getGame()->getSoldier());
  while(in_inventory)
  {
    while(SDL_PollEvent(&inventory_event))
    {
      SDL_Keycode pressed = inventory_event.key.keysym.sym;
      if(inventory_event.type == SDL_KEYDOWN && inventory_event.key.repeat == 0)
      {
        if(pressed == SDLK_e)
        {
          in_inventory = false;
        }
      }

      if (inventory_event.type == SDL_MOUSEBUTTONDOWN)
      {
        int mouse_x = inventory_event.button.x;
        int mouse_y = inventory_event.button.y;

        checkBoundInventorySlots(player, mouse_x, mouse_y);    
      }

    }

    SDL_RenderCopy(main_tools.getMainRenderer(), main_tools.getIntroScreenInterface(), nullptr, nullptr);

    SDL_SetRenderDrawColor(main_tools.getMainRenderer(), 0, 0, 0, 128); // black 50% transparent

    SDL_Rect darken_rect = {0, 0, main_tools.getScreenWidth(), main_tools.getScreenHeight()};
    SDL_RenderFillRect(main_tools.getMainRenderer(), &darken_rect);

    


    

    SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::INVENTORY], nullptr, &this->coords_dimensions);

    int x_offset_armor = armor_x_axis_inventory;
    int y_offset_armor = armor_y_axis_inventory;

    // outline!!!
    /*
    // Draw red outlines for all armor slots
    for (int index = 1; index < static_cast<int>(Ranges::AMOUNT_OF_ARMOR); index++)
    {
      SDL_Rect outline;
      outline.x = this->coords_dimensions.x + x_offset_armor;
      outline.y = this->coords_dimensions.y + y_offset_armor;
      outline.w = cell_both_dimensions;
      outline.h = cell_both_dimensions;

      SDL_SetRenderDrawColor(main_tools.getMainRenderer(), 255, 0, 0, 255);
      SDL_RenderDrawRect(main_tools.getMainRenderer(), &outline);

      y_offset_armor += vertical_gap + cell_both_dimensions;
    }

    SDL_Rect outline;
    outline.x = this->coords_dimensions.x + sword_x_axis_inventory;
    outline.y = this->coords_dimensions.y + sword_y_axis_inventory;
    outline.w = cell_both_dimensions;
    outline.h = cell_both_dimensions;

    SDL_SetRenderDrawColor(main_tools.getMainRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRect(main_tools.getMainRenderer(), &outline);*/  // RED THING !


    // outline!!!
    printItems(main_tools, this->coords_dimensions.x, this->coords_dimensions.y);
    printArmory(main_tools, this->coords_dimensions.x, this->coords_dimensions.y);
    printStats(main_tools, player);

    SDL_RenderPresent(main_tools.getMainRenderer());
    
  }

}

void Inventory::printArmory(Tools& main_tools, int inventory_x, int inventory_y) noexcept
{
  if(this->players_armor_[ArmorSlot::SWORD].getItem() != nullptr)
  {
    Button& sword_button = this->players_armor_[ArmorSlot::SWORD];

    auto [ texture, width, height ] = getDimensionsOfItemAndTextureKey(sword_button.getItem());

    SDL_Rect placeholder;
    placeholder.w = static_cast<int>(width) * SCALING_FACTOR_TWO;
    placeholder.h = static_cast<int>(height) * SCALING_FACTOR_TWO;
    placeholder.x = inventory_x + sword_x_axis_inventory + (cell_both_dimensions / 2) - (placeholder.w / 2);
    placeholder.y = inventory_y + sword_y_axis_inventory + (cell_both_dimensions / 2) - (placeholder.h / 2);
    SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_map[texture], nullptr, &placeholder);
  }


  int x_offset_armor = armor_x_axis_inventory;
  int y_offset_armor = armor_y_axis_inventory;

  for(int index = 1; index < static_cast<int>(Ranges::AMOUNT_OF_ARMOR); index++)
  {
    Button& current_button = this->players_armor_[static_cast<ArmorSlot>(index)];
    SDL_Rect placeholder;

    if(current_button.getItem() != nullptr)
    {
      auto [ texture, width, height ] = getDimensionsOfItemAndTextureKey(current_button.getItem());

      SDL_Rect placeholder;
      placeholder.w = static_cast<int>(width) * SCALING_FACTOR_TWO;
      placeholder.h = static_cast<int>(height) * SCALING_FACTOR_TWO;
      placeholder.x = inventory_x + x_offset_armor + (cell_both_dimensions / 2) - (placeholder.w / 2);
      placeholder.y = inventory_y + y_offset_armor + (cell_both_dimensions / 2) - (placeholder.h / 2);

      SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_map[texture], nullptr, &placeholder);
    }

    y_offset_armor += vertical_gap + cell_both_dimensions;
  }
}

void Inventory::printItems(Tools& main_tools, int inventory_x, int inventory_y) noexcept
{
  int x_offset = items_inventory_x;
  int y_offset = items_inventory_y;

  for(int index = 0; index < this->getButtons().size(); index++)
  {
    for(int inner = 0; inner < this->getButtons()[index].size(); inner++)
    {
      if(this->getButtons()[index][inner].getItem() != nullptr)
      {
        auto [ texture, width, height ] = getDimensionsOfItemAndTextureKey(this->getButtons()[index][inner].getItem());

        SDL_Rect placeholder;
        placeholder.w = static_cast<int>(width) * SCALING_FACTOR_TWO;
        placeholder.h = static_cast<int>(height) * SCALING_FACTOR_TWO;
        placeholder.x = inventory_x + x_offset + (cell_both_dimensions / 2) - (placeholder.w / 2);
        placeholder.y = inventory_y + y_offset + (cell_both_dimensions / 2) - (placeholder.h / 2);

        SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_map[texture], nullptr, &placeholder);        
      }

      x_offset += horizontal_gap + cell_both_dimensions;
    }

    x_offset = items_inventory_x;
    y_offset += vertical_gap + cell_both_dimensions;
    
  }
}

void Inventory::printStats(Tools& main_tools, Soldier* player) noexcept
{
  int width_player_hp_invent = 0;
  int width_player_money = 0;
  int width_player_base_ap = 0;
  int width_inventory_declaration = 0;

  int height_player_hp_invent = 0;
  int height_player_ap_invent = 0;
  int height_player_money = 0;
  int height_inventory_declaration = 0;


  SDL_QueryTexture(textures_for_UI[UI::INVENTORY_TEXT_FOR_HP], nullptr, nullptr, &width_player_hp_invent, &height_player_hp_invent);
  SDL_QueryTexture(textures_for_UI[UI::INVENTORY_TEXT_FOR_ATTACK], nullptr, nullptr, &width_player_base_ap, &height_player_ap_invent);
  SDL_QueryTexture(textures_for_UI[UI::INVENTORY_TEXT_FOR_MONEY], nullptr, nullptr, &width_player_money, &height_player_money);
  SDL_QueryTexture(textures_for_UI[UI::INVENTORY_TEXT_FOR_INVENTORY_DECLARATION], nullptr, nullptr, &width_inventory_declaration, &height_inventory_declaration);

  std::string player_base_hp = std::to_string(player->getBaseHealth());
  std::string player_money = std::to_string(player->getMoney());
  std::string player_base_ap = std::to_string(player->getBaseDamage());

  SDL_Surface* surface_for_player_base_hp = TTF_RenderText_Blended(main_tools.getMainFont(), player_base_hp.c_str(), main_tools.getTextColour());
  SDL_Texture* texture_for_player_hp = SDL_CreateTextureFromSurface(main_tools.getMainRenderer(), surface_for_player_base_hp);
  SDL_FreeSurface(surface_for_player_base_hp);

  SDL_Surface* surface_for_player_base_ap = TTF_RenderText_Blended(main_tools.getMainFont(), player_base_ap.c_str(), main_tools.getTextColour());
  SDL_Texture* texture_for_player_ap = SDL_CreateTextureFromSurface(main_tools.getMainRenderer(), surface_for_player_base_ap);
  SDL_FreeSurface(surface_for_player_base_ap);

  SDL_Surface* surface_for_player_money= TTF_RenderText_Blended(main_tools.getMainFont(), player_money.c_str(), main_tools.getTextColour());
  SDL_Texture* texture_for_player_money = SDL_CreateTextureFromSurface(main_tools.getMainRenderer(), surface_for_player_money);
  SDL_FreeSurface(surface_for_player_money);


  int width_player_base_hp_number = 0;
  int width_player_money_number = 0;
  int width_player_base_ap_number = 0;

  int height_player_hp_invent_number = 0;
  int height_player_ap_invent_number = 0;
  int height_player_money_number = 0;

  SDL_QueryTexture(texture_for_player_hp, nullptr, nullptr, &width_player_base_hp_number, &height_player_hp_invent_number);
  SDL_QueryTexture(texture_for_player_ap, nullptr, nullptr, &width_player_base_ap_number, &height_player_ap_invent_number);
  SDL_QueryTexture(texture_for_player_money, nullptr, nullptr, &width_player_money_number, &height_player_money_number);

  SDL_Rect text_player_hp;
  text_player_hp.x = INVENTORY_PLAYER_HP_X + this->coords_dimensions.x;
  text_player_hp.y = INVENTORY_PLAYER_HP_Y + this->coords_dimensions.y;
  text_player_hp.w = width_player_hp_invent;
  text_player_hp.h = height_player_hp_invent;

  SDL_Rect text_player_ap;
  text_player_ap.x = INVENTORY_COIN_AND_ATTACK_POWER_X + this->coords_dimensions.x;
  text_player_ap.y = INVENTORY_PLAYER_HP_Y + INVENTROY_TEXT_VERTICAL_GAP + this->coords_dimensions.y;
  text_player_ap.w = width_player_base_ap;
  text_player_ap.h = height_player_ap_invent;

  SDL_Rect text_player_money;
  text_player_money.x = INVENTORY_COIN_AND_ATTACK_POWER_X + this->coords_dimensions.x;
  text_player_money.y = INVENTORY_PLAYER_HP_Y + INVENTROY_TEXT_VERTICAL_GAP * 2 + this->coords_dimensions.y;
  text_player_money.w = width_player_money;
  text_player_money.h = height_player_money;

  SDL_Rect text_player_hp_number;
  text_player_hp_number.x = text_player_hp.x + text_player_hp.w;
  text_player_hp_number.y = text_player_hp.y;
  text_player_hp_number.h = height_player_hp_invent_number;
  text_player_hp_number.w = width_player_base_hp_number;

  SDL_Rect text_player_ap_number;
  text_player_ap_number.x = text_player_ap.x + text_player_ap.w;
  text_player_ap_number.y = text_player_ap.y;
  text_player_ap_number.h = height_player_ap_invent_number;
  text_player_ap_number.w = width_player_base_ap_number;

  SDL_Rect text_player_money_number;
  text_player_money_number.x = text_player_money.x + text_player_money.w;
  text_player_money_number.y = text_player_money.y;
  text_player_money_number.h = height_player_money_number;
  text_player_money_number.w = width_player_money_number;


  SDL_Rect text_declaration;
  text_declaration.x = this->coords_dimensions.x + INVENTORY_TEXT_DECLARATION_X;
  text_declaration.y = this->coords_dimensions.y + INVENTORY_TEXT_DECLARATION_Y;
  text_declaration.h = height_inventory_declaration;
  text_declaration.w = width_inventory_declaration;



  

  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::INVENTORY_TEXT_FOR_HP], nullptr, &text_player_hp);
  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::INVENTORY_TEXT_FOR_ATTACK], nullptr, &text_player_ap);
  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::INVENTORY_TEXT_FOR_MONEY], nullptr, &text_player_money);

  SDL_RenderCopy(main_tools.getMainRenderer(), texture_for_player_hp, nullptr, &text_player_hp_number);
  SDL_RenderCopy(main_tools.getMainRenderer(), texture_for_player_ap, nullptr, &text_player_ap_number);
  SDL_RenderCopy(main_tools.getMainRenderer(), texture_for_player_money, nullptr, &text_player_money_number);

  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::INVENTORY_TEXT_FOR_INVENTORY_DECLARATION], nullptr, &text_declaration);






}

std::tuple<Grid , Grid, Grid> getDimensionsOfItemAndTextureKey(Item* item_to_identify)
{
  if(auto placeholder = dynamic_cast<Mushroom*>(item_to_identify))
  {
    return {Grid::MUSHROOM, Grid::MUSHROOM_W, Grid::MUSHROOM_H};
  }

  if(auto placeholder = dynamic_cast<Potion*>(item_to_identify))
  {
    return {Grid::HEALTH_POT, Grid::HEALTH_POT_W, Grid::HEALTH_POT_W};
  }

  if(auto placeholder = dynamic_cast<GoldSapphireRing*>(item_to_identify))
  {
    return {Grid::RING_SAPPHIRE_GOLD , Grid::RING_SAPPHIRE_GOLD_BOTH, Grid::RING_SAPPHIRE_GOLD_BOTH};
  }

  if(auto placeholder = dynamic_cast<SapphireRing*>(item_to_identify))
  {
    return {Grid::RING_SAPPHIRE , Grid::RING_SAPPHIRE_GOLD_BOTH, Grid::RING_SAPPHIRE_GOLD_BOTH};
  }

  if(auto placeholder = dynamic_cast<RubyRing*>(item_to_identify))
  {
    return {Grid::RING_RUBY , Grid::RING_SAPPHIRE_GOLD_BOTH, Grid::RING_SAPPHIRE_GOLD_BOTH};
  }

  if(auto placeholder = dynamic_cast<StoneSword*>(item_to_identify))
  {
    return {Grid::STONE_SWORD, Grid::SWORDS_ALL, Grid::SWORDS_ALL};
  }

  if(auto placeholder = dynamic_cast<GoldSword*>(item_to_identify))
  {
    return {Grid::GOLD_SWORD, Grid::SWORDS_ALL, Grid::SWORDS_ALL};
  }

  if(auto placeholder = dynamic_cast<BigGoldSword*>(item_to_identify))
  {
    return {Grid::BIG_GOLD_SWORD, Grid::SWORDS_ALL, Grid::SWORDS_ALL};
  }

  if(auto placeholder = dynamic_cast<Trinket*>(item_to_identify))
  {
    if(placeholder->getType() == TrinketType::GOLDRUBY)
    {
      return {Grid::TRINKET_RUBY_GOLD, Grid::TRINKETS_BOTH, Grid::TRINKETS_BOTH};
    }
    else if(placeholder->getType() == TrinketType::RUBY)
    {
      return {Grid::TRINKET_RUBY, Grid::TRINKETS_BOTH, Grid::TRINKETS_BOTH};
    }
    else if(placeholder->getType() == TrinketType::SAPPHIRE)
    {
      return {Grid::TRINKET_SAPPHIRE, Grid::TRINKETS_BOTH, Grid::TRINKETS_BOTH};
    }
  }

  return {};
}

Item* identifyItem(Item* item_to_identify)
{
  if(auto placeholder = dynamic_cast<Mushroom*>(item_to_identify))
  {
    return placeholder;
  }

  if(auto placeholder = dynamic_cast<Potion*>(item_to_identify))
  {
    return placeholder;
  }

  if(auto placeholder = dynamic_cast<Ring*>(item_to_identify))
  {
    return placeholder;
  }

  if(auto placeholder = dynamic_cast<Sword*>(item_to_identify))
  {
    return placeholder;
  }

  if(auto placeholder = dynamic_cast<Trinket*>(item_to_identify))
  {
    return placeholder;
  }

  return nullptr;
}

void Inventory::checkBoundInventorySlots(Soldier* player, int x_mouse, int y_mouse) noexcept
{

  //std::cout << "Click at: " << x_mouse << ", " << y_mouse << std::endl;

  int inside_grid_x = x_mouse - (items_inventory_x + this->coords_dimensions.x);
  int inside_grid_y = y_mouse - (items_inventory_y + this->coords_dimensions.y);

  if(inside_grid_x >= 0 && inside_grid_y >= 0 
  && inside_grid_x < columns * (cell_both_dimensions + horizontal_gap)
  && inside_grid_y < rows * (cell_both_dimensions + vertical_gap))
  {
    int current_col_location = inside_grid_x / (cell_both_dimensions + horizontal_gap);
    int current_row_location = inside_grid_y / (cell_both_dimensions + vertical_gap);

    int cell_start_x = (items_inventory_x + this->coords_dimensions.x) + current_col_location * (cell_both_dimensions + horizontal_gap);
    int cell_start_y = (items_inventory_y + this->coords_dimensions.y) + current_row_location * (cell_both_dimensions + vertical_gap);

    if(x_mouse < cell_start_x + cell_both_dimensions && y_mouse < cell_start_y + cell_both_dimensions)
    {
      Button& clicked_button = this->buttons_[current_row_location][current_col_location];
      if(clicked_button.getItem() != nullptr)
      {
        Item* placeholder = identifyItem(clicked_button.getItem());

        std::cout << player->getMoney() << std::endl;
        if(player->isInShop()) { placeholder->sell(player); clicked_button.setItem(nullptr); return;}
        


        placeholder->use(player);
        if((!dynamic_cast<Sword*>(placeholder) && !dynamic_cast<Ring*>(placeholder)) && !dynamic_cast<Trinket*>(placeholder)
        || placeholder == player->getArmor()->getFirstRing() || placeholder == player->getArmor()->getFirstTrinket() || placeholder == player->getArmor()->getSecondTrinket()
        || placeholder == player->getArmor()->getSecondRing() || placeholder == player->getArmor()->getSword())
        {
          clicked_button.setItem(nullptr);
        }
      }
      
      // now logic for USE
      //std::cout << current_row_location << "   " << current_col_location << std::endl;
    }
  }


  for(int index = 0; index < static_cast<int>(Ranges::AMOUNT_OF_ARMOR); index++)
  {
    Button& current_button = this->getArmorFromInventory()[static_cast<ArmorSlot>(index)];

    if(current_button.getItem() != nullptr)
    {
      if(isMouseInsideArmoryCheck(x_mouse, y_mouse, current_button.getX(),
      current_button.getY(), current_button.getW(), current_button.getH()))
      {
        current_button.getItem()->use(player);
      }
    }
  }
}

bool isMouseInsideArmoryCheck(int x_mouse, int y_mouse, int x, int y, int w, int h)
{
  return (x_mouse >= x && x_mouse <= x + w && y_mouse <= y + h && y_mouse >= y);
}

Inventory::Inventory(Tools* main_tools)
{

  SDL_Rect new_rect;
  int height_of_inventory = 0;
  int width_of_inventory = 0;

  SDL_QueryTexture(textures_for_UI[UI::INVENTORY], nullptr, nullptr, &width_of_inventory, &height_of_inventory);

  new_rect.w = width_of_inventory * SCALING_FACTOR_THREE;
  new_rect.h = height_of_inventory * SCALING_FACTOR_THREE;
  new_rect.x = (main_tools->getScreenWidth() / 2) - (new_rect.w / 2);
  new_rect.y = (main_tools->getScreenHeight() / 2) - (new_rect.h / 2);

  this->coords_dimensions = new_rect;


  initButtons(main_tools);

  int y_offset = armor_y_axis_inventory;
  
  for(int index = 0; index < static_cast<int>(ArmorSlot::TRINKET_TWO) + 1; index++)
  {
    Button placeholder;
    placeholder.setX(armor_x_axis_inventory + this->coords_dimensions.x);
    placeholder.setY(y_offset + this->coords_dimensions.y);
    placeholder.setH(cell_both_dimensions);
    placeholder.setW(cell_both_dimensions);

    if(index == 0)
    {
      placeholder.setX(sword_x_axis_inventory + this->coords_dimensions.x);
      placeholder.setY(sword_y_axis_inventory + this->coords_dimensions.y);
    }

    this->players_armor_[static_cast<ArmorSlot>(index)] = placeholder;

    if(index > 0 )
    {
      y_offset += vertical_gap + cell_both_dimensions;
    }
  }

}

void Inventory::initButtons(Tools* main_tools) noexcept
{
  
  this->buttons_.resize(rows, std::vector<Button>(columns));
  // Buttons are copied ONLY here ! <-----------------------------------------------------------------



  int x_offset = items_inventory_x + this->coords_dimensions.x;
  int y_offset = items_inventory_y + this->coords_dimensions.y;

  for(int index = 0; index < rows; index++)
  {
    for(int inner = 0; inner < columns; inner++)
    {
      Button& current_button = this->buttons_[index][inner];

      current_button.setX(x_offset);
      current_button.setY(y_offset);
      current_button.setH(cell_both_dimensions);
      current_button.setW(cell_both_dimensions);

      x_offset += horizontal_gap + cell_both_dimensions;

     
    }

    x_offset = this->coords_dimensions.x + items_inventory_x;
    y_offset += vertical_gap + cell_both_dimensions;

  }
}

void Inventory::addItem(Item* new_item)
{
  this->current_items_.push_back(new_item);

  for(int index = 0; index < this->getButtons().size(); index++)
  {
    for(int inner = 0; inner < this->getButtons()[index].size(); inner++)
    {
      if(this->getButtons()[index][inner].getItem() == nullptr)
      {
        this->getButtons()[index][inner].setItem(new_item);
        return;
      }
    }
  }

}