#include "player.h"
#include "player_shape.h"
#include <cassert>
#include <cmath>

player::player(const double x, const double y, const player_shape shape, const double size)
    : m_x{x}, m_y{y}, m_shape{shape}, m_size{size}
{

}

void test_player() //!OCLINT tests may be long
{
  #ifdef FIX_ISSUE_35
  // Can default construct a player
  {
    const player p;
    assert(p.get_x() == 0.0);
    assert(p.get_y() == 0.0);
    assert(p.get_shape() == player_shape::rocket); //Or your favorite shape
  }
  #endif
  // A player has the same coordinats as set at construction
  {
    const double x{12.34};
    const double y{23.45};
    const player_shape s{player_shape::rocket};
    const player p(x, y, s);
    // Must be the same
    assert(std::abs(p.get_x() - x) < 0.00001);
    assert(std::abs(p.get_y() - y) < 0.00001);
  }
  // A player constructed with a rocket shape, must have a rocket shape
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(p.get_shape() == player_shape::rocket);
  }
  // A player constructed with a circle shape, must have a circle shape
  {
    const player p{1.2, 3.4, player_shape::circle};
    assert(p.get_shape() == player_shape::circle);
  }
  #ifdef FIX_ISSUE_36
  // A player starts with 1.0 (that is, 100%) health
  {
    const player p{1.2, 3.4, player_shape::rocket};
    // Health is 100% by default
    assert(std::abs(p.get_health() - 1.0) < 0.00001);
  }
  #endif
  #ifdef FIX_ISSUE_44
  // A player has a direction of zero radians
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_direction() - 0.0) < 0.00001);
  }
  #endif
  #ifdef FIX_ISSUE_45
  // A player has a speed of zero
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_speed() - 0.0) < 0.00001);
  }
  #endif

  // A player has an initial size of one hundred
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_size() - 100.0) < 0.00001);
  }
}

