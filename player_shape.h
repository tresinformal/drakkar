#ifndef PLAYER_SHAPE_H
#define PLAYER_SHAPE_H

#include <iosfwd>
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
std::ostream& operator<<(std::ostream& os, const player_shape ps);

#endif // PLAYER_SHAPE_H
