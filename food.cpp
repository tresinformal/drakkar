#include "food.h"
#include <cassert>
#include <cmath>
#include <sstream>

food::food(const double x, const double y, const color &c, const double timer, food_state food_state)
    : m_x{x}, m_y{y}, m_color{c},m_regeneration_time{timer},m_food_state{food_state}
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

void test_food()
{
  #ifndef NDEBUG // no tests in release
  {
    const food f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }

  //foods that are on the same coordinate point but with different colour Are equal, when this is not true
  {
    const food a;
    const food b;
    const food c(1234.5678);
    assert(a == b);
    assert(!(a == c));
  }
  //#define FIX_ISSUE_349
  #ifdef FIX_ISSUE_349
  //Can compare two foods for inequality, operator!=
  {
    const food a(1.2);
    const food b(3.4);
    assert(a != b);
  }
  #endif // FIX_ISSUE_349
    //#define FIX_ISSUE_341
    #ifdef FIX_ISSUE_341
    {
      const food test_food_one(0.0f,0.0f,color());
      const food test_food_two(0.0f,0.0f,color(0,0,0));
      assert(not (test_food_one==test_food_two));
    }
    #endif
    //#define FIX_ISSUE_329
    #ifdef FIX_ISSUE_329
    {
      coordinate some_random_point(1,1);
      food n_food(some_random_point);
      assert(food.get_position()==some_random_point);
    }
    #endif


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
    assert(f.get_regeneration_time() == 0.0);
  }

  //A food has a regeneration time
  {
    food f;
    assert(f.get_regeneration_time() || !f.get_regeneration_time());
  }
  //A food has a regeneration time member that can be initialized, by default == 10
  {
    const int regeneration_time = 31415;
    const food f{0,0,color(), regeneration_time};
    assert(f.get_regeneration_time() == regeneration_time);
  }
#endif // no tests in release
}



const std::vector<double> get_position(const food& in_food)
{
    return std::vector<double> {in_food.get_x(),in_food.get_y()};
}
