#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "account.hpp"


class DataBaseManager
{
  private:
    PGconn* connection_;
    std::string connection_parameters_;
    std::unordered_map<QueryEnums, std::string> query_map_;
    
    
  public:
    // Contructor Copy Constructor Desctructor 
    DataBaseManager();
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
    Account* tryLogin(const std::string username, const std::string password) noexcept;
    Account* tryRegister(const std::string username, const std::string password) noexcept;
    std::string loadAccount(const std::string username, const std::string password) noexcept;
    std::vector<Character*> loadCharacters(const std::string account_id) noexcept;


    // Queries <!> 
    std::string                     queryAccount(const std::string username, const std::string password)      noexcept;
    std::vector<loadedCharValues>   queryCharacters(const std::string account_id)                             noexcept;
    Stats*                          queryStats(const std::string character_id)                                noexcept;
    Attributes*                     queryAttributes(const std::string character_id)                           noexcept;
    Armory*                         queryArmory(const std::string character_id)                               noexcept;
    Inventory*                      queryInventory(const std::string character_id)                            noexcept;
    std::vector<Container*>         queryContainers(const std::string inventory_id)                           noexcept;
    std::vector<std::vector<Item*>> queryItems(const std::string container_id)                                noexcept;
    bool                            queryRegistration(const std::string username, const std::string password) noexcept;


    // Helpers
    bool validatePGresult(PGresult* result) noexcept;
    bool validatePGcommand(PGresult* result) noexcept;
    


};


extern DataBaseManager* db_manager;


#endif