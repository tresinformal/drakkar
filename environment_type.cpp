#include <sstream>
#include "environment_type.h"
#include <cassert>

std::string to_str(environment_type this_env_type)
{
  switch (this_env_type)
  {
  case environment_type::empty:
    return "empty";
  case environment_type::quiet:
    return "quiet";
  case environment_type::random:
    return "random";
  case environment_type::attractive:
    return "attractive";
  case environment_type::repellent:
    return "repellent";
  case environment_type::wormhole:
    return "wormhole";
  }
  return "[Unknown environment_type]";
}

void test_individual_type()
{
  // Conversion to string
  {
    assert(to_str(environment_type::empty) == "empty");
    assert(to_str(environment_type::random) == "random");
    assert(to_str(environment_type::random) != "wormhole");
  }
  // Other tests will follow here
 {
    std::stringstream s;
    s << environment_type::empty;
 }
}

std::ostream &operator<<(std::ostream &os, const action_type t)
{
  os << to_str_act_type(t);
  return os;
}
