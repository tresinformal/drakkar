#include "player_shape.h"

void test_player_shape()
{
  #ifdef FIX_ISSUE_38
  //Conversion to string
  {
    assert(to_str(player_shape::circle) == "circle");
    assert(to_str(player_shape::rocket) == "rocket");
  }
  #endif
}

