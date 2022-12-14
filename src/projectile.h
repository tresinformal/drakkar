#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "projectile_type.h"
#include "coordinate.h"
#include "color.h"
#include <string>

/// A projectile has the virtual shape of a circle
class projectile
{
public:
  projectile(const coordinate c,
             const double direction = 0.0, projectile_type = projectile_type::rocket,
             const double radius = 100, const std::string& owner_id = "-1");

  coordinate get_position() const noexcept { return m_coordinate; }
  double get_x() const noexcept { return m_coordinate.get_x(); }
  double get_y() const noexcept { return m_coordinate.get_y(); }

  /// Get the direction of player movement
  double get_direction() const noexcept { return m_direction; }

  ///Get the radius of the projectile
  double get_radius() const noexcept {return m_radius;}

  /// Move a certain distance (of 1.0 for now) in the direction the projectile
  /// is facing
  void move();

  ///Places a projectile at a given coordinate
  void place(const coordinate& c);

  /// Get projectile type of the game
  projectile_type get_type() const { return m_projectile_type; }

  void set_type(const projectile_type &p_type) noexcept { m_projectile_type = p_type; }

  std::string get_owner_id() noexcept;

  /// The fire rate of the projectile, in ticks
  static const int m_fire_rate{200};

private:
  /// The coordinate
  coordinate m_coordinate;

  /// The direction of projectile in radians
  double m_direction;

  /// the environment
  projectile_type m_projectile_type;

  /// The projectile is a circle
  double m_radius;

  /// The owner of the projectile
  std::string m_owner_id;
};

void test_projectile();

#endif // PROJECTILE_H
