#ifndef CHARACTER_OVERVIEW_HPP
#define CHARACTER_OVERVIEW_HPP

#include "state.hpp"
#include "character.hpp"
#include "elementUI.hpp"
#include "character_overview_panel.hpp"

#include "../../namespaces_/namespaces.hpp"

class CharacterOverviewState : virtual public State
{
  private:
    /* Maybe we can add a void* to elementUI* that can be used to see if it already is a placeholder for character or something else <!> */
    CharacterOverviewPanel* panel_;
    std::unordered_map<CharacterOverviewUI, ElementUI*> ui_elements_;

  public:
    // Constructor Desctructor Copy Constructor
    CharacterOverviewState() = default;
    CharacterOverviewState(Game& game);
    CharacterOverviewState(const CharacterOverviewState& copy) = delete;
    ~CharacterOverviewState();

    // Getters
    CharacterOverviewPanel* getPanel() noexcept;
    std::unordered_map<CharacterOverviewUI, ElementUI*>& getUIElements() noexcept { return this->ui_elements_; }

    // Setters
    void setPanel(CharacterOverviewPanel* new_panel) noexcept { this->panel_ = new_panel; }

    // Methods 
    void addElement(CharacterOverviewUI key, ElementUI* element) noexcept;


    // Virtual Methods
    void dispatchKeyboardInput(Game& game) override;
    void dispatchMouseInput(Game& game) override;
    void render(Game& game) override;
    void update(Game& game) override;
    void initializeUIOffsets(Game& game) override;
    void handleEnter(Game& game) override;

    // Mini Render Functions
    void renderBackground(Game& game) noexcept;


};

#endif