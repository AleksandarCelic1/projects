#include "../include_/database_manager.hpp"
#include "../../namespaces_/namespaces.hpp"


DataBaseManager::DataBaseManager()
{
  /*
    #include <libpq-fe.h>

    this is a library that lets us connect to the Database.
    In our case we will be using PostgreSQL and will need to 
    connect to an already running server

    Some sort of connection has to be established in the CTOR of DatabaseManager,
    and of course we would disconnect in DTOR.

    The appropriate syntax will be used according to the libpq-fe.h, e.g. PGconn 
    will be used as a connection and there will of course be "log in " credentials for 
    connecting ourselves to the Database.

    "PGresult* result = PQexec(conn, "SELECT id, name FROM users;")"
    |-> this is a example of how to query our database, and we'd have to check each time
    if its successful if not we'd have to consider a robust way to handle this.

  */
  this->initializeConnectionParameters();
  this->connection_ = PQconnectdb(this->connection_parameters_.c_str());
  this->connection_parameters_.clear();

  if(PQstatus(this->connection_) != CONNECTION_OK)
  {
    std::cout << "[ERROR] -> [DataBaseManager::DataBaseManager()] -> connection to the database failed <!> " << std::endl;
    PQfinish(this->connection_);
    return;
  }
}

DataBaseManager::~DataBaseManager()
{
  /*
    Disconnect yourself from the Database <!> 
  */

  PQfinish(this->connection_);
}

void DataBaseManager::initializeQueryMap() noexcept
{
  /*
    Fill the map with key, value pairs as follows
    map.insert(QUERY_SOME_KEY, "SELECT user_id FROM users;")

    So when a query happens we just do the appopriate query to the DB
  */

  this->query_map_.insert({QueryEnums::QUERY_LOGIN, "SELECT account_id, username_, password_ FROM Accounts WHERE username_ = $1 AND password_ = $2 "});
}

void DataBaseManager::initializeConnectionParameters() noexcept
{
  std::string result;
  std::vector<std::string> credentials;

  /*
    We have to parse the env folder <!> 
  */

  std::ifstream file("../../env_/database_credentials.env");
  if(!file.is_open())
  {
    std::cout << "[ERROR] -> [DataBaseManager::initializeConnectionParameters] -> File couldn't be opened <!> " << std::endl;
    return;
  }

  std::string line;

  while(std::getline(file, line))
  {
    if(line.empty())
    {
      continue;
    }

    size_t index = line.find('=');
    if(index == std::string::npos)
    {
      continue;
    }

    result += line;
    result += " ";

  }


  this->connection_parameters_ = result;

  /* Debug Log */
  std::cout << "[DEBUG] -> [DataBaseManager::initializeConnectionParameters] -> " << this->connection_parameters_ << std::endl;
}

DataBaseManager* DataBaseManager::instance()
{
  if(instance_ == nullptr)
  {
    instance_ = new DataBaseManager();
  }

  return instance_;
}

void DataBaseManager::destroy()
{
  if(instance_ != nullptr)
  {
    delete instance_;
    instance_ = nullptr;
  }
  
}

Account* DataBaseManager::loadAccount(std::string& username, std::string& password) noexcept
{
  auto [valid, account_id] = this->queryAccount(username, password);
  if(valid == false)
  {
    return nullptr;
  }

  /*
    We need to query for characters related to each account, and of course to load a single char we need to
    load stats, attr, inventory, armory and etc.
  */



}




// <---- ! -----> [Queries] <---- ! ----->
std::pair<bool, std::string> DataBaseManager::queryAccount(std::string& username, std::string& password) noexcept
{
  const char* values[2] = { username.c_str(), password.c_str() };

  std::string& query = this->query_map_.at(QueryEnums::QUERY_LOGIN); 
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 2, nullptr, values, nullptr, nullptr, 0);
  /*
    This line is a (synchronous) database call. It sends our SQL Query as string and the parameters to PostgreSQL,
    and waits until PostgreSQL finishes, and gives us back a PGresult*.

    PGresult* is a libpq object that stores the result of the SQL command, it can have 0 rows or more.
    It is also a heap-managed object by libpq, so we must "release" it with PQclear(result)
    According to the PostgreSQL's docs every command result should be "released" with PQclear, when 
    of couse no longer needed

    PostgreSQL describes the PQexecParams as a command execution function that is protected from SQL injection mistakes.
    Arguments:
      1. Database connection
      2. C-style string -> Query 
      3. # of Parameters
      4. Parameter type array -> by passing nullptr -> we are saying infer the parameter types yourself
      5. acutaly parameter value array -> in our case "values"
      6. paramLengths -> nullptr -> treat values as normal null-terminated C strings. usually this is passed
        when we use binary parameters or need to pass values with embedded null bytes.
      7. paramFormats -> nullptr -> meaning all params are text format 
      8. resultFormat -> it controls how many columns are given back to us  
  */


  if(result == nullptr)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryAccount] -> Query result is nullptr <!> " << std::endl;
    return {false, nullptr};
  }

  if(PQresultStatus(result) != PGRES_TUPLES_OK)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryAccount] -> Query failed <!> " << std::endl;
    return {false, nullptr};
  }

  int rows = PQntuples(result);
  std::string account_id;

  if(rows == 1)
  {
    std::cout << "[SUCCESS] -> [DataBaseManager::queryAccount] -> Login Success <!> " << std::endl;
    account_id = PQgetvalue(result, 0, 0);
  }
  else
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryAccount] -> Login failed <!> " << std::endl;
  }

  PQclear(result);

  return {true, account_id};
}



