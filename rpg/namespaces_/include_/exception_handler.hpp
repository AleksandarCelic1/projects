#ifndef EXCEPTION_HANDLER_HPP
#define EXCEPTION_HANDLER_HPP

/*
  Utility Namespace [ExceptionHandler] -> used to detect exceptions 
*/
namespace ExceptionHandler
{
  template <typename Map, typename Key> 
  void contains(std::vector<Map>& map, Key& key);

};



#endif