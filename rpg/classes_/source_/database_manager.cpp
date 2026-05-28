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

  this->query_map_.insert({QueryEnums::QUERY_LOGIN, "SELECT account_id_, username_, password_ FROM Accounts WHERE username_ = $1 AND password_ = $2 "});
  this->query_map_.insert({QueryEnums::QUERY_CHARACTERS, "SELECT * FROM Characters WHERE account_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_STATS, "SELECT * FROM CharactersStats WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_ATTRIBUTES, "SELECT * FROM CharactersAttributes WHERE character_id_ = $1 "});

  /* Look into last 2 <!> */
  this->query_map_.insert({QueryEnums::QUERY_INVENTORY, "SELECT * FROM Inventory WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_ARMORY, "SELECT * FROM Armory WHERE character_id_ = $1 "});


  
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

bool DataBaseManager::validatePGresult(PGresult* result) noexcept
{
  if(result == nullptr)
  {
    std::cout << "[ERROR] -> [DataBaseManager::validatePGresult] -> Query result is nullptr <!> " << std::endl;
    return false;
  }

  if(PQresultStatus(result) != PGRES_TUPLES_OK)
  {
    std::cout << "[ERROR] -> [DataBaseManager::validatePGresult] -> Query failed <!> " << std::endl;
    return false;
  }

  return true;
}
    

Account* DataBaseManager::tryLogin(std::string& username, std::string& password) noexcept
{
  std::string account_id = this->loadAccount(username, password);
  if(account_id.empty())
  {
    std::cout << "[ERROR] -> [DataBaseManager::tryLogin] -> Account does not exist <!> " << std::endl;
    return nullptr;
  }

  std::vector<Character*> characters = this->loadCharacters(account_id);
  if(characters.empty())
  {
    std::cout << "[INFORMATION] -> [DataBaseManager::tryLogin] -> Account has no Characters <!> " << std::endl;
  }

  size_t acc_id = static_cast<size_t>(std::stoi(account_id));
  Account* acc = new Account(username, acc_id, characters);

}

std::string DataBaseManager::loadAccount(std::string& username, std::string& password) noexcept
{
  std::string account_id = this->queryAccount(username, password);
  if(account_id.empty())
  {
    return "";
  }

  return account_id;

}

std::vector<Character*> DataBaseManager::loadCharacters(std::string& account_id) noexcept
{
  std::vector<std::string> char_ids = this->queryCharacters(account_id);
  if(char_ids.empty())
  {
    return {};
  }


  std::vector<Character*> characters;
  int size = char_ids.size();
  for(int index = 0; index < size; index++)
  {
    std::string char_id = char_ids.at(index);


    Stats* stats = this->queryStats(char_id);
    Attributes* attr = this->queryAttributes(char_id);
    Armory* armory = this->queryArmory(char_id);
    Inventory* inventory = this->queryInventory(char_id);

    if(stats == nullptr
    || attr == nullptr
    || armory == nullptr
    || inventory == nullptr)
    {
      std::cout << "[ERROR] -> [DataBaseManager::loadCharacters] -> Char with ID:" << char_id << " can not be loaded <!> " << std::endl;
      continue;
    }

    /* To make char i need world x,y and state/index for animation still ? */
  }
}


// <---- ! -----> [Queries] <---- ! ----->
std::string DataBaseManager::queryAccount(std::string& username, std::string& password) noexcept
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

  if(!validatePGresult(result)) 
  {
    return "";
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

  return account_id;
}

std::vector<std::string> DataBaseManager::queryCharacters(std::string& account_id) noexcept
{
  const char* values[1] = { account_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_CHARACTERS); 
  
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {};
  }

  int rows = PQntuples(result);
  std::vector<std::string> char_ids;

  for(int index = 0; index < rows; index++)
  {
    std::string placeholder = PQgetvalue(result, index, 0);
    /* Do i need to check if this is valid !? */
    char_ids.push_back(placeholder);
  }

  return char_ids;
}

Stats* DataBaseManager::queryStats(std::string& character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_STATS);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return nullptr;
  }

  int rows = PQntuples(result);
  if(rows != 1)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryStats] -> More than one Stats* exists for a single Char ?! <!> " << std::endl;
    return nullptr;
  }

  int base_health = std::stoi(PQgetvalue(result, 0, 1));
  int current_health = std::stoi(PQgetvalue(result, 0, 2));
  int base_mana = std::stoi(PQgetvalue(result, 0, 3));
  int current_mana = std::stoi(PQgetvalue(result, 0, 4));
  int physical_power = std::stoi(PQgetvalue(result, 0, 5));
  int spell_power = std::stoi(PQgetvalue(result, 0, 6));
  int magic_resistance = std::stoi(PQgetvalue(result, 0, 7));
  int armor = std::stoi(PQgetvalue(result, 0, 8));
  int melee_range = std::stoi(PQgetvalue(result, 0, 9));
  int spell_range = std::stoi(PQgetvalue(result, 0, 10));
  int gcd = std::stoi(PQgetvalue(result, 0, 11));
  int arp = std::stoi(PQgetvalue(result, 0, 12));
  int spell_pen = std::stoi(PQgetvalue(result, 0, 13));

  float attack_speed = std::stof(PQgetvalue(result, 0, 14));
  float spell_haste = std::stof(PQgetvalue(result, 0, 15));
  float hit_rating = std::stof(PQgetvalue(result, 0, 16));
  float physical_crit_chance = std::stof(PQgetvalue(result, 0, 17));
  float magic_crit_chance = std::stof(PQgetvalue(result, 0, 18));
  float movement_speed = std::stof(PQgetvalue(result, 0, 19));
  float lifesteal = std::stof(PQgetvalue(result, 0, 20));
  float tenacity = std::stof(PQgetvalue(result, 0, 21));

  Stats* loaded_stats = new Stats
    (base_health, current_health, base_mana, current_mana, physical_power, spell_power,
     attack_speed, spell_haste, hit_rating, physical_crit_chance, magic_crit_chance,
     magic_resistance, armor, melee_range, spell_range, gcd, arp, spell_pen, movement_speed,
     lifesteal, tenacity);

  return loaded_stats;

}

