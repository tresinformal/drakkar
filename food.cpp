  #include "food.h"
#include <cassert>
#include <cmath>
#include <sstream>

food::food(const double x, const double y, const color &c, const double timer, food_state food_state)
    : m_x{x}, m_y{y}, m_color{c},m_timer{timer},m_food_state{food_state}
{
}

double food::get_x() const noexcept { return m_x; }
double food::get_y() const noexcept { return m_y; }

std::ostream &operator<<(std::ostream &os, const food f)
{
  os << "x : "<<f.get_x()<<
        "y : "<<f.get_y();
  return os;
}

bool is_eaten(const food &f) noexcept {
    if (f.food_state == eaten) {};
};


void test_food()
{
  #ifndef NDEBUG // no tests in release
  {
    const food f;
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

  {
    const food f(3.14, 2.71);
    std::stringstream s;
    s << f;
    assert(!s.str().empty());
  }

  //A food has a food_state member initialized to ::uneaten by default
  {
    food f;
    assert(f.get_food_state() == food_state::uneaten);
  }

//#ifdef FIX_ISSUE_260
  {
    food f; //by default uneaten
    assert(!f.is_eaten());
  }
//#endif

  //Food has a regeneration timer member, set to 0 by default
  {
    food f;
    assert(f.get_timer_regeneration() == 0.0);
  }

#ifdef FIX_ISSUE_258a
  //A food has a regeneration time
  {
    food f;
    assert(f.get_regeneration_time() || !f.get_regeneration_time());
  }
#endif

#ifdef FIX_ISSUE_258b
  //A food has a regeneration time member that cna be initialized, by default == 10
  {
    const int regeneration_time = 31415;
    const food f2{0,0,color(), regeneration_time};
    assert(f.get_regeneration_time() == regeneration_time);
  }
#endif
#endif // no tests in release
}


