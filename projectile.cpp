#include "projectile.h"
#include <cmath>

projectile::projectile(const double x, const double y, const double direction)
    : m_x{x}, m_y{y}, m_direction{direction}

{
}

void projectile::move()
{
  m_x += std::cos(m_direction);
  m_y += std::sin(m_direction);
}
