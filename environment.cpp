#include "environment.h"
#include <cassert>
#include <sstream>

environment::environment(double wall_short_side, environment_type enviroment_type) :
  m_wall_short_side{wall_short_side},
  m_wall_long_side{wall_short_side * 16 / 9},
  m_max_x{m_wall_long_side},
  m_min_x{0},
  m_max_y{m_wall_short_side},
  m_min_y{0},
  m_environment_type{enviroment_type}


{
}

std::ostream &operator<<(std::ostream &os, const environment& e)
{
  os << "Max X : " << e.get_max_x()
     << "Max Y : " << e.get_max_y()
     << "Min X : " << e.get_min_x()
     << "Min X : " << e.get_min_y()
     << "Type : " << e.get_type()
     << "Wall L Side : " << e.get_wall_l_side()
     << "Wall S Side : " << e.get_wall_s_side();

  return os;
}

void test_environment()
{
  // Minimal and maximal coordinats should make sense
  {
    const environment e;
    assert(e.get_min_x() < e.get_max_x());
    assert(e.get_min_y() < e.get_max_y());
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
  #define FIX_ISSUE_204
  #ifdef FIX_ISSUE_204
  {
    const environment e;
    std::stringstream s;
    s << e;
    assert(!s.str().empty());
  }
  #endif // FIX_ISSUE_204
}
