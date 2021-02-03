#include "projectile_type.h"
#include <sstream>
#include <cassert>

void test_projectile_type()
{
  // String conversion
  {
    assert(to_str(projectile_type::cat) == "cat");
    assert(to_str(projectile_type::rocket) == "rocket");
  }
  // Can stream
  {
    std::stringstream s;
    s << projectile_type::rocket;
    assert(!s.str().empty());
  }
}

std::ostream &operator<<(std::ostream &os, const projectile_type t)
{
  os << to_str(t);
  return os;
}

std::string to_str(const projectile_type this_projectile_type) noexcept
{
  if (this_projectile_type == projectile_type::rocket)
  {
    return "rocket";
  }
  assert(this_projectile_type == projectile_type::cat);
  return "cat";
}
