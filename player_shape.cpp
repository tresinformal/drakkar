#include "player_shape.h"
#include <cassert>
#include <sstream>
#include <iostream>


void test_player_shape()
{
  // Conversion to string
  {
    assert(to_str(player_shape::circle) == "circle");
    assert(to_str(player_shape::rocket) == "rocket");
    assert(to_str(player_shape::square) == "square");
  }
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
