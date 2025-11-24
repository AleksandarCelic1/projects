#include "shopkeeper.hpp"
#include "soldier.hpp"
#include "../celaUtility.hpp"

Shopkeeper::Shopkeeper() : MapObjects() 
{
  setAnimationState(AnimationState::SHOP_KEEPER_IDLE);
  coords_and_dimensions_.x = 0;
  coords_and_dimensions_.y = 0;

  this->items_to_sell_.push_back(new Potion());
  this->items_to_sell_.push_back(new Mushroom());
  this->items_to_sell_.push_back(new RubyRing());
  this->items_to_sell_.push_back(new SapphireRing());
  this->items_to_sell_.push_back(new GoldSword());
  this->items_to_sell_.push_back(new BigGoldSword());


}

void Shopkeeper::updateAnimation(float delta_time) 
{
  if(this->is_animating_frame_ == false) 
  {
    return;
  }

  this->animation_timer_ += delta_time;
  if(animation_timer_ >= frame_duration_)
  {
    animation_timer_ = 0.0f;
    current_frame_++;

    if(current_frame_ >= total_frames_)
    {
      if(this->animation_state_ == AnimationState::SHOP_KEEPER_IDLE)
      {
        setAnimationState(AnimationState::SHOP_KEEPER_IDLE);
        // Constant Moving Animation !
      }
      else 
      {
        current_frame_ = 0;
      }
    }
  }
}


void Shopkeeper::use(Tools& main_tools) noexcept 
{

  if(this->coords_and_dimensions_.x == 0 && this->coords_and_dimensions_.y == 0) { initDimensionsForRendering(&main_tools); }
  Inventory* players_items = main_tools.getGame()->getSoldier()->getInventory();
  Soldier* player = dynamic_cast<Soldier*>(main_tools.getGame()->getSoldier());


  SDL_Event current_event;
  bool programm_running = true;


  while(programm_running)
  {
    while(SDL_PollEvent(&current_event))
    {

      SDL_Keycode pressed = current_event.key.keysym.sym;
      if(current_event.type == SDL_KEYDOWN && current_event.key.repeat == 0)
      {
        if(pressed == SDLK_RETURN)
        {
          programm_running = false;
          player->setShopStatus(false);
        }
      }

      if (current_event.type == SDL_MOUSEBUTTONDOWN)
      {
        int mouse_x = current_event.button.x;
        int mouse_y = current_event.button.y;

        players_items->checkBoundInventorySlots(player, mouse_x, mouse_y);
        checkBoundsForBuy(player, mouse_x, mouse_y);   
      }
    }


    SDL_RenderCopy(main_tools.getMainRenderer(), main_tools.getIntroScreenInterface(), nullptr, nullptr);
    SDL_SetRenderDrawColor(main_tools.getMainRenderer(), 0, 0, 0, 128); 
    SDL_Rect darken_rect = {0, 0, main_tools.getScreenWidth(), main_tools.getScreenHeight()};
    SDL_RenderFillRect(main_tools.getMainRenderer(), &darken_rect);

    SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[UI::SHOP], nullptr, &this->coords_and_dimensions_);


    printShopkeepersItemsToSell(main_tools);
    players_items->printItems(main_tools, players_items->getRect().x + SHOP_INVENTORY_ITEMS_X_DIFFERENCE,
    players_items->getRect().y - SHOP_INVENTORY_ITEMS_Y_DIFFERENCE);

    SDL_RenderPresent(main_tools.getMainRenderer());
  }
}

void Shopkeeper::printShopkeepersItemsToSell(Tools& main_tools) noexcept
{
  int x_offset = items_to_sell_shop_x;
  int y_offset = items_to_sell_shop_y;

  for(int index = 0; index < this->buttons_.size(); index++)
  {
    for(int inner = 0; inner < this->buttons_[index].size(); inner++)
    {
      if(this->buttons_[index][inner].getItem() != nullptr)
      {
        Button& current_button = this->buttons_[index][inner];

        auto [ texture, width, height ] = getDimensionsOfItemAndTextureKey(this->buttons_[index][inner].getItem());

        SDL_Rect placeholder;
        placeholder.w = static_cast<int>(width) * SCALING_FACTOR_TWO;
        placeholder.h = static_cast<int>(height) * SCALING_FACTOR_TWO;
        placeholder.x = this->coords_and_dimensions_.x + x_offset + (cell_both_dimensions / 2) - (placeholder.w / 2);
        placeholder.y = this->coords_and_dimensions_.y + y_offset + (cell_both_dimensions / 2) - (placeholder.h / 2);

        UI price;
        price = itemIdentifierForPrices(this->buttons_[index][inner].getItem());
        if(price == UI::INVALID_TEXT)
        {
          continue;
        }

        int width_for_price = current_button.getX() + (current_button.getW() / 2);
        renderPrices(main_tools, price, width_for_price , current_button.getH() + current_button.getY());


        

        

        SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_map[texture], nullptr, &placeholder);        
      }

      x_offset += horizontal_gap_shop_items_to_sell + cell_both_dimensions;
    }

    x_offset = items_to_sell_shop_x;
    y_offset += vertical_gap_shop_items_to_sell + cell_both_dimensions;
    
  }
}

