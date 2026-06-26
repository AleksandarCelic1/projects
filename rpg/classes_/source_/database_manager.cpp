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

  // Setter (Insert) Queries 
  this->query_map_.insert({QueryEnums::QUERY_INSERT_CHARACTER,  "INSERT INTO Characters "
                                                                "("
                                                                  "account_id_, world_x, world_y, level_, class_, animation_state_, animation_index_"
                                                                ")"
                                                                "VALUES "
                                                                "("
                                                                  "$1, $2, $3, $4, $5, $6, $7"
                                                                ");"}); /* You need to return the char id from here <!> */

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
                                                                  "$1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12"
                                                                ");"
                                                              });

  this->query_map_.insert({QueryEnums::QUERY_INSERT_INVENTORY,  " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_ARMORY,     " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_CONTAINER,  " NOT FINISHED <!> "});
  this->query_map_.insert({QueryEnums::QUERY_INSERT_ITEM,       " NOT FINISHED <!> "});

  // Modify Queries <!> 
  this->query_map_.insert({QueryEnums::QUERY_MODIFY_CHARACTER,  "UPDATE Characters "
                                                                "SET "
                                                                  "world_x_           = $2, "
                                                                  "world_y_           = $3, "
                                                                  "level_             = $4, "
                                                                  "class_             = $5, "
                                                                  "animation_state_   = $6, "
                                                                  "animation_index_   = $7  "
                                                                "WHERE character_id_ = $1; "
                                                              });

  this->query_map_.insert({QueryEnums::QUERY_MODIFY_STATS,  "UPDATE CharactersStats "
                                                            "SET "
                                                              "base_health_           = $2, "
                                                              "current_health_        = $3, "
                                                              "base_mana_             = $4, "
                                                              "current_mana_          = $5, "
                                                              "physical_power_        = $6, "
                                                              "spell_power_           = $7, "
                                                              "magic_resistance_      = $8, "
                                                              "armor_                 = $9, "
                                                              "melee_range_           = $10, "
                                                              "spell_range_           = $11, "
                                                              "global_cooldown_       = $12, "
                                                              "armor_penetration_     = $13, "
                                                              "spell_penetration_     = $14, "
                                                              "attack_speed_          = $15, "
                                                              "spell_haste_           = $16, "
                                                              "hit_rating_            = $17, "
                                                              "physical_crit_chance_  = $18, "
                                                              "magic_crit_chance_     = $19, "
                                                              "movement_speed_        = $20, "
                                                              "lifesteal_             = $21, "
                                                              "tenacity_              = $22 "
                                                            "WHERE character_id_     = $1; "
                                                          });

  this->query_map_.insert({QueryEnums::QUERY_MODIFY_ATTRIBUTES, "UPDATE CharactersAttributes "
                                                                "SET "
                                                                  "strength_ = $2, "
                                                                  "dexterity_ = $3, "
                                                                  "intellect_ = $4, "
                                                                  "wisdom_ = $5, "
                                                                  "havoc_ = $6, "
                                                                  "chaos_ = $7, "
                                                                  "insight_ = $8, "
                                                                  "perception_ = $9, "
                                                                  "vamp_ = $10, "
                                                                  "faith_ = $11, "
                                                                  "tenacity_ = $12 "
                                                                "WHERE character_id_ = $1; "
                                                              });

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
  std::vector<LoadedCharValues> char_values = this->queryCharacters(account_id);
  if(char_values.empty())
  {
    return {};
  }


  std::vector<Character*> characters;
  int size = char_values.size();
  for(int index = 0; index < size; index++)
  {
    LoadedCharValues placeholder = char_values.at(index);
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

  std::vector<Character*> accounts_characters = account_logged_in->getCharacters();
  std::vector<Character*> loaded_characters = this->loadCharacters(account_id);
  if(loaded_characters.empty())
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

std::vector<LoadedCharValues> DataBaseManager::queryCharacters(const std::string account_id) noexcept
{
  const char* values[1] = { account_id.c_str() };
  std::string& query = this->query_map_.at(QueryEnums::QUERY_GET_CHARACTERS); 
  
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 1, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result)) 
  {
    return {};
  }

  int rows = PQntuples(result);
  std::vector<LoadedCharValues> loaded_char_values;

  for(int index = 0; index < rows; index++)
  {
    LoadedCharValues placeholder;
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

bool DataBaseManager::queryInsertCharacter(Character* character, size_t account_id) noexcept
{
  std::string acc_id          = std::to_string(account_id);
  std::string world_x         = std::to_string(character->getWorldX());
  std::string world_y         = std::to_string(character->getWorldY());
  std::string level           = std::to_string(character->getLevel());
  std::string class_type      = std::to_string(static_cast<int>(character->getClassType()));
  std::string animation_state = std::to_string(static_cast<int>(character->getAnimationState()));
  std::string animation_index = std::to_string(static_cast<int>(character->getAnimationIndex()));

  const char* values[7] = { acc_id.c_str(), world_x.c_str(), world_y.c_str(), 
                            level.c_str(), class_type.c_str(), animation_state.c_str(), 
                            animation_index.c_str() };

                  
  std::string& query = this->query_map_.at(QueryEnums::QUERY_INSERT_CHARACTER);
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 7, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGresult(result))
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInsertCharacter] -> Query failed <!> " << std::endl;
    return false;
  }


  /*
    Not finished this query should also return the char id since we have serial PK, will use that to store other character components
  */
}

