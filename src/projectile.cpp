#include "projectile.h"
#include <cassert>
#include <cmath>


projectile::projectile(
  const coordinate c, const double direction, const projectile_type p,
  const double radius, const std::string& owner_id)
  : m_coordinate{c}, m_direction{direction}, m_projectile_type{p}, m_radius{radius}, m_owner_id{owner_id}

{
}

void projectile::move()
{
  m_coordinate.set_x(m_coordinate.get_x() + std::cos(m_direction));
  m_coordinate.set_y(m_coordinate.get_y() + std::sin(m_direction));
  //m_coordinate.move(m_direction);
}

void projectile::place(const coordinate& c)
{
  m_coordinate = c;
}

std::string projectile::get_owner_id() noexcept { return m_owner_id;}

void test_projectile()
{
  #ifndef NDEBUG // no tests in release
  // Constructor
  {
    const double x{1.2};
    const double y{3.4};
    const coordinate c{x, y};
    const double d{5.6};
    const projectile_type t = projectile_type::cat;
    const double r{7.8};
    const projectile p(c, d, t, r);
    assert(x == get_x(p));
    assert(y == get_y(p));
    assert(d == p.get_direction());
    assert(t == p.get_type());
    assert(r == p.get_radius());
  }
  #endif

#define FIX_ISSUE_327
#ifdef FIX_ISSUE_327
  {
    coordinate c{1.23456, 123456.789};
    projectile p{c};
    assert(p.get_position() == c);
  }
#endif


//#define FIX_ISSUE_364
#ifdef FIX_ISSUE_364
  {
    auto init_position = coordinate{0, 0};
    double direction{0};
    projectile p{init_position, direction};
    p.move();
    assert(p.get_position() != init_position);
  }
#endif

}
