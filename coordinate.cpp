#include "coordinate.h"
#include <cmath>
#include <cassert>
#include <vector>

coordinate::coordinate(const double x, const double y)
  : m_x{x}, m_y{y}
{
}

double coordinate::get_x() const noexcept { return m_x; }
double coordinate::get_y() const noexcept { return m_y; }

void coordinate::move(const double& direction, const double& speed)
{
  m_x = m_x + cos(direction) * speed;
  m_y = m_y + sin(direction) * speed;
}

void coordinate::reset_coords_to_zero()
{
  m_x = 0;
  m_y = 0;
}

bool coordinate::operator==(coordinate in_coord) {
  return (m_x == in_coord.m_x) && (m_y == in_coord.m_y);
}

bool coordinate::operator!=(coordinate in_coord) {
  return not((m_x == in_coord.m_x) && (m_y == in_coord.m_y));
}

void test_coordinate() {
  // (356) Initial coordinates can be set at construction
 {
    coordinate c{1.23456, 123456.789};
    assert(get_x(c) == 1.23456);
    assert(get_y(c) == 123456.789);
  }

 {
    // (331)
    double x = 1.23456;
    double y = 123456.789;
    coordinate c1{x, y};
    coordinate c2{x, y};
    assert(c1 == c2);
    coordinate c3{x + 1.0, y};
    assert(c1 != c3);
  }

#define FIX_ISSUE_366
#ifdef FIX_ISSUE_366
  {
    coordinate c{0,0};
    ///Test along x axis
    ///When direction is 0 player should
    ///only move along the x axis
    double direction = 0;

    double default_speed = 1;
    c.move(direction);
    double error_x = abs(get_x(c) - default_speed);
    double error_y = abs(get_y(c) - 0);
    assert(error_x < 0.00001);
    assert(error_y < 0.00001);

    std::vector<double> speeds{0.1, 0.5, 2, -0.1, -0.2, -1};
    for(const auto& speed : speeds)
      {
        c.reset_coords_to_zero();
        c.move(direction, speed);
        error_x = abs(get_x(c) - speed);
        error_y = abs(get_y(c) - 0);
        assert(error_x < 0.00001);
        assert(error_y < 0.00001);
      }

    ///Test along y axis
    ///When direction is 0 player should
    ///only move along the y axis
    c.reset_coords_to_zero();
    direction = M_PI / 2;
    c.move(direction);
    error_x = abs(get_x(c) - 0);
    error_y = abs(get_y(c) - default_speed);
    assert(error_x < 0.00001);
    assert(error_y < 0.00001);

    for(const auto& speed : speeds)
      {
        c.reset_coords_to_zero();
        c.move(direction, speed);
        error_x = abs(get_x(c) - 0);
        error_y = abs(get_y(c) - speed);
        assert(error_x < 0.00001);
        assert(error_y < 0.00001);
      }
  }
#endif

//#define FIX_ISSUE_408
#ifdef FIX_ISSUE_408
{
  // Two vectors of coordinates can be checked for strict equality
  const coordinate a{1.0, 1.0};
  const coordinate b{2.0, 1.0};
  const coordinate c{3.0, 1.5};
  const coordinate d{1.0, 0.0};
  const std::vector<coordinate> some_coordinates{a, b, c};
  const std::vector<coordinate> same_coordinates{a, b, c};
  const std::vector<coordinate> other_coordinates{a, b, d};
  const std::vector<coordinate> less_coordinates{a, b};
  const std::vector<coordinate> shuffled_coordinates{b, a, c};

  assert(all_positions_equal(some_coordinates, same_coordinates));
  assert(!all_positions_equal(some_coordinates, other_coordinates));
  assert(!all_positions_equal(some_coordinates, less_coordinates));
  assert(!all_positions_equal(some_coordinates, shuffled_coordinates));
}
#endif
}

