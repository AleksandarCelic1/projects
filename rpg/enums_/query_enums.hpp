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
  QUERY_ = 0
};


#endif