void DataBaseManager::queryInsertStats(Stats* stats, size_t character_id) noexcept
{
  if(stats == nullptr)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInsertStats] -> Stats* provided is nullptr <!> " << std::endl;
    return;
  }

  std::string char_id           = std::to_string(character_id);
  std::string base_health       = std::to_string(stats->getBaseHealth());
  std::string current_health    = std::to_string(stats->getCurrentHealth());
  std::string base_mana         = std::to_string(stats->getBaseMana());
  std::string current_mana      = std::to_string(stats->getCurrentMana());
  std::string physical_power    = std::to_string(stats->getPhysicalPower());
  std::string spell_power       = std::to_string(stats->getSpellPower());
  std::string magic_resistance  = std::to_string(stats->getMagicResistance());
  std::string armor             = std::to_string(stats->getArmor());
  std::string melee_range       = std::to_string(stats->getMeleeRange());
  std::string spell_range       = std::to_string(stats->getSpellRange());
  std::string global_cdr        = std::to_string(stats->getGlobalCooldown());
  std::string armor_pen         = std::to_string(stats->getArmorPenetration());
  std::string spell_pen         = std::to_string(stats->getSpellPenetration());
  std::string attack_speed      = std::to_string(stats->getAttackSpeed());
  std::string spell_haste       = std::to_string(stats->getSpellHaste());
  std::string hit_rating        = std::to_string(stats->getHitRating());
  std::string phy_crit_chance   = std::to_string(stats->getPhysicalCritChance());
  std::string magic_crit_chance = std::to_string(stats->getMagicCritChance());
  std::string movement_speed    = std::to_string(stats->getMovementSpeed());
  std::string lifesteal         = std::to_string(stats->getLifeSteal());
  std::string tenacity          = std::to_string(stats->getTenacity());

  const char* values[22] = 
  {
    char_id.c_str(), base_health.c_str(), current_health.c_str(), base_mana.c_str(), current_mana.c_str(), 
    physical_power.c_str(), spell_power.c_str(), magic_resistance.c_str(), armor.c_str(), melee_range.c_str(),
    spell_range.c_str(), global_cdr.c_str(), armor_pen.c_str(), spell_pen.c_str(), attack_speed.c_str(),
    spell_haste.c_str(), hit_rating.c_str(), phy_crit_chance.c_str(), magic_crit_chance.c_str(), 
    movement_speed.c_str(), lifesteal.c_str(), tenacity.c_str()
  };

  std::string& query = this->query_map_.at(QueryEnums::QUERY_INSERT_STATS);
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 22, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGcommand(result))
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInsertStats] -> Query failed <!> " << std::endl;
    return;
  }
}


void DataBaseManager::queryInsertAttributes(Attributes* attributes, size_t character_id) noexcept
{
  if(attributes == nullptr)
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInsertAttributes] -> Attributes* provided is nullptr <!> " << std::endl;
    return;
  }

  std::string char_id    = std::to_string(character_id);
  std::string strength   = std::to_string(attributes->getStrength());
  std::string dexterity  = std::to_string(attributes->getDexterity());
  std::string intellect  = std::to_string(attributes->getIntellect());
  std::string wisdom     = std::to_string(attributes->getWisdom());
  std::string havoc      = std::to_string(attributes->getHavoc());
  std::string chaos      = std::to_string(attributes->getChaos());
  std::string insight    = std::to_string(attributes->getInsight());
  std::string perception = std::to_string(attributes->getPerception());
  std::string vamp       = std::to_string(attributes->getVamp());
  std::string faith      = std::to_string(attributes->getFaith());
  std::string tenacity   = std::to_string(attributes->getTenacity());

  const char* values[12] =
  {
    char_id.c_str(),
    strength.c_str(),
    dexterity.c_str(),
    intellect.c_str(),
    wisdom.c_str(),
    havoc.c_str(),
    chaos.c_str(),
    insight.c_str(),
    perception.c_str(),
    vamp.c_str(),
    faith.c_str(),
    tenacity.c_str()
  };

  std::string& query = this->query_map_.at(QueryEnums::QUERY_INSERT_ATTRIBUTES);
  PGresult* result = PQexecParams(this->connection_, query.c_str(), 12, nullptr, values, nullptr, nullptr, 0);

  if(!validatePGcommand(result))
  {
    std::cout << "[ERROR] -> [DataBaseManager::queryInsertAttributes] -> Query failed <!> " << std::endl;
    return;
  }
}

void DataBaseManager::queryInsertArmory(Armory* armory, size_t account_id) noexcept
{

}

void DataBaseManager::queryInsertInvetory(Inventory* invetory, size_t account_id) noexcept
{

}
void DataBaseManager::queryInsertContainer(Container* container, size_t account_id) noexcept
{

}

void DataBaseManager::queryInsertItem(Item* item, size_t account_id) noexcept
{

}