#include "shelter.h"
#include <cassert>
#include <cmath>

shelter::shelter(const double x, const double y, const double radius,
                 const color &c, const double shelter_speed, const double direction)
    : m_color{c}, m_radius{radius}, m_x{x}, m_y{y},m_speed {shelter_speed},
      m_direction{direction}
{
}

const color& shelter::get_color() const noexcept
{
  return m_color;
}

double shelter::get_radius() const noexcept
{
  return m_radius;
}

double shelter::get_x() const noexcept
{
  return m_x;
}

double shelter::get_y() const noexcept
{
  return m_y;
}

void shelter::update_shelter_position()
{
  m_x += std::cos(rand());
  m_y += std::sin(rand());
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
    f.update_shelter_position();
    f.update_shelter_position(); //move shelter
    assert(f.get_x() != 0.0); //see that shelter moves
  }
  // Colors
  {
    const int r{1};
    const int g{2};
    const int b{3};
    const int a{4};
    const color c(r, g, b, a);
    const shelter s(0.0, 0.0, 100.0, c);
    assert(get_blueness(s) == b);
    assert(get_greenness(s) == g);
    assert(get_opaqueness(s) == a);
    assert(get_redness(s) == r);
  }
}
