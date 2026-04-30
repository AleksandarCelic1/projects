#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(Game& game) : State(game.getRenderer())
{
  this->validator_ = new LoginValidator();
  this->initializeUIOffsets(game);
  
  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();

  // Scale
  this->ui_elements_[LoginUI::LOGIN_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::LOGIN_BACKGROUND), game.getScalingFactor());

  // Assign Correct (X,Y)
  this->panel_ = new LoginPanel(this->getOffsetMap(), game.getTextureManager()->getUITexture(UI::LOGIN_PANEL), game.getScalingFactor());
  panel_->setX(this->centerX(0, screen_width, panel_->getW()));
  panel_->setY(this->centerY(0, screen_height, panel_->getH()));

}

void LoginState::initializeUIOffsets(Game& game) 
{
  int scaling_factor = game.getScalingFactor();

  /*
    Username Login 141 117
    Password Login 141 170
    Username Registration 343 117
    Password Registration 343 170
    Password Confirmation Registration 343 223
  */

  std::unordered_map<Offsets, std::pair<int, int>>& map = this->getOffsetMap();

  map.insert({Offsets::LOGIN_USERNAME, { 141 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::LOGIN_PASSWORD, { 141 * scaling_factor, 170 * scaling_factor }});
  map.insert({Offsets::REGISTRATION_USERNAME, { 343 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::REGISTRATION_PASSWORD, { 343 * scaling_factor, 170 * scaling_factor }}); 
  map.insert({Offsets::REGISTRATION_PASSWORD_CONFIRMATION, { 343 * scaling_factor, 223 * scaling_factor }});


}


void LoginState::render(Game& game)
{
  this->renderBackground(game);
  this->getPanel()->render(game);
}

void LoginState::update(Game& game) 
{
  this->updatePanelTimePassed(game);
}

void LoginState::renderBackground(Game& game) noexcept
{
  ElementUI* placeholder = this->ui_elements_[LoginUI::LOGIN_BACKGROUND];
  placeholder->render(game); // this change should work <!>
  //SDL_Rect copy = placeholder->getRect();
  //SDL_RenderCopy(game.getRenderer(), placeholder->getTexture(), nullptr, &copy);

  // nullprt for SRC rect means -> that we take a specific part of the texture and then render 
  // it with DST rect and DST holds x,y,w,h if we do nullprt for SRC we just use the entire Texture
}

void LoginState::updatePanelTimePassed(Game& game) noexcept
{
  LoginPanel* placeholder = this->getPanel();
  placeholder->setTimePassed(placeholder->getTimePassed() + game.getDeltaTime());

}


void LoginState::dispatchKeyboardInput(Game& game) 
{
  const SDL_Keycode& keycode = game.getDispatcher()->getKeyCode();
  bool shift_pressed = game.getDispatcher()->getShiftHeld();
  bool control_pressed = game.getDispatcher()->getControlHeld();


  std::pair<SDL_Keycode, bool> key = {keycode, shift_pressed};
  auto iterator = SDL_KEYS.find(key);
  if(iterator == SDL_KEYS.end())
  {
    return;
  }

  char new_char = iterator->second;
  TextField* placeholder = this->getPanel()->getActiveField();
  if(placeholder != nullptr)
  {
    keycode == SDLK_BACKSPACE ? placeholder->handleBackspace() : placeholder->handleNewLetter(new_char);
  }
  
}

void LoginState::dispatchMouseInput(Game& game)
{
  Uint8 mouse_button = game.getDispatcher()->getMouseButton();
  Dispatcher* dispatcher = game.getDispatcher();

  /*
    Now we can introduce a simple for loop/ big switch to detect clicks,
    which would be fine in LoginState, since there arent many widgets/clickable items,
    but in the PlayingState there should already be some sort of better dispatch for mouse input
    there are some viable gamedev techniques found -> grid spatial partitioning, quadtree, layers/z-order hit testing
  */

  if(mouse_button == SDL_BUTTON_LEFT)
  {
    // handle left click
    LoginPanel* panel = this->getPanel();
    /*if(panel->detectMouseClick())
    {

    }

    if(panel->getUsernameLogin()->detectMouseClick())
    {

    }

    if(panel->getPasswordLogin()->detectMouseClick())
    {

    }

    if(panel->getUsernameRegistration()->detectMouseClick())
    {

    }

    if(panel->getPasswordRegistration()->detectMouseClick())
    {

    }


    if(panel->getPasswordConfirmation()->detectMouseClick())
    {

    }*/
    
  }
  else if (mouse_button == SDL_BUTTON_RIGHT)
  {
    // handle right click
  }
  else
  {
    std::cout << "[FAIL] -> [dispatchMouseInput] -> what did user press ?!" << std::endl;
  }
}




