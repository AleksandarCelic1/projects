#include "../include_/account.hpp"


// This custom overloaded CTOR should be used when we load the account from the database << !
Account::Account(const std::string username, size_t account_id, const std::vector<Character*> characters)
    : username_(username), account_id_(account_id), characters_(characters) {}

