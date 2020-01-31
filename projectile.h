#ifndef PROJECTILE_H
#define PROJECTILE_H

class projectile
{
public:
  projectile(const double x = 0.0, const double y = 0.0,
             const double direction = 0.0);

  double get_x() const noexcept { return m_x; }
  double get_y() const noexcept { return m_y; }

  /// Get the direction of player movement
  double get_direction() const noexcept { return m_direction; }

  /// Move a certain distance (of 1.0 for now) in the direction the projectile
  /// is facing
  void move();

private:
  /// The x coordinat
  double m_x;

  /// The y coordinat
  double m_y;

  /// The direction of projectile in radians
  double m_direction;
};

#endif // PROJECTILE_H
