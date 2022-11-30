#include "player_shape.h"
#include <cassert>
#include <sstream>
#include <iostream>


void test_player_shape()
{
  #ifndef NDEBUG // no tests in release
  // Conversion to string
  {
    assert(to_str(player_shape::circle) == "circle");
    assert(to_str(player_shape::rocket) == "rocket");
    assert(to_str(player_shape::square) == "square");
    std::stringstream s;
    s << "Player has shape " << player_shape::circle;
    assert(s.str() == "Player has shape circle");
  }
  #endif
}

std::string to_str(player_shape this_player_shape)
{
  if (this_player_shape == player_shape::circle)
  {
    return "circle";
  }
  else if (this_player_shape == player_shape::rocket)
  {
    return "rocket";
  }
  assert(this_player_shape == player_shape::square);
  return "square";
}

std::ostream& operator<<(std::ostream& os, const player_shape ps)
{
   os << to_str(ps);
   return os;
}
