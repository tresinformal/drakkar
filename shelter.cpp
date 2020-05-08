#include "shelter.h"
#include <cassert>
#include <cmath>

shelter::shelter(const double x, const double y, const double radius,
                 const color &c, const double shelter_speed, const double direction)
    : m_color{c}, m_radius{radius}, m_x{x}, m_y{y},m_speed {shelter_speed}, m_direction{direction}
{
}

int get_blueness(const shelter &f) noexcept
{
  return get_blueness(f.get_color());
}

int get_greenness(const shelter &f) noexcept
{
  return get_greenness(f.get_color());
}

int get_opaqueness(const shelter &f) noexcept
{
  return get_opaqueness(f.get_color());
}

int get_redness(const shelter &f) noexcept
{
  return get_redness(f.get_color());
}

void test_shelter()
{

  {
    shelter f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }
  // X and Y work as expected
  {
    const double x{12.34};
    const double y{23.45};
    const shelter f(x, y);
    assert(std::abs(f.get_x() - x) < 0.00001);
    assert(std::abs(f.get_y() - y) < 0.00001);
  }
  //test that shelter moves with each tick
  {
    shelter f;

    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }
}
