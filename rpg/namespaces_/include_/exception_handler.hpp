#ifndef EXCEPTION_HANDLER_HPP
#define EXCEPTION_HANDLER_HPP

/*
  Utility Namespace [ExceptionHandler] -> used to detect exceptions 
*/
namespace ExceptionHandler
{
  template <typename Map, typename Key> 
  auto get(Map& container, Key& key)
  {
    try
    {
      return container.at(key);
    }
    catch(const std::exception& exception)
    {
      std::cout << "[Exception Caught] -> [ExceptionHandler::contains]" << std::endl;
      return nullptr;
    }
  }

};



#endif