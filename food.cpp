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
  os << "x : "<< get_x(f)<<
        "y : "<< get_y(f);
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
    bool is_color_equal = lhs.get_color() == rhs.get_color();

    return get_x(lhs) == get_x(rhs) &&
          get_y(lhs) == get_y(rhs) &&

           is_color_equal;
}

bool operator!=(const food& lhs, const food& rhs) noexcept
{
    return !(lhs == rhs);
}


void food::place_randomly(std::mt19937 &rng, const coordinate& top_left, const coordinate& bottom_right)
{
  std::uniform_real_distribution<> dis_x(top_left.get_x(), bottom_right.get_x());
  std::uniform_real_distribution<> dis_y(top_left.get_y(), bottom_right.get_y());
  m_c = coordinate(dis_x(rng), dis_y(rng));
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
    assert(get_x(f) == 2000.0);
    assert(get_y(f) == 1000.0);
  }

  //foods that are on the same coordinate point but with different colour Are equal, when this is not true
  {
    const food a;
    const food b;
    const food c(coordinate(1234.5678, 0));
    assert(a == b);
    assert(!(a == c));
  }

  //Can compare two foods for inequality, operator!= #349
  {
    coordinate c_a(1.2, 0);
    coordinate c_b(3.4, 0);
    const food a(c_a);
    const food b(c_b);
    assert(a != b);
  }
    {
    // (341)

      coordinate c(0.0f, 0.0f);
      const food test_food_one(c, color());
      const food test_food_two(c, color(0, 0, 0));
      assert(test_food_one != test_food_two);
    }
    {
      // 329
      coordinate some_random_point(1, 1);
      food n_food(some_random_point);
      assert(n_food.get_position() == some_random_point);
    }

  {
    coordinate c(1.0, 2.0);
    food f{c};
    assert(get_x(f) == 1.0);
    assert(get_y(f) == 2.0);
  }

  // X and Y work as expected
  {
    const coordinate c(12.34, 23.45);
    const food f(c);
    assert(std::abs(get_x(f) - get_x(c)) < 0.00001);
    assert(std::abs(get_y(f) - get_y(c)) < 0.00001);
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

  {
    // (260)
    food f; //by default uneaten
    assert(!f.is_eaten());
  }

  // Food has a regeneration timer member, set to 0 by default
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
// (389) A food has a radius member
  {
    const food f;
    assert(f.get_radius() >= 0.0);
  }
#endif // no tests in release
}

