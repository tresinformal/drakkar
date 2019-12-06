
#include "environment_type.h"
#include <cassert>

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
