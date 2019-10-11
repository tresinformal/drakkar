#include "player.h"
#include <cassert>

player::player(const double x, const double y)
  : m_x{x}, m_y{y}
{

}

void test_player()
{
  const double x{12.34};
  const double y{23.45};
  const player p(x, y);
  assert(p.get_x() == x);
  assert(p.get_y() == y);
}
