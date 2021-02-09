#ifndef PLAYER_SHAPE_H
#define PLAYER_SHAPE_H

#include <cassert>
#include <string>

enum class player_shape
{
  rocket,
  circle,
  square
};

/// Tests the functions related to player_shape
void test_player_shape();

std::string to_str(player_shape this_player_shape);

#endif // PLAYER_SHAPE_H
