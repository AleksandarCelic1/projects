#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "account.hpp"


class DataBaseManager
{
  private:
    PGconn* connection_;
    std::string connection_parameters_;
    std::unordered_map<QueryEnums, std::string> query_map_;
    static DataBaseManager* instance_;
    
    // Constructor
    DataBaseManager();
  public:
    // Copy Constructor Desctructor 
    DataBaseManager(const DataBaseManager& copy) = delete;
    ~DataBaseManager();

    // Getters
    PGconn* getPGconn() const noexcept { return this->connection_; }
    std::string getConnectionParameters() const noexcept { return this->connection_parameters_; }
    std::unordered_map<QueryEnums, std::string>& getQueryMap() noexcept { return this->query_map_; }

    // Setters
    void setPGconn(PGconn* new_connection) noexcept { this->connection_ = new_connection; }
    void setConnectionParameters(std::string new_params) noexcept { this->connection_parameters_ = new_params; }
    void setQueryMap(std::unordered_map<QueryEnums, std::string> new_map) noexcept { this->query_map_ = new_map; }

    // Class related functions
    void initializeConnectionParameters() noexcept;
    void initializeQueryMap() noexcept;

    // Database related functions
    bool tryLogin(std::string& username, std::string& password) noexcept;

    /* Refactor this function, currently load account handles whole login <!> */
    Account* loadAccount(std::string& username, std::string& password) noexcept;
    std::vector<Character*> loadCharacters(std::string& account_id) noexcept;

    // Static Functions
    static DataBaseManager* instance();
    static void destroy();

    // Queries <!> 
    std::pair<bool, std::string> queryAccount(std::string& username, std::string& password) noexcept;
    std::vector<std::string> queryCharacters(std::string& account_id) noexcept;

    /* Look more into this <!> */
    void queryStats(std::string& character_id) noexcept;
    void queryAttributes(std::string& character_id) noexcept;
    void queryArmory(std::string& character_id) noexcept;
    void queryInventory(std::string& character_id) noexcept;
    


};


#endif