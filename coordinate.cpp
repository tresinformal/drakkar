#include "coordinate.h"
#include <cassert>

coordinate::coordinate(const double x, const double y)
  : m_x{x}, m_y{y}
{
}

double coordinate::get_x() const noexcept { return m_x; }
double coordinate::get_y() const noexcept { return m_y; }

bool coordinate::operator==(coordinate in_coord) {
    return (m_x == in_coord.m_x) && (m_y == in_coord.m_y);
}

bool coordinate::operator!=(coordinate in_coord) {
    return not((m_x == in_coord.m_x) && (m_y == in_coord.m_y));
}

void test_coordinate() {
  // Initial coordinates can be set at construction
  #define FIX_ISSUE_356
  #ifdef FIX_ISSUE_356
  {
    coordinate c{1.23456, 123456.789};
    assert(c.get_x() == 1.23456);
    assert(c.get_y() == 123456.789);
  }
  #endif

  #define FIX_ISSUE_331
  #ifdef FIX_ISSUE_331
  {
    double x = 1.23456;
    double y = 123456.789;
    coordinate c1{x, y};
    coordinate c2{x, y};
    assert(c1 == c2);
    coordinate c3{x + 1.0, y};
    assert(c1 != c3);
  }
  #endif

//#define FIX_ISSUE_366
#ifdef FIX_ISSUE_366
  {
    coordinate c{0,0};
    double default_speed = 1;
    double direction = 0;
    c.move(direction);
    assert(c.get_x() == default_speed);
    assert(c.get_y() == 0 );

    c.reset_coords_to_zero();
    double speed = 2;
    c.move(direction, speed);
    assert(c.get_x() == speed );
    assert(c.get_y() == 0 );

    c.reset_coords_to_zero();
    double speed = 0.5;
    c.move(direction, speed);
    assert(c.get_x() == speed );
    assert(c.get_y() == 0 );

    c.reset_coords_to_zero();
    double speed = -1;
    c.move(direction, speed);
    assert(c.get_x() == speed );
    assert(c.get_y() == 0 );
  }
#endif
}

