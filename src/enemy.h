#ifndef ENEMY_H
#define ENEMY_H
#include "coordinate.h"
#include <string>

class enemy
{
public:
  enemy(const coordinate c = coordinate(0.0, 0.0));
  /// Get the X coordinate of the player
  double get_x() const noexcept {return get_position().get_x(); }

  /// Get the Y coordinate of the player
  double get_y() const noexcept {return get_position().get_y(); }

  /// Get the coordinate object of the player
  coordinate get_position() const noexcept { return m_coordinate;}

private:
  /// The coordinates of the enemy
  coordinate m_coordinate;
};



void test_enemy();

/// Implement stream operator
std::stringstream& operator << (std::stringstream &out, const enemy &enemy);

/// Implement equality operator
bool operator==(const enemy& lhs, const enemy& rhs) noexcept;


#endif // ENEMY_H
