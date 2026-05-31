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
  QUERY_CHARACTERS = 1,
  QUERY_STATS = 2,
  QUERY_ATTRIBUTES = 3,
  QUERY_INVENTORY = 4,
  QUERY_ARMORY = 5,
  QUERY_CONTAINERS = 6,
  QUERY_ITEMS = 7,
  QUERY_REGISTARTION = 8
};


#endif