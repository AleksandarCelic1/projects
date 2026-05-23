#include "../include_/database_manager.hpp"


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

