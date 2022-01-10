#include "environment.h"
#include <cassert>
#include <sstream>

environment::environment(double wall_short_side, environment_type environment_type) :
  m_wall_short_side{wall_short_side},
  m_wall_long_side{wall_short_side * 16 / 9},
  m_top_left_position{coordinate(0, 0)},
  m_bottom_right_position{coordinate(m_wall_long_side, m_wall_short_side)},
  m_environment_type{environment_type}
{
}

double get_max_x(const environment& e)
{
  return e.get_bottom_right().get_x();
}

double get_max_y(const environment& e)
{
  return e.get_bottom_right().get_y();
}

double get_min_x(const environment& e)
{
  return e.get_top_left().get_x();
}

double get_min_y(const environment& e)
{
  return e.get_top_left().get_y();
}

std::ostream &operator<<(std::ostream &os, const environment& e)
{
  os << "Max X : " << get_max_x(e)
     << "Max Y : " << get_max_y(e)
     << "Min X : " << get_min_x(e)
     << "Min X : " << get_min_y(e)
     << "Type : " << e.get_type()
     << "Wall L Side : " << e.get_wall_l_side()
     << "Wall S Side : " << e.get_wall_s_side();

  return os;
}

void test_environment()
{
  #ifndef NDEBUG // no tests is release
  // Minimal and maximal coordinats should make sense
  {
    const environment e;
    assert(get_min_x(e) < get_max_x(e));
    assert(get_min_y(e) < get_max_y(e));
  }

  // An environment has a type
  {
    const environment e;
    assert(e.get_type() == environment_type::empty);
    const environment e1( 720, environment_type::quiet);
    assert(e1.get_type() == environment_type::quiet);
  }
  //An environment is initialized with walls, the walls form a 16:9
  //rectangle with center at coordinates of 0,0
  //And short size = 760 by default;
  {
    auto wall_short_side = 760.0;
    environment e(wall_short_side);
    assert(e.get_wall_s_side() - wall_short_side < 0.00001 &&
           e.get_wall_s_side() - wall_short_side > -0.00001);
  }

#define FIX_ISSUE_424
#ifdef FIX_ISSUE_424
    {
        environment e;
        coordinate top_left = e.get_top_left();
        coordinate bottom_right = e.get_bottom_right();
        assert(top_left == coordinate(0,0));
        assert(bottom_right == coordinate(e.get_wall_l_side() + top_left.get_x(), e.get_wall_s_side() + top_left.get_y()));
    }
#endif

  #define FIX_ISSUE_204
  #ifdef FIX_ISSUE_204
  {
    const environment e;
    std::stringstream s;
    s << e;
    assert(!s.str().empty());
  }
  #endif // FIX_ISSUE_204

#endif // no tests in release
}
