#ifndef PLAYER_H
#define PLAYER_H
#include "player_shape.h"

class player
{
public:
  player(const double x, const double y, const player_shape shape, const double player_speed=0);

  /// Get the X coordinat of the player
  double get_x() const noexcept { return m_x; }

  /// Get the Y coordinat of the player
  double get_y() const noexcept { return m_y; }

  /// Get the shape of the player
  player_shape get_shape() const noexcept { return m_shape; }
  
  /// Get the speed of the player
  double get_speed() const noexcept { return m_player_speed; }

private:

  /// The X coordinat of the player
  double m_x;

  /// The Y coordinat of the player
  double m_y;

  ///The shape of the player
  player_shape m_shape;

  /// The speed of the player
  double m_player_speed;
};

/// Test the player class
void test_player();


#endif // PLAYER_H
