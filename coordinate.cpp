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
  #endif // FIX_ISSUE_356
}

