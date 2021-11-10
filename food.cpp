#include "coordinate.h"
#include "food.h"
#include <cassert>
#include <cmath>
#include <sstream>

food::food(const coordinate c, const color &col, const int regeneration_time, food_state food_state, double radius)
  : m_c{c}, m_color{col}, m_regeneration_time{regeneration_time}, m_food_state{food_state}, m_radius{radius}
{
}

double food::get_x() const noexcept { return m_c.get_x(); }
double food::get_y() const noexcept { return m_c.get_y(); }
double food::get_radius() const noexcept {return m_radius;}
std::ostream &operator<<(std::ostream &os, const food f)
{
  os << "x : "<<f.get_x()<<
        "y : "<<f.get_y();
  return os;
}

bool food::is_eaten() const noexcept {
    if (food::get_food_state() == food_state::eaten) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const food& lhs, const food& rhs) noexcept
{
    return lhs.get_x() == rhs.get_x()
            && lhs.get_y() == rhs.get_y() ;
}

void food::increment_timer()
{
  ++m_timer;
}

void food::reset_timer()
{
  m_timer = 0;
}

void test_food()
{
  #ifndef NDEBUG // no tests in release
  {
    const food f;
    assert(f.get_x() == 2000.0);
    assert(f.get_y() == 1000.0);
  }

  //foods that are on the same coordinate point but with different colour Are equal, when this is not true
  {
    const food a;
    const food b;
    const food c(coordinate(1234.5678, 0));
    assert(a == b);
    assert(!(a == c));
  }
  //#define FIX_ISSUE_349
  #ifdef FIX_ISSUE_349
  //Can compare two foods for inequality, operator!=
  {
    coordinate c_a(1.2, 0);
    coordinate c_b(3.4, 0);
    const food a(c_a);
    const food b(c_b);
    assert(a != b);
  }
  #endif // FIX_ISSUE_349

    //#define FIX_ISSUE_341
    #ifdef FIX_ISSUE_341
    {
      coordinate c(0.0f, 0.0f);
      const food test_food_one(c, color());
      const food test_food_two(c, color(0, 0, 0));
      assert(not (test_food_one == test_food_two));
    }
    #endif
    #define FIX_ISSUE_329
    #ifdef FIX_ISSUE_329
    {
      coordinate some_random_point(1, 1);
      food n_food(some_random_point);
      assert(n_food.get_position() == some_random_point);
    }
    #endif

  {
    coordinate c(1.0, 2.0);
    food f{c};
    assert(f.get_x() == 1.0);
    assert(f.get_y() == 2.0);
  }

  // X and Y work as expected
  {
    const coordinate c(12.34, 23.45);
    const food f(c);
    assert(std::abs(f.get_x() - c.get_x()) < 0.00001);
    assert(std::abs(f.get_y() - c.get_y()) < 0.00001);
  }

  {
    const coordinate c(3.14, 2.71);
    const food f(c);
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
    assert(f.get_regeneration_time() == 100);
  }

  //A food has a regeneration time
  {
    food f;
    assert(f.get_regeneration_time() || !f.get_regeneration_time());
  }
  //A food has a regeneration time member that can be initialized, by default == 10
  {
    const int regeneration_time = 31415;
    const coordinate c(0, 0);
    const food f{c, color(), regeneration_time};
    assert(f.get_regeneration_time() == regeneration_time);
  }
//   A food has a radius member
  #define FIX_ISSUE_389
  #ifdef FIX_ISSUE_389
  {
    const food f;
    assert(f.get_radius() >= 0.0);
  }
  #endif
#endif // no tests in release
}

