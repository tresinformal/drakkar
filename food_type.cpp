#include "food_type.h"
#include <string>
#include <cassert>
#include <sstream>
// in food_type.cpp

void test_food_type()
{
  {
    std::stringstream s;
    s << food_type::rocket;
  }
  {
    std::stringstream s;
    s << food_type::potion_of_camouflage;
  }
  {
    std::stringstream s;
    s << food_type::neutral;
  }
  {
    std::stringstream s;
    s << food_type::laser;
  }
  {
    std::stringstream s;
    s << food_type::poison;
    assert(!s.str().empty());
  }
    assert(to_str(food_type::rocket) == std::string("rocket"));
    assert(to_str(food_type::potion_of_camouflage) == std::string("potion_of_camouflage"));
    assert(to_str(food_type::neutral) == std::string("neutral"));
    assert(to_str(food_type::laser) == std::string("laser"));
    assert(to_str(food_type::poison) == std::string("poison"));
}

std::ostream &operator<<(std::ostream &os, const food_type t)
{
  os << to_str(t);
  return os;
}

std::string to_str(food_type this_food_type) noexcept

{

  switch (this_food_type) //!OCLINT
                          // it might be wise to keep a default statement
                          // in case for some reason an invalid input is given
  {
  case food_type::rocket:
    return "rocket";
  case food_type::potion_of_camouflage:
    return "potion_of_camouflage";
  case food_type::laser:
    return "laser";
  case food_type::poison:
    return "poison";
  case food_type::neutral:
    return "neutral";

  default:
    return "[Unknown food_type]";
  }
}
