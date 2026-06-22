#include "../include_/database_manager.hpp"
#include "../../namespaces_/namespaces.hpp"

DataBaseManager* db_manager = new DataBaseManager();


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
  
  this->initializeQueryMap();
  this->initializeConnectionParameters();
  this->connection_ = PQconnectdb(this->connection_parameters_.c_str());
  this->connection_parameters_.clear();

  if(PQstatus(this->connection_) != CONNECTION_OK)
  {
    std::cout << "[ERROR] -> [DataBaseManager::DataBaseManager()] -> connection to the database failed <!> " << std::endl;
    PQfinish(this->connection_);
    this->connection_ = nullptr;
    return;
  }
  

  std::cout << "[INFORMATION] -> [DataBaseManager::DataBaseManager()] -> Connection to the DataBase Status: Succesful <!> " << std::endl;
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

  this->query_map_.insert({QueryEnums::QUERY_LOGIN,        "SELECT account_id_, username_, password_ FROM Accounts WHERE username_ = $1 AND password_ = $2 "});
  this->query_map_.insert({QueryEnums::QUERY_REGISTARTION, "INSERT INTO Accounts (username_, password_) VALUES ( $1, $2);"});

  // Getter Queries
  this->query_map_.insert({QueryEnums::QUERY_GET_CHARACTERS, "SELECT * FROM Characters WHERE account_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_STATS,      "SELECT * FROM CharactersStats WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_ATTRIBUTES, "SELECT * FROM CharactersAttributes WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_INVENTORY,  "SELECT * FROM Inventory WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_ARMORY,     "SELECT * FROM Armory WHERE character_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_CONTAINERS, "SELECT * FROM Containers WHERE invetory_id_ = $1 "});
  this->query_map_.insert({QueryEnums::QUERY_GET_ITEMS,      "SELECT * FROM Item WHERE container_id_ = $1 "});

  // Setter Queries 
  this->query_map_.insert({QueryEnums::QUERY_INSERT_CHARACTER,  " NOT FINISHED <!> "});

  this->query_map_.insert({QueryEnums::QUERY_INSERT_STATS,      "INSERT INTO CharactersStats "
                                                                "("
                                                                  "character_id_, base_health_, current_health_, base_mana_, current_mana_, physical_power_,"
                                                                  "spell_power_, magic_resistance_, armor_, melee_range_, spell_range_, global_cooldown_, armor_penetration_,"
                                                                  "spell_penetration_, attack_speed_, spell_haste_, hit_rating_, physical_crit_chance_, magic_crit_chance_," 
                                                                  "movement_speed_, lifesteal_, tenacity_"
                                                                ") "
                                                                "VALUES "
                                                                "( "
                                                                  "$1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20, $21, $22"
                                                                ");"
                                                              });

                                                              
  this->query_map_.insert({QueryEnums::QUERY_INSERT_ATTRIBUTES, "INSERT INTO CharactersAttributes "
                                                                "("
                                                                  "character_id_, strength_, dexterity_, intellect_, wisdom_, havoc_, chaos_,"
                                                                  "insight_, perception_, vamp_, faith_, tenacity_"
                                                                ") "
                                                                "VALUES "
                                                                "( "
                                                                  "$1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11"
                                                                ");"
                                                              });

  this->query_map_.insert({QueryEnums::QUERY_INSERT_INVENTORY,  " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_ARMORY,     " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_CONTAINER,  " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_ITEM,       " NOT FINISHED <!> "});

  this->query_map_.insert({QueryEnums::QUERY_MODIFY_CHARACTER, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_STATS, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_ATTRIBUTES, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_INVENTORY, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_ARMORY, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_CONTAINER, " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_ITEM, " NOT FINISHED <!> "});




  
}

void DataBaseManager::initializeConnectionParameters() noexcept
{
  std::string result;
  std::vector<std::string> credentials;

  /*
    We have to parse the env folder <!> 
  */

  std::ifstream file("../env_/database_credentials.env");
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

  result.pop_back();
  this->connection_parameters_ = result;

  /* Debug Log 
  std::cout << "[DEBUG] -> [DataBaseManager::initializeConnectionParameters] -> " << this->connection_parameters_ << std::endl; */
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

bool DataBaseManager::validatePGcommand(PGresult* result) noexcept
{
  if(result == nullptr)
  {
    std::cout << "[ERROR] -> [DataBaseManager::validatePGcommand] -> Query result is nullptr <!> " << std::endl;
    return false;
  }

  /*
    PostgreSQL checks the commands like UPDATE, DELETE, INSERT, CREATE TABLE and etc. as commands which 
    do not (and they dont) return rows, and because of that we cant compare the result with
    PGRES_TUPLES_OK but with PGRES_COMMAND_OK
  */
  if(PQresultStatus(result) != PGRES_COMMAND_OK)
  {
    std::cout << "[ERROR] -> [DataBaseManager::validatePGcommand] -> Query command was unsuccessful <!> " << std::endl;
    return false;
  }

  return true;
}
    

Account* DataBaseManager::tryLogin(const std::string username, const std::string password) noexcept
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
  Account* acc = new Account(username, password, acc_id, characters);

  return acc;
}

std::string DataBaseManager::loadAccount(const std::string username, const std::string password) noexcept
{
  std::string account_id = this->queryAccount(username, password);
  if(account_id.empty())
  {
    return "";
  }

  return account_id;

}

std::vector<Character*> DataBaseManager::loadCharacters(const std::string account_id) noexcept
{
  std::vector<loadedCharValues> char_values = this->queryCharacters(account_id);
  if(char_values.empty())
  {
    return {};
  }


  std::vector<Character*> characters;
  int size = char_values.size();
  for(int index = 0; index < size; index++)
  {
    loadedCharValues placeholder = char_values.at(index);
    std::string char_id = placeholder.character_id_;


    Stats* stats = this->queryStats(char_id);
    Attributes* attr = this->queryAttributes(char_id);
    Armory* armory = this->queryArmory(char_id);
    Inventory* inventory = this->queryInventory(char_id);

    if(stats == nullptr
    || attr == nullptr
    // || armory == nullptr
    || inventory == nullptr)
    {
      std::cout << "[ERROR] -> [DataBaseManager::loadCharacters] -> Char with ID:" << char_id << " can not be loaded <!> " << std::endl;
      continue;
    }


    /* Need to create a Character but no Classes are introduced yet <!> */
  }

  return {};
}

Account* DataBaseManager::tryRegister(const std::string username, const std::string password) noexcept
{
  std::string existing_account_id = this->loadAccount(username, password);
  if(!existing_account_id.empty())
  {
    return nullptr;
  }

  bool retval = this->queryRegistration(username, password);

  if(retval)
  {
    std::string account_id = this->queryAccount(username, password);
    if(account_id.empty())
    {
      std::cout << "[ERROR] -> [DataBaseManager::tryRegister] -> Account does not exist <!> " << std::endl;
      return nullptr;
    }

    size_t casted_id = static_cast<size_t>(std::stoi(account_id));


    Account* new_acc = new Account(username, password, casted_id, {});
    return new_acc;
  }

  return nullptr;
}

void DataBaseManager::save(Account* account_logged_in) noexcept
{
  /*
    1. Query to get the account to verify its existance in the DataBase
    2. Save each character 

  */

  std::string account_id = this->queryAccount(account_logged_in->getUsername(), account_logged_in->getPassword());
  if(account_id.empty())
  {
    std::cout << "[ERROR] -> [DataBaseManager::save] -> Current logged in Account does not exist in the DataBase <!> " << std::endl;
    return;
  }

  std::vector<Character*> characters = this->loadCharacters(account_id);
  if(characters.empty())
  {
    /*
      1. Insert the new chars if there are any <!> 
    */

    return;
  }

  /*
    1. Modify the existing chars <!> 
  */
  
  return;
}

// <---- ! -----> [Queries] <---- ! ----->
std::string DataBaseManager::queryAccount(const std::string username, const std::string password) noexcept
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
    std::cout << "[SUCCESS] -> [DataBaseManager::queryAccount] -> Success <!> " << std::endl;
    account_id = PQgetvalue(result, 0, 0);
  }
  else
  {
    /* 
      Those debug logs will be deleted as they are confusing due to register needing this to fail,
      and the login must not fail in order to succeed <!> 
    */
    std::cout << "[ERROR] -> [DataBaseManager::queryAccount] -> Failed <!> " << std::endl;
  }

  PQclear(result);

  return account_id;
}

std::vector<loadedCharValues> DataBaseManager::queryCharacters(const std::string account_id) noexcept
{
  const char* values[1] = { account_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_CHARACTERS); 
  
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {};
  }

  int rows = PQntuples(result);
  std::vector<loadedCharValues> loaded_char_values;

  for(int index = 0; index < rows; index++)
  {
    loadedCharValues placeholder;
    placeholder.character_id_ = PQgetvalue(result, index, 0);
    placeholder.world_x_ = std::stoi(PQgetvalue(result, index, 2));
    placeholder.world_y_ = std::stoi(PQgetvalue(result, index, 3));
    placeholder.level_ = std::stoi(PQgetvalue(result, index, 4));
    placeholder.class_ = std::stoi(PQgetvalue(result, index, 5));
    placeholder.anim_state_ = std::stoi(PQgetvalue(result, index, 6));
    placeholder.anim_index_ = std::stoi(PQgetvalue(result, index, 7));

    loaded_char_values.push_back(placeholder);

  }

  return loaded_char_values;
}

Stats* DataBaseManager::queryStats(const std::string character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_STATS);

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

Attributes* DataBaseManager::queryAttributes(const std::string character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_ATTRIBUTES);

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

Armory* DataBaseManager::queryArmory(const std::string character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_ARMORY);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return nullptr;
  }

  /* Armory will have to wait as we did not design the armory yet <!> */

  return nullptr;
}