Attributes* DataBaseManager::queryAttributes(std::string& character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_ATTRIBUTES);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {};
  }

  int rows = PQntuples(result);
  if(rows != 1)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryAttributes] -> More than one Attributes* exists for a single Char ?! <!> " << std::endl;
    return nullptr;
  }

  int strength = std::stoi(PQgetvalue(result, 0, 1));
  int dexterity = std::stoi(PQgetvalue(result, 0, 2));

  int intellect = std::stoi(PQgetvalue(result, 0, 3));
  int wisdom = std::stoi(PQgetvalue(result, 0, 4));

  int havoc = std::stoi(PQgetvalue(result, 0, 5));
  int chaos = std::stoi(PQgetvalue(result, 0, 6));

  int insight = std::stoi(PQgetvalue(result, 0, 7));
  int perception = std::stoi(PQgetvalue(result, 0, 8));

  int vamp = std::stoi(PQgetvalue(result, 0, 9));
  int faith = std::stoi(PQgetvalue(result, 0, 10));
  int tenacity = std::stoi(PQgetvalue(result, 0, 11));

  Attributes* loaded_attr = new Attributes
    (strength, dexterity, intellect, 
     wisdom, havoc,chaos, insight, 
     perception, vamp, faith, tenacity);

  return loaded_attr;
}

Armory* DataBaseManager::queryArmory(std::string& character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_ARMORY);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return nullptr;
  }


  /* Armory will have to wait as we did not design the armory yet <!> */
}

Inventory* DataBaseManager::queryInventory(std::string& character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_INVENTORY);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return nullptr;
  }

  int rows = PQntuples(result);
  if(rows != 1)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInventory] -> More than one Inventory* exists for a single Char ?! <!> " << std::endl;
    return nullptr;
  }

  int gold = std::stoi(PQgetvalue(result, 0, 1));
  int silver = std::stoi(PQgetvalue(result, 0, 2));
  int bronze = std::stoi(PQgetvalue(result, 0, 3));

  /* I still need containers <!> */

  Inventory* loaded_inventroy = new Inventory();

}





