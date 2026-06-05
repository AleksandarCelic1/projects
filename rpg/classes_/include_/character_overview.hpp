#ifndef CHARACTER_OVERVIEW_HPP
#define CHARACTER_OVERVIEW_HPP

#include "state.hpp"
#include "character.hpp"
#include "elementUI.hpp"

#include "../../namespaces_/namespaces.hpp"

class CharacterOverviewState : virtual public State
{
  private:
    /* Maybe we can add a void* to elementUI* that can be used to see if it already is a placeholder for character or something else <!> */
    std::unordered_map<ElementUI*, Character*> characters_;
    std::unordered_map<CharacterOverviewUI, ElementUI*> ui_elements_;

  public:
    // Constructor Desctructor Copy Constructor
    CharacterOverviewState() = default;
    CharacterOverviewState(Game& game);
    CharacterOverviewState(const CharacterOverviewState& copy) = delete;
    ~CharacterOverviewState();

    // Getters
    Character* getCharacter(ElementUI* key) noexcept;
    std::unordered_map<CharacterOverviewUI, ElementUI*>& getUIElements() noexcept { return this->ui_elements_; }

    // Setters
    void addCharacter(ElementUI* key, Character* new_char) noexcept { this->characters_.insert({key, new_char}); }
    void addElement(CharacterOverviewUI key, ElementUI* element) noexcept;

    // Functions 


};

#endif