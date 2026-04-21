#ifndef TEXT_FIELD_HPP
#define TEXT_FIELD_HPP

#include "../../constants_/constants.hpp"
#include "../../enums_/enums.hpp"
#include "../../structs_/structs.hpp"

class TextField
{
  private:
    std::string text_;
    bool active_;
    size_t max_length_;

    int x_;
    int y_;

  public:

    // Constructor Desctructor Copy Constructor
    TextField() = default;
    TextField(const TextField& copy) = delete;
    ~TextField() = default;

    // Getters
    std::string getTextConst() const noexcept { return this->text_; }
    std::string& getTextModifiable() noexcept { return this->text_; }
    bool getActive() const noexcept { return this->active_; }
    size_t getMaxLength() const noexcept { return this->max_length_; }

    int getX() const noexcept { return this->x_; }
    int getY() const noexcept { return this->y_; }

    // Setters
    void setText(std::string& new_test) noexcept { this->text_ = new_test; }
    void setActive(bool new_active) noexcept { this->active_ = new_active; }
    void setMaxLength(size_t new_max_length) noexcept { this->max_length_ = new_max_length; }
    void setX(int new_x) noexcept { this->x_ = new_x; }
    void setY(int new_y) noexcept { this->y_ = new_y; }

    // Functions

    void handleBackspace() noexcept;
    void handleNewLetter(char character) noexcept;
};


#endif