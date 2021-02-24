#include "food.h"
#include <cassert>
#include <cmath>
#include <sstream>

food::food(const double x, const double y, const color &c)
    : f_x{x}, f_y{y}, m_color{c}
{
}

double food::get_x() const noexcept { return f_x; }
double food::get_y() const noexcept { return f_y; }

void test_food()
{

  {
    food f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }

  {
    food f{1.0,2.0};
    assert(f.get_x() == 1.0);
    assert(f.get_y() == 2.0);
  }

  // X and Y work as expected
  {
    const double x{12.34};
    const double y{23.45};
    const food f(x, y);
    assert(std::abs(f.get_x() - x) < 0.00001);
    assert(std::abs(f.get_y() - y) < 0.00001);
  }
  //#define FIX_ISSUE_206
  #ifdef FIX_ISSUE_206
  {
    const food f(3.14, 2.71);
    std::stringstream s;
    s << f;
    assert(!s.str().empty());
  }
  #endif // FIX_ISSUE_206
}
