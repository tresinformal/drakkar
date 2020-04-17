#include "projectile_type.h"
#include <sstream>
// in projectile_type.cpp

void test_projectile_type()
{
  {
    std::stringstream s;
    s << projectile_type::rocket;
  }
  {
    std::stringstream s;
    s << projectile_type::cat;
  }
}

std::ostream &operator<<(std::ostream &os, const projectile_type t)
{
  os << to_str_projectile_type(t);
  return os;
}

const std::string to_str_projectile_type(projectile_type this_projectile_type)

{

  switch (this_projectile_type) //!OCLINT
                          // it might be wise to keep a default statement
                          // in case for some reason an invalid input is given
  {
  case projectile_type::rocket:
    return "rocket";
  case projectile_type::cat:
    return "cat";


  default:
    return "[Unknown projectile_type]";
  }
}
