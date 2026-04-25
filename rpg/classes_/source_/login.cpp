#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(Game& game) : State(game.getRenderer())
{
  this->validator_ = new LoginValidator();
  
  int screen_width = game.getWindowWidth();
  int screen_height = game.getWindowHeight();

  // Scale
  this->ui_elements_[LoginUI::LOGIN_BACKGROUND] = new ElementUI(game.getTextureManager()->getUITexture(UI::LOGIN_BACKGROUND), game.getScalingFactor());

  // Assign Correct (X,Y)
  this->panel_ = new LoginPanel(game.getTextureManager()->getUITexture(UI::LOGIN_PANEL), game.getScalingFactor());
  panel_->setX(this->centerX(0, screen_width, panel_->getW()));
  panel_->setY(this->centerY(0, screen_height, panel_->getH()));

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
  SDL_Rect copy = placeholder->getRect();
  SDL_RenderCopy(game.getRenderer(), placeholder->getTexture(), nullptr, &copy);

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

  // I need to somehow 

  if(mouse_button == SDL_BUTTON_LEFT)
  {
    // handle left click
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


