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
    out << "Enemy at" << enemy.get_position();
    return out;
}

bool operator==(const enemy& lhs, const enemy& rhs) noexcept
{
    return get_x(lhs) == get_x(rhs)
           && get_y(lhs) == get_y(rhs);
}

void test_enemy()
{
  #ifndef NDEBUG // no tests is release
  {
    const enemy e;
    assert(get_x(e) == 0.0);
    assert(get_y(e) == 0.0);
  }

  {
    const double x = 0.1;
    const double y = 0.3;
    const coordinate c{x, y};
    const enemy e{c};
    assert(get_x(e) - x < 0.000001);
    assert(get_y(e) - y < 0.000001);
  }
  {
    // (345)

    auto coord = coordinate{1.2, 3.4};
    const enemy e{coord};
    const enemy f{coord};
    assert(e == f);
  }

  {
    std::stringstream s;
    const enemy e;
    s << e;
  }
    {
      // (328)

      coordinate some_random_point(1.0, 1.0);
      enemy n_enemy(some_random_point);
      assert(n_enemy.get_position() == some_random_point);
    }
#endif
}
