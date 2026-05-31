#include "../include_/login.hpp"
#include "../include_/game.hpp"

LoginState::LoginState(Game& game) : State(game.getRenderer(), game.getWindowWidth(), game.getWindowHeight())
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

  // QuadTree - Insert Chain -> Think about making a seperate functions for this <!>
  QuadTree* quad_tree = this->getQuadTree();
  quad_tree->insert(this->panel_->getUsernameLogin());
  quad_tree->insert(this->panel_->getPasswordLogin());
  quad_tree->insert(this->panel_->getUsernameRegistration());
  quad_tree->insert(this->panel_->getPasswordRegistration());
  quad_tree->insert(this->panel_->getPasswordConfirmation());
  

}

LoginState::~LoginState()
{
  MemoryFreeingUtils::clearPointer(this->validator_);
  MemoryFreeingUtils::clearPointer(this->panel_);
  MemoryFreeingUtils::clearMap(this->ui_elements_);
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
  map.insert({Offsets::REGISTRATION_USERNAME, { 344 * scaling_factor, 117 * scaling_factor }});
  map.insert({Offsets::REGISTRATION_PASSWORD, { 344 * scaling_factor, 170 * scaling_factor }}); 
  map.insert({Offsets::REGISTRATION_PASSWORD_CONFIRMATION, { 344 * scaling_factor, 223 * scaling_factor }});


}

void LoginState::render(Game& game)
{
  this->renderBackground(game);
  this->getPanel()->render(game);


  /* Debugging Render*/
  // this->getQuadTree()->debugOutline(game.getRenderer());
}

void LoginState::update(Game& game) 
{
  this->getPanel()->update(game);
}

void LoginState::renderBackground(Game& game) noexcept
{
  ElementUI* placeholder = this->ui_elements_[LoginUI::LOGIN_BACKGROUND];
  placeholder->render(game); 

  // nullprt for SRC rect means -> that we take a specific part of the texture and then render 
  // it with DST rect and DST holds x,y,w,h if we do nullprt for SRC we just use the entire Texture
}

void LoginState::dispatchKeyboardInput(Game& game) 
{
  std::queue<KeyboardInput*>& queue = game.getDispatcher()->getInputQueue();
  TextField* text = this->getPanel()->getActiveField();
  if(text == nullptr)
  {
    ParserUtility::flushQueue(queue);
    return;
  }

  KeyboardInput* new_input =  ParserUtility::getKeyboardInput(text, queue);
  if(new_input == nullptr)
  {
    return;
  }

  SDL_Keycode keycode = new_input->key_pressed_;
  bool shift_pressed = new_input->shift_held_;
  bool control_pressed = new_input->control_held_;

  std::pair<SDL_Keycode, bool> key = {keycode, shift_pressed};
  auto iterator = SDL_KEYS.find(key);
  if(iterator == SDL_KEYS.end())
  {
    std::cout << "[ERROR] -> [LoginState::dispatchKeyboardInput] -> key not found <!> " << std::endl;
    delete new_input;
    return;
  }

  char new_char = iterator->second;
  
  if(text != nullptr)
  {
    if(keycode == SDLK_RETURN)
    { 
      this->handleEnter(game);
    }
    else if(keycode == SDLK_BACKSPACE)
    {
      text->handleBackspace();
    }
  
    text->handleNewLetter(new_char);
  }



  delete new_input;
}

void LoginState::dispatchMouseInput(Game& game)
{
  Dispatcher* dispatcher = game.getDispatcher();
  Uint8 mouse_button = dispatcher->getMouseButton();
  int mouse_x = dispatcher->getMouseX();
  int mouse_y = dispatcher->getMouseY();


  if(mouse_button == SDL_BUTTON_LEFT)
  {
    LoginPanel* panel = this->getPanel();
    ElementUI* tmp = this->getQuadTree()->search(mouse_x, mouse_y);

    if(tmp == nullptr)
    {
      panel->setActiveField(nullptr);
      return;
    }

    TextField* txt_field = dynamic_cast<TextField*>(tmp);
    if(txt_field == nullptr)
    {
      panel->setActiveField(nullptr);
      std::cout << "[ERROR] -> [LoginState::dispatchMouseInput] -> dynamic_cast failed <!> " << std::endl;
      return;
    }

    panel->setActiveField(txt_field);
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

void LoginState::handleEnter(Game& game) 
{
  
  LoginValidator* validator = this->getValidator();
  TextField* text = this->panel_->getActiveField();

  TextField* username = this->panel_->getUsernameLogin();


  if(text == this->panel_->getUsernameLogin() 
  || text == this->panel_->getPasswordLogin())
  {
    if(validator->validate(game, text->getTextConst(), this->panel_->getPasswordLogin()->getTextConst()))
    {
      std::cout << "[Validator] -> returned valid input -> we can now try to query the database <!> " << std::endl;
      Account* loaded_acc = DataBaseManager::instance()->tryLogin
                            (this->panel_->getUsernameLogin()->getTextConst(), this->panel_->getPasswordLogin()->getTextConst());

      if(loaded_acc)
      {
        game.setCurrentAccountLoggedIn(loaded_acc);
        game.setGameState(GameState::CHARACTER_OVERVIEW);
      }
    }
  }
  
  if(validator->validateRegistration(game, panel_->getUsernameRegistration()->getTextConst(), 
  panel_->getPasswordRegistration()->getTextConst(), panel_->getPasswordConfirmation()->getTextConst()))
  {
    std::cout << "[Validator] -> returned valid input -> we can now try to query the database <!> " << std::endl;
    Account* registered_account = nullptr; // DataBaseManager::instance().tryRegister()
  }

}

