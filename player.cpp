#include "player.h"
#include "player_shape.h"
#include <cassert>
#include <cmath>

player::player(const double x, const double y, const player_shape shape,
               const double player_speed, const double player_max_speed,
               const double player_acceleration,
               const double player_deceleration, const double size,
               const double direction, const double turn_rate,
               const color &any_color)
    : m_color{any_color}, m_x{x}, m_y{y}, m_shape{shape},
      m_player_speed{player_speed}, m_player_max_speed{player_max_speed},
      m_player_acceleration{player_acceleration},
      m_player_deceleration{player_deceleration}, m_size{size},
      m_direction{direction}, m_turn_rate{turn_rate}
{
}

void player::do_action(action_type action)
{

  switch (action)
  {
  case action_type::turn_left:
  {
    turn_left();
    break;
  }
  case action_type::turn_right:
  {
    turn_right();
    break;
  }
  case action_type::accelerate:
  {
    accelerate();
    break;
  }
  case action_type::brake:
  {
    brake();
    break;
  }
  }
}

void player::brake() noexcept
{
  if (m_player_speed > m_player_max_speed)
  {
    m_player_speed = m_player_max_speed;
  }
  else if (m_player_speed >= 0)
  {
    m_player_speed - m_player_deceleration < 0
        ? m_player_speed = 0
        : m_player_speed -= m_player_deceleration;
  }
  else
  {
    m_player_speed = 0;
  }
  update_player_position();
}

void player::accelerate() noexcept
{
  if (m_player_speed < m_player_max_speed)
  {
    m_player_speed += m_player_acceleration;
  }
  else
  {
    m_player_speed = m_player_max_speed;
  }
  update_player_position();
}

int get_blueness(const player& p) noexcept
{
  return p.get_color().get_blue();
}

int get_greenness(const player& p) noexcept
{
  return p.get_color().get_green();
}

int get_redness(const player& p) noexcept
{
  return p.get_color().get_red();
}

void test_player() //!OCLINT tests may be long
{
  // Can default construct a player
  {
    const player p;
    assert(p.get_x() == 0.0);
    assert(p.get_y() == 0.0);
    assert(p.get_shape() == player_shape::rocket); // Or your favorite shape
  }
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
#define FIX_ISSUE_36
#ifdef FIX_ISSUE_36
  // A player starts with 1.0 (that is, 100%) health
  {
    const player p{1.2, 3.4, player_shape::rocket};
    // Health is 100% by default
    assert(std::abs(p.get_health() - 1.0) < 0.00001);
  }
#endif

  // A player has a speed of zero
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_speed() - 0.0) < 0.00001);
  }

  // A player has a direction of zero radians
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_direction() - 0.0) < 0.00001);
  }

#define FIX_ISSUE_45
#ifdef FIX_ISSUE_45
  // A player has an initial speed of zero
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_speed() - 0.0) < 0.00001);
  }
#endif
  // A player has a max_speed of 2(arbitrary value for now)
  {
    const player p;
    assert(p.get_max_s() - 2 < 0.000000000001);
  }
  // A player has a default acceleration of 0.1 per frame
  {
    const player p;
    assert(p.get_acceleration() - 0.1 < 0.00000000001);
  }
  // A player has an initial size of one hundred
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_size() - 100.0) < 0.00001);
  }
  // A player can update its position
  {
    player p;
    // with intial position only x will change since sin of 0 is 0
    double a_x = p.get_x();
    double a_y = p.get_y();
    p.accelerate(); // move the player
    double b_x = p.get_x();
    double b_y = p.get_y();
    assert(std::abs(a_x - b_x) > 0.0000001);
    assert(std::abs(a_y - b_y) < 0.0000001);
  }
  {
    player p;
    p.turn_left();
    // change direction a little bit
    // otherwise default direction would not show
    // a change in y
    double a_x = p.get_x();
    double a_y = p.get_y();
    p.accelerate(); // move the player
    double b_x = p.get_x();
    double b_y = p.get_y();
    assert(std::abs(a_x - b_x) > 0.0000001);
    assert(std::abs(a_y - b_y) > 0.0000001);
  }
  {
    player p;
    assert(p.get_color().get_blue() >= 0);
  }
}
