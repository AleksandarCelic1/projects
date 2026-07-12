#ifndef CHARACTER_OVERVIEW_PANEL_HPP
#define CHARACTER_OVERVIEW_PANEL_HPP

#include "../../include_/panel.hpp"
#include "../../include_/character.hpp"


class CharacterOverviewPanel : public Panel
{
  private:
    std::unordered_map<ElementUI*, Character*> characters_;
    ElementUI* currently_selected_;
    SDL_Rect char_overview_rect_;

  public:
    CharacterOverviewPanel() = default;
    CharacterOverviewPanel(std::unordered_map<Offsets, std::pair<int,int>>& map, const TextureAsset& asset, int scaling_factor);
    CharacterOverviewPanel(const CharacterOverviewPanel& copy) = delete;
    ~CharacterOverviewPanel();


    // Getters
    std::unordered_map<ElementUI*, Character*>& getCharacterMappings() noexcept { return this->characters_; }
    Character* getCharacter(ElementUI* key) noexcept;
    ElementUI* getCurrentlySelectedElement() noexcept { return this->currently_selected_; }
    SDL_Rect& getCharOverviewRect() noexcept { return this->char_overview_rect_; }

    // Setters
    void setCharacterMappings(std::unordered_map<ElementUI*, Character*> new_mappings) noexcept { this->characters_ = new_mappings; }
    void setCharOverviewRect(SDL_Rect new_rect) noexcept { this->char_overview_rect_ = new_rect; }


    // Methods
    void addCharacter(ElementUI* key, Character* new_char) noexcept;
    void setCurrentlySelectedElement(ElementUI* new_curr_selec) noexcept;

    // Virtual Methods
    void render(Game& game) noexcept override;
    void update(Game& game) noexcept override;

    // Mini render functions
    void renderCharacterOverview(Game& game) noexcept;
    void renderPlus(Game& game, ElementUI* element) noexcept;


};

#endif