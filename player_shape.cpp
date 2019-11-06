#include <assert.h>
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
  }
  #endif
}

