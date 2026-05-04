#ifndef TEXT_FIELD_HPP
#define TEXT_FIELD_HPP

#include "elementUI.hpp"

class TextField : virtual public ElementUI
{
  private:
    std::string text_;
    size_t max_length_;
    bool active_;
    bool text_changed_;
    
    
  public:

    // Constructor Desctructor Copy Constructor
    TextField() = default;
    TextField(std::pair<int, int> coords, std::pair<int,int> offsets, int scaling_factor);
    TextField(const TextField& copy) = delete;
    ~TextField() = default;

    // Getters
    std::string getTextConst() const noexcept { return this->text_; }
    std::string& getTextModifiable() noexcept { return this->text_; }
    bool getActive() const noexcept { return this->active_; }
    bool getTextChanged() const noexcept { return this->text_changed_; }
    size_t getMaxLength() const noexcept { return this->max_length_; }

    // Setters
    void setText(std::string& new_test) noexcept { this->text_ = new_test; }
    void setActive(bool new_active) noexcept { this->active_ = new_active; }
    void setTextChanged(bool new_active) noexcept { this->text_changed_ = new_active; }
    void setMaxLength(size_t new_max_length) noexcept { this->max_length_ = new_max_length; }

    // Functions
    void render(Game& game) noexcept override;
    void update(Game& game) noexcept override;
    void handleBackspace() noexcept;
    void handleNewLetter(char character) noexcept;

    // Virtual TextField specific functions
    virtual void rebuildText(Game& game) noexcept;
};


#endif