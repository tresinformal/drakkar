
#include "environment_type.h"
#include <cassert>

std::string to_str_env_type(environment_type environment_type)
{
    switch (environment_type)
    {
        case environment_type::empty:   return "empty";
        case environment_type::quiet:   return "quiet";
        case environment_type::random:   return "random";
        case environment_type::attractive:   return "attractive";
        case environment_type::repellent:   return "repellent";
        case environment_type::wormhole:   return "wormhole";
        default:      return "[Unknown environment_type]";
    }
}

void test_environment_type()
{
  //Conversion to string
  {
    assert(to_str_env_type(environment_type::empty) == "empty");
    assert(to_str_env_type(environment_type::random)== "random");
    assert(to_str_env_type(environment_type::random)!= "wormhole");
  }
  //Other tests will follow here

}
