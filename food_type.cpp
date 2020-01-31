#include "food_type.h"
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
  }
}

std::ostream &operator<<(std::ostream &os, const food_type t)
{
  os << to_str_food_type(t);
  return os;
}

const std::string to_str_food_type(food_type this_food_type)

{

  switch (this_food_type) //!OCLINT
                          // it might be wise to keep a default statement
                          // in case for some reason an invalid input is given
  {
  case food_type::rocket:
    return "rocket";
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
