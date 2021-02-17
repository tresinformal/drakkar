#include "enemy.h"
#include <cassert>
#include <sstream>

void test_enemy()
{
  {
    enemy e;
    assert(e.get_x() == 0.0);
    assert(e.get_y() == 0.0);
  }

  {
    const double x = 0.1;
    const double y = 0.3;
    const enemy e{x, y};
    assert(e.get_x() - x < 0.000001);
    assert(e.get_y() - y < 0.000001);
  }
  //#define FIX_ISSUE_200
  #ifdef FIX_ISSUE_200
  // operator==
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
}

enemy::enemy(const double x, const double y) : m_x{x}, m_y{y} {}

std::stringstream& operator << (std::stringstream &out, const enemy &enemy)
{
    out << "Enemy(" << std::to_string(enemy.get_x()) <<
           ", " << std::to_string(enemy.get_y()) <<
           ")";

    return out;
}
