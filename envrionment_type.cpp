
#include "environment_type.h"
#include <cassert>

void test_environment_type()
{
#define FIX_ISSUE_40
#ifdef  FIX_ISSUE_40
//Conversion to string

  assert(to_str_env_type(environment_type::empty) == "empty");
  assert(to_str_env_type(environment_type::random)== "random");
  assert(to_str_env_type(environment_type::random)!= "wormhole");
#endif
}
