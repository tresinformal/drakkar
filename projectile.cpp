#include "projectile.h"
#include <cmath>

projectile::projectile(
  const double x, const double y, const double direction, const projectile_type p,
  const double radius)
  : m_x{x}, m_y{y}, m_direction{direction}, m_projectile_type{p}, m_radius{radius}

{
}

void projectile::move()
{
  m_x += std::cos(m_direction);
  m_y += std::sin(m_direction);
}

