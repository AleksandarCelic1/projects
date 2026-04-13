#ifndef INPUT_VALIDATOR_HPP
#define INPUT_VALIDATOR_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"

class Game;

class InputValidator
{
  private:

  public:
    // Constructor Copy Constructor Desctructor
    InputValidator() = default;
    InputValidator(const InputValidator& copy ) = delete;
    virtual ~InputValidator();


    // Functions 
    virtual void validate(Game& game, const std::string& username, const std::string& password) = 0;
};


#endif