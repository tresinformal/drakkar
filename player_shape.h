#include<string>
#include<cassert>

#ifndef PLAYER_SHAPE_H
#define PLAYER_SHAPE_H

enum class player_shape
{
  rocket,
  circle
};

/// Tests the functions related to player_shape
void test_player_shape();
inline const std::string to_str(player_shape this_player_shape)
{
    switch (this_player_shape)
    {
    case player_shape::circle:   return "circle";
    default:
        assert(this_player_shape == player_shape::rocket);
                return "rocket";
    }
}
#endif // PLAYER_SHAPE_H
