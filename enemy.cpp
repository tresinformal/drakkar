#include "enemy.h"
#include "coordinate.h"
#include <cassert>
#include <sstream>

enemy::enemy(const coordinate c)
  : m_coordinate{c}
{
}

std::stringstream& operator << (std::stringstream &out, const enemy &enemy)
{
    out << "Enemy(" << std::to_string(enemy.get_x()) <<
           ", " << std::to_string(enemy.get_y()) <<
           ")";

    return out;
}

bool operator==(const enemy& lhs, const enemy& rhs) noexcept
{
    return lhs.get_x() == rhs.get_x()
           && lhs.get_y() == rhs.get_y();
}

void test_enemy()
{
  #ifndef NDEBUG // no tests is release
  {
    const enemy e;
    assert(e.get_x() == 0.0);
    assert(e.get_y() == 0.0);
  }

  {
    const double x = 0.1;
    const double y = 0.3;
    const coordinate c{x, y};
    const enemy e{c};
    assert(e.get_x() - x < 0.000001);
    assert(e.get_y() - y < 0.000001);
  }
  //#define FIX_ISSUE_345
  #ifdef FIX_ISSUE_345
  {
    const enemy e{1.2, 3.4};
    const enemy f{1.2, 3.4};
    assert(e == f);
  }
  #endif

  {
    std::stringstream s;
    const enemy e;
    s << e;
  }
    #define FIX_ISSUE_328
    #ifdef FIX_ISSUE_328
    {
      coordinate some_random_point(1.0, 1.0);
      enemy n_enemy(some_random_point);
      assert(n_enemy.get_position() == some_random_point);
    }
    #endif
#endif
}