Inventory* DataBaseManager::queryInventory(const std::string character_id) noexcept
{
  const char* values[1] = { character_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_INVENTORY);

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

  std::string inventory_id = PQgetvalue(result, 0, 0);
  int gold = std::stoi(PQgetvalue(result, 0, 2));
  int silver = std::stoi(PQgetvalue(result, 0, 3));
  int bronze = std::stoi(PQgetvalue(result, 0, 4));

  
  std::vector<Container*> containers = this->queryContainers(inventory_id);

  Inventory* loaded_inventroy = new Inventory(gold, silver, bronze, containers);
  return loaded_inventroy;

}

std::vector<Container*> DataBaseManager::queryContainers(const std::string inventory_id) noexcept
{
  const char* values[1] = { inventory_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_CONTAINERS);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {};
  }

  /* Containers will have to wait as thier design is yet to be finished <!> */
  return {};
}

std::vector<std::vector<Item*>> DataBaseManager::queryItems(const std::string container_id) noexcept
{
  const char* values[1] = { container_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_ITEMS);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {{}};
  }

  /* Items will have to wait as their desing is yet to be finished <!> */

  return {{}};
}

bool DataBaseManager::queryRegistration(const std::string username, const std::string password) noexcept
{
  const char* values[2] = { username.c_str(), password.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_REGISTARTION);

  PGresult* result = PQexecParams(this->connection_, query.c_str(), 2, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGcommand(result))
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryRegistration] -> Registration failed <!> " << std::endl;
    return false;
  }

  return true;
}

void DataBaseManager::queryInsertCharacter(Character* character) noexcept
{

}