#ifndef QUERY_ENUMS_HPP
#define QUERY_ENUMS_HPP


/*
  QueryEnums is used an enum, which is going to be used as a key in a map that will map to strings,
  those strings are essentially queries, which the program will use to query the db in order to 
  get the desired information, to avoid manually calling queries everytime we make a map of constant strings

  Prefix: "Query_"
*/
enum class QueryEnums
{
  QUERY_LOGIN = 0,
  QUERY_REGISTARTION = 1,

  QUERY_GET_CHARACTERS = 2,
  QUERY_GET_STATS = 3,
  QUERY_GET_ATTRIBUTES = 4,
  QUERY_GET_INVENTORY = 5,
  QUERY_GET_ARMORY = 6,
  QUERY_GET_CONTAINERS = 7,
  QUERY_GET_ITEMS = 8,

  QUERY_INSERT_CHARACTER = 9,
  QUERY_INSERT_STATS = 10,
  QUERY_INSERT_ATTRIBUTES = 11,
  QUERY_INSERT_INVENTORY = 12,
  QUERY_INSERT_ARMORY = 13,
  QUERY_INSERT_CONTAINER = 14,
  QUERY_INSERT_ITEM = 15,

  QUERY_MODIFY_CHARACTER = 16,
  QUERY_MODIFY_STATS = 17,
  QUERY_MODIFY_ATTRIBUTES = 18,
  QUERY_MODIFY_INVENTORY = 19,
  QUERY_MODIFY_ARMORY = 20,
  QUERY_MODIFY_CONTAINER = 21,
  QUERY_MODIFY_ITEM = 22
};


#endif