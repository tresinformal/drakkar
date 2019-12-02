#include "player_shape.h"
#include <cassert>

void test_player_shape()
{

#define FIX_ISSUE_38
#ifdef FIX_ISSUE_38

  //Conversion to string
  {
    assert(to_str(player_shape::circle) == "circle");
    assert(to_str(player_shape::rocket) == "rocket");
    assert(to_str(player_shape::square) == "square");

  }
  #endif
}

const std::string to_str(player_shape this_player_shape)
{
  if (this_player_shape == player_shape::circle)
  {
    return "circle";
  }
  else if (this_player_shape == player_shape::rocket)
  {
  return "rocket";
  }
  else if(this_player_shape == player_shape::square)
  {
      return "square";
  }
  else {
      return "ERROR! Invalid player_shape, "
             "or unitiated player shape";
  }
}
