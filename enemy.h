#ifndef ENEMY_H
#define ENEMY_H
#include "coordinate.h"
#include <string>

class enemy
{
public:
  enemy(const coordinate c = coordinate(0.0, 0.0));

  /// Get the coordinate object of the player
  coordinate get_position() const noexcept { return m_coordinate;}

private:
  /// The coordinates of the enemy
  coordinate m_coordinate;
};

/// Get the X coordinate of the player
double get_x(const enemy& e) noexcept;

/// Get the Y coordinate of the player
double get_y(const enemy& e) noexcept;


void test_enemy();

/// Implement stream operator
std::stringstream& operator << (std::stringstream &out, const enemy &enemy);

/// Implement equality operator
bool operator==(const enemy& lhs, const enemy& rhs) noexcept;


#endif // ENEMY_H
