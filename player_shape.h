#include<string>

#ifndef PLAYER_SHAPE_H
#define PLAYER_SHAPE_H

enum class player_shape
{
  rocket,
  circle
};

/// Tests the functions related to player_shape
void test_player_shape();
inline const std::string to_str(player_shape cat)
{
    switch (cat)
    {
        case player_shape::circle:   return "circle";
        case player_shape::rocket:   return "rocket";
        default:      return "[Unknown player_shape]";
    }
}
#endif // PLAYER_SHAPE_H
