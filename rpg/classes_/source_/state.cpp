#include "../include_/state.hpp"
#include "../include_/game.hpp"

State::State(SDL_Renderer* main_renderer, int window_width, int window_height)
{
  SDL_Rect placeholder;
  placeholder.x = 0;
  placeholder.y = 0;
  placeholder.w = window_width;
  placeholder.h = window_height;

  this->quad_tree_ = new QuadTree(placeholder);
  this->renderer_ = main_renderer;

}

State::~State()
{
  MemoryFreeingUtils::clearPointer(this->quad_tree_);
}

int State::centerX(int x, int screen_width, int object_width)
{
  return (x + ((screen_width / 2) - (object_width / 2)));
}

int State::centerY(int y, int screen_height, int object_height)
{
  return (y + ((screen_height / 2) - (object_height / 2)));
}

std::optional<std::pair<SDL_Keycode, char>> State::takeKeyboardInput(Game& game, TextField* text)
{
  std::queue<KeyboardInput*>& queue = game.getDispatcher()->getInputQueue();
  if(text == nullptr)
  {
    ParserUtility::flushQueue(queue);
    return std::nullopt;
  }

  KeyboardInput* new_input =  ParserUtility::getKeyboardInput(text, queue);
  if(new_input == nullptr)
  {
    return std::nullopt;
  }

  SDL_Keycode keycode = new_input->key_pressed_;
  bool shift_pressed = new_input->shift_held_;
  bool control_pressed = new_input->control_held_;

  delete new_input;

  std::pair<SDL_Keycode, bool> key = {keycode, shift_pressed};
  auto iterator = SDL_KEYS.find(key);
  if(iterator == SDL_KEYS.end())
  {
    std::cout << "[ERROR] -> [LoginState::dispatchKeyboardInput] -> key not found <!> " << std::endl;
    return std::nullopt;
  }


  /* 
    Returning just {} means returning a empty optional data type meaning 
    its the same as nullopt, thast why we return explicitly std::pair
  */
  char new_char = iterator->second;
  return std::pair{keycode, new_char};
}
