#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "character.hpp"

class Account
{
  private:
    std::string username_;
    size_t account_id_;

    int current_character_id_;
    std::vector<Character*> characters_;

  public:
    // Constructor Destructor Copy Constructor
    Account() = default;
    Account(const std::string username, size_t account_id, const std::vector<Character*> characters);
    Account(const Account& copy ) = delete;
    ~Account() = default; // <-- free the runtime chars and save the game in the database << !

    //Getters
    std::string getUsername() const noexcept { return this->username_; }
    size_t getAccountID() const noexcept { return this->account_id_; }
    int getCurrentCharacterID() const noexcept { return this->current_character_id_; }
    Character* getCurrentCharacter() noexcept { return this->characters_[current_character_id_];}
    std::vector<Character*> getCharacters() const noexcept { return this->characters_; }


    //Setters
    void setUsername(const std::string& username) noexcept { this->username_ = username; }
    void setAccountId(size_t account_id) noexcept { this->account_id_ = account_id; }
    void setCurrentCharacterId(int current_character_id) noexcept { this->current_character_id_ = current_character_id;}
    void setCharacters(std::vector<Character*>& vector_of_chars) noexcept { this->characters_ = vector_of_chars; }

    //Functions


};



#endif


