#include "food.h"
#include <cassert>

void test_food()
{

  {
    food f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }

  const double x{12.34};
  const double y{23.45};
  const food f(x, y);
  assert(f.get_x() == x);
  assert(f.get_y() == y);
}

food::food(const double x, const double y) : f_x{x}, f_y{y} {}
