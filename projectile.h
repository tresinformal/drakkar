#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "projectile_type.h"
#include "coordinate.h"

/// A projectile has the virtual shape of a circle
class projectile
{
public:
  projectile(const coordinate c,
             const double direction = 0.0, projectile_type = projectile_type::rocket,
             const double radius = 100);

  coordinate get_position() const noexcept { return m_coordinate; }



  /// Get the direction of player movement
  double get_direction() const noexcept { return m_direction; }

  ///Get the radius of the projectile
  double get_radius() const noexcept {return m_radius;}

  /// Move a certain distance (of 1.0 for now) in the direction the projectile
  /// is facing
  void move();

  /// Get projectile type of the game
  projectile_type get_type() const { return m_projectile_type; }

  void set_type(const projectile_type &p_type) noexcept { m_projectile_type = p_type; }

//  const double get_x() { return m_coordinate.get_x(); }
//  const double get_y() { return m_coordinate.get_y(); }


private:
  /// The coordinate
  coordinate m_coordinate;

  /// The direction of projectile in radians
  double m_direction;

  /// the environment
  projectile_type m_projectile_type;

  /// The projectile is a circle
  double m_radius;
};


//get only x or y coordinate of a projectile
double get_x(const projectile& p)  noexcept;
double get_y(const projectile& p)  noexcept;

void test_projectile();

#endif // PROJECTILE_H
