#include "player_shape.h"
#include <cassert>

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
  switch (this_player_shape)
  {
    case player_shape::circle: return "circle";
    case player_shape::rocket: return "rocket";
    default: break;
  }
  assert(this_player_shape == player_shape::square);
  return "square";
}
