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

  default:
    assert(this_env_type == environment_type::wormhole);
    return "wormhole";
  }
}

void test_individual_type()
{
  #ifndef NDEBUG // no tests is release
  // Conversion to string
  {
    assert(to_str(environment_type::empty) == "empty");
    assert(to_str(environment_type::quiet) == "quiet");
    assert(to_str(environment_type::random) == "random");
    assert(to_str(environment_type::attractive) == "attractive");
    assert(to_str(environment_type::repellent) == "repellent");
    assert(to_str(environment_type::wormhole) == "wormhole");
  }
  // Other tests will follow here
 {
    std::stringstream s;
    s << environment_type::empty;
 }
#endif
}

std::ostream &operator<<(std::ostream &os, const environment_type t)
{
  os << to_str(t);
  return os;
}
