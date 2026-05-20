#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include "account.hpp"

class DataBaseManager
{
  private:
    PGconn* connection_;
    char* connection_parameters_;
    

  public:
    // Constructor Copy Constructor Desctructor 
    DataBaseManager();
    DataBaseManager(const DataBaseManager& copy) = delete;
    ~DataBaseManager();

    // Getters
    PGconn* getPGconn() const noexcept { return this->connection_; }
    char* getConnectionParameters() const noexcept { return this->connection_parameters_; }

    // Setters
    void setPGconn(PGconn* new_connection) noexcept { this->connection_ = new_connection; }
    void setConnectionParameters(char* new_params) noexcept { this->connection_parameters_ = new_params; }

    // Functions




};


#endif