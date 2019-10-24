#include "player.h"
#include "player_shape.h"
#include <cassert>

player::player(const double x, const double y, const player_shape shape)
    : m_x{x}, m_y{y}, m_shape{shape}
{

}

void test_player()
{
  const double x{12.34};
  const double y{23.45};
  const player_shape s{player_shape::rocket};
  const player p(x, y, s);
  assert(p.get_x() == x);
  assert(p.get_y() == y);

  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(p.get_shape()== player_shape::rocket);
  }
  {
    const player p{1.2, 3.4, player_shape::circle};
    assert(p.get_shape() == player_shape::circle);
  }

}