void Shopkeeper::renderPrices(Tools& main_tools, UI price_of_item, int x_cord, int y_cord) noexcept
{
  SDL_Rect to_render;

  
  int width = 0;
  int height = 0;

  SDL_QueryTexture(textures_for_UI[price_of_item], nullptr, nullptr, &width, &height);
  to_render.x = x_cord - width / 2;
  to_render.y = y_cord + height / 2;

  to_render.w = width;
  to_render.h = height;

  SDL_Rect coin;
  coin.x = to_render.x + to_render.w;
  coin.y = to_render.y - COIN_Y_AT_PRICES;
  coin.h = static_cast<int>(Grid::COIN_BOTH) * SCALING_FACTOR_TWO;
  coin.w = static_cast<int>(Grid::COIN_BOTH) * SCALING_FACTOR_TWO;





  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_UI[price_of_item], nullptr, &to_render);
  SDL_RenderCopy(main_tools.getMainRenderer(), textures_for_map[Grid::COIN], nullptr, &coin);
}

UI itemIdentifierForPrices(Item* item_to_identify)
{
  if(auto placeholder = dynamic_cast<Mushroom*>(item_to_identify))
  {
    return UI::SHOP_PRICE_MUSHROOM;
  }

  if(auto placeholder = dynamic_cast<Potion*>(item_to_identify))
  {
    return UI::SHOP_PRICE_POT;
  }

  if(auto placeholder = dynamic_cast<RubyRing*>(item_to_identify))
  {
    return UI::SHOP_PRICE_RUBY_RING;
  }

  if(auto placeholder = dynamic_cast<SapphireRing*>(item_to_identify))
  {
    return UI::SHOP_PRICE_SAPPHIRE_RING;
  }

  if(auto placeholder = dynamic_cast<GoldSword*>(item_to_identify))
  {
    return UI::SHOP_PRICE_GOLD_SWORD;
  }

  if(auto placeholder = dynamic_cast<BigGoldSword*>(item_to_identify))
  {
    return UI::SHOP_PRICE_BIG_GOLD_SWORD;
  }


  return UI::INVALID_TEXT;
}

void Shopkeeper::initDimensionsForRendering(Tools* main_tools) noexcept
{
  SDL_Rect new_rect;
  int height_of_inventory = 0;
  int width_of_inventory = 0;

  SDL_QueryTexture(textures_for_UI[UI::SHOP], nullptr, nullptr, &width_of_inventory, &height_of_inventory);

  new_rect.w = width_of_inventory * SCALING_FACTOR_THREE;
  new_rect.h = height_of_inventory * SCALING_FACTOR_THREE;
  new_rect.x = (main_tools->getScreenWidth() / 2) - (new_rect.w / 2);
  new_rect.y = (main_tools->getScreenHeight() / 2) - (new_rect.h / 2);

  this->coords_and_dimensions_ = new_rect;

  this->buttons_.resize(rows_shop, std::vector<Button>(columns_shop));

  int x_offset = items_to_sell_shop_x + this->coords_and_dimensions_.x;
  int y_offset = items_to_sell_shop_y + this->coords_and_dimensions_.y;

  for(int index = 0; index < rows_shop; index++)
  {
    for(int inner = 0; inner < columns_shop; inner++)
    {
      Button& current_button = this->buttons_[index][inner];

      current_button.setX(x_offset);
      current_button.setY(y_offset);
      current_button.setH(cell_both_dimensions);
      current_button.setW(cell_both_dimensions);

      x_offset += horizontal_gap_shop_items_to_sell + cell_both_dimensions;
     
    }
    x_offset = this->coords_and_dimensions_.x + items_to_sell_shop_x;
    y_offset += vertical_gap_shop_items_to_sell + cell_both_dimensions;
  }

  int ind = 0;
  for(int index = 0; index < this->buttons_.size(); index++)
  {
    for(int inner = 0; inner < this->buttons_[index].size(); inner++)
    {
      if(this->buttons_[index][inner].getItem() == nullptr)
      {
        this->buttons_[index][inner].setItem(items_to_sell_[ind]);
        ind++;
      }
    }
  }
}

void Shopkeeper::checkBoundsForBuy(Character* player, int mouse_x, int mouse_y)
{
  for(int index = 0; index < this->buttons_.size(); index++)
  {
    for(int inner = 0; inner < this->buttons_[index].size(); inner++)
    {
      Button& current_button = this->buttons_[index][inner];

      if(current_button.getItem() != nullptr)
      {
        if(isMouseInsideArmoryCheck(mouse_x, mouse_y, current_button.getX(),
        current_button.getY(), current_button.getW(), current_button.getH()))
        {
          if(current_button.getItem()->buy(player))
          { 
            player->getInventory()->addItem(current_button.getItem());
            current_button.setItem(nullptr); 
          }
          else 
          { 
            return;
          }
          
        }
      }
    }
  }
}









