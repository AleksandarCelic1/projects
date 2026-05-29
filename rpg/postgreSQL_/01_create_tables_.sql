DROP TABLE IF EXISTS Accounts;
DROP TABLE IF EXISTS Characters;
DROP TABLE IF EXISTS CharactersStats;
DROP TABLE IF EXISTS CharactersAttributes;


CREATE TABLE Accounts 
(
  account_id_ SERIAL        PRIMARY KEY,
  username_   VARCHAR(64)   UNIQUE NOT NULL,
  password_   VARCHAR(64)   NOT NULL

);

CREATE TABLE Characters
(
  character_id_     SERIAL      PRIMARY KEY,
  account_id_       INTEGER     NOT NULL REFERENCES Accounts(account_id_),
  world_x_          INTEGER     NOT NULL,
  world_y_          INTEGER     NOT NULL,
  level_            INTEGER     NOT NULL,
  class_            INTEGER     NOT NULL,
  animation_state_  INTEGER     NOT NULL,
  animation_index_  INTEGER     NOT NULL

);

CREATE TABLE CharactersStats
(
  character_id_         INTEGER       NOT NULL REFERENCES Characters(character_id_),
  base_health_          INTEGER,
  current_health_       INTEGER,
  base_mana_            INTEGER,
  current_mana_         INTEGER,
  physical_power_       INTEGER,
  spell_power_          INTEGER,
  magic_resistance_     INTEGER,
  armor_                INTEGER,
  melee_range_          INTEGER,
  spell_range_          INTEGER,
  global_cooldown_      INTEGER,
  armor_penetration_    INTEGER,
  spell_penetration_    INTEGER,

  attack_speed_         DECIMAL(4, 2),
  spell_haste_          DECIMAL(4, 2),
  hit_rating_           DECIMAL(4, 2),
  physical_crit_chance_ DECIMAL(4, 2),
  magic_crit_chance_    DECIMAL(4, 2),
  movement_speed_       DECIMAL(4, 2),
  lifesteal_            DECIMAL(4, 2),
  tenacity_             DECIMAL(4, 2)
);

CREATE TABLE CharactersAttributes
(
  character_id_ INTEGER       NOT NULL REFERENCES Characters(character_id_),
  strength_     INTEGER,
  dexterity_    INTEGER,
  intellect_    INTEGER,
  wisdom_       INTEGER,
  havoc_        INTEGER,
  chaos_        INTEGER,
  insight_      INTEGER,
  perception_   INTEGER,
  vamp_         INTEGER,
  faith_        INTEGER,
  tenacity_     INTEGER
);

CREATE TABLE Inventory
(
  inventory_id_ SERIAL        PRIMARY KEY,
  character_id_ INTEGER       NOT NULL REFERENCES Characters(character_id_),
  gold_         INTEGER,
  silver_       INTEGER,
  bronze_       INTEGER,
);

CREATE TABLE Container
(
  container_id_ SERIAL      PRIMARY KEY,
  inventory_id_ INTEGER     NOT NULL REFERENCES Inventory(inventory_id_),

);

CREATE TABLE Item 
(
  item_id_      SERIAL    PRIMARY KEY,
  container_id_ INTEGER.  NOT NULL REFERENCES Container(container_id_)
);

CREATE TABLE Armory
(
  character_id_ INTEGER       NOT NULL REFERENCES Characters(character_id_),
);


















