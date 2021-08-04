#include "coordinate.h"

coordinate::coordinate(){}

bool coordinate::operator==(coordinate in_coord) {
    return (m_x == in_coord.m_x) && (m_y == in_coord.m_y);
}

bool coordinate::operator!=(coordinate in_coord) {
    return not((m_x == in_coord.m_x) && (m_y == in_coord.m_y));
}

void test_coordinate() {
  // Initial coordinates can be set at construction
  // #define FIX_ISSUE_356
  #ifdef FIX_ISSUE_356
  {

  }
  #endif // FIX_ISSUE_356
}

