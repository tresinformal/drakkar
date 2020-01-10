#ifndef PROJECTILE_H
#define PROJECTILE_H


class projectile
{
public:
  projectile(const double x = 0.0, const double y = 0.0, const double direction = 0.0);

  private:

  /// The x coordinat
  double m_x;

  /// The y coordinat
  double m_y;

  /// The direction of projectile in radians
  double m_direction;

};

#endif // PROJECTILE_H
