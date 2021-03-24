#include "player.h"
#include "player_shape.h"
#include "player_state.h"
#include <cassert>
#include <cmath>

player::player(const double x,
               const double y,
               const player_shape shape,
               const player_state state,
               const double player_max_speed,
               const double player_acceleration,
               const double player_deceleration,
               const double player_acc_backward,
               const double size,
               const double turn_rate,
               const color &any_color,
               const std::string& ID)
  : m_color{any_color},
    m_ID{ID},
    m_x{x},
    m_y{y},
    m_shape{shape},
    m_state{state},
    m_player_max_speed{player_max_speed},
    m_player_acceleration{player_acceleration},
    m_player_deceleration{player_deceleration},
    m_player_acc_backward{player_acc_backward},
    m_diameter{size},
    m_turn_rate{turn_rate}
{
}

/// Get the X coordinate of the player
double player::get_x() const noexcept { return m_x; }

/// Get the Y coordinate of the player
double player::get_y() const noexcept { return m_y; }

/// Get the radius of the player
double player::get_diameter() const noexcept { return m_diameter; }

/// Get the direction of player movement, in radians
double player::get_direction() const noexcept { return m_direction_radians; }

void player::brake() noexcept
{

  if(m_player_speed > 0.0)
    {
      m_player_speed += m_player_deceleration;
    }
  else if(m_player_speed < 0.0)
    {
      m_player_speed -= m_player_deceleration;
    }
  else
    {
      return;
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

void player::acc_backward() noexcept
{
  if (m_player_speed < -m_player_max_speed)
    {
      m_player_speed = -m_player_max_speed;
    }
  else
    {
      m_player_speed = -m_player_max_speed;
    }
  update_player_position();
}

void add_action(player& p, action_type action) noexcept
{
  p.get_action_set().insert(action);
}

bool are_colliding(const player &lhs, const player &rhs) noexcept
{
  const double dx = std::abs(lhs.get_x() - rhs.get_x());
  const double dy = std::abs(lhs.get_y() - rhs.get_y());
  const double actual_distance = std::sqrt((dx * dx) + (dy * dy));
  const double collision_distance = (lhs.get_diameter() + rhs.get_diameter()) / 2;
  return actual_distance < collision_distance;
}
int get_blueness(const player &p) noexcept { return p.get_color().get_blue(); }

int get_greenness(const player &p) noexcept
{
  return p.get_color().get_green();
}

int get_redness(const player &p) noexcept { return p.get_color().get_red(); }

bool is_blue(const player &p) noexcept
{
  assert(p.get_color().get_red() == 0 || p.get_color().get_red() == 255);
  assert(p.get_color().get_green() == 0 || p.get_color().get_green() == 255);
  assert(p.get_color().get_blue() == 0 || p.get_color().get_blue() == 255);
  return p.get_color().get_red() == 0
      && p.get_color().get_green() == 0
      && p.get_color().get_blue() == 255
      ;
}

bool is_green(const player &p) noexcept
{
  assert(p.get_color().get_red() == 0 || p.get_color().get_red() == 255);
  assert(p.get_color().get_green() == 0 || p.get_color().get_green() == 255);
  assert(p.get_color().get_blue() == 0 || p.get_color().get_blue() == 255);
  return p.get_color().get_red() == 0
      && p.get_color().get_green() == 255
      && p.get_color().get_blue() == 0
      ;
}

bool is_red(const player & p) noexcept
{
  assert(p.get_color().get_red() == 0 || p.get_color().get_red() == 255);
  assert(p.get_color().get_green() == 0 || p.get_color().get_green() == 255);
  assert(p.get_color().get_blue() == 0 || p.get_color().get_blue() == 255);
  return p.get_color().get_red() == 255
      && p.get_color().get_green() == 0
      && p.get_color().get_blue() == 0
      ;
}

void stun(player &p) noexcept
{
    p.set_state(player_state::stunned);
}

bool is_alive(const player& p) noexcept
{
  return !is_dead(p);
}

bool is_active(const player & p) noexcept
{
    return p.get_state() == player_state::active;
}

bool is_dead(const player& p) noexcept
{
  return p.get_state() == player_state::dead;
}

bool is_stunned(const player & p) noexcept
{
    return p.get_state() == player_state::stunned;
}

int get_colorhash(const player &p) noexcept
{
  assert(p.get_color().get_red() == 0 || p.get_color().get_red() == 255);
  assert(p.get_color().get_green() == 0 || p.get_color().get_green() == 255);
  assert(p.get_color().get_blue() == 0 || p.get_color().get_blue() == 255);

  //1 is red, 2 is blue, 3 is green
  if(p.get_color().get_red() == 255)
    return 0;
  if(p.get_color().get_green() == 255)
    return 1;
  assert(p.get_color().get_blue() == 255);
  return 2;
}
void remove_action(player& p, action_type action) noexcept
{
  p.get_action_set().erase(action);
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

  // A player has an initial speed of zero
  {
    const player p{1.2, 3.4, player_shape::rocket};
    assert(std::abs(p.get_speed() - 0.0) < 0.00001);
  }

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
    assert(std::abs(p.get_diameter() - 100.0) < 0.00001);
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
  // A player can shoot
  {
    player p;
    p.shoot();
    assert(p.is_shooting());
  }
  // A player can stop shooting
  {
    player p;
    p.shoot();
    assert(p.is_shooting());
    p.stop_shooting();
    assert(!p.is_shooting());
  }
  // two players(assuming they are not rotated) collide when they are less than
  // their size away
  {
    const player p1(0.0, 0.0);
    assert(p1.get_diameter() == 100.0);
    // So, 90 pixels is a collision then
    const player p2(90.0, 0.0);
    assert(are_colliding(p1, p2));
  }
  // A player of RGB values (255, 0, 0) should be red, not green, not blue
  {
    player p;
    p.set_color(color(255, 0, 0));
    assert(is_red(p));
    assert(!is_green(p));
    assert(!is_blue(p));
  }
  // A player of RGB values (0, 255, 0) should be green, not red, not blue
  {
    player p;
    p.set_color(color(0, 255, 0));
    assert(!is_red(p));
    assert(is_green(p));
    assert(!is_blue(p));

  }
  // A player of RGB values (0, 0, 255) should be blue, not red, not green
  {
    player p;
    p.set_color(color(0, 0, 255));
    assert(!is_red(p));
    assert(!is_green(p));
    assert(is_blue(p));

  }
  //A player with RGB values (255, 0, 0) should be red with colorhash1 ,not 2 or 3
  {
    //0 is red, 1 is blue, 2 is green
    player p;
    p.set_color(color(255, 0, 0));
    assert(get_colorhash(p)==0);
    assert(get_colorhash(p)!=1);
    assert(get_colorhash(p)!=2);
  }
  //A player with RGB values (0,255, 0) should be blue with colorhash2 ,not 1 or 3
  {
    //0 is red, 1 is blue, 2 is green
    player p;
    p.set_color(color(0, 255, 0));
    assert(get_colorhash(p)!=0);
    assert(get_colorhash(p)==1);
    assert(get_colorhash(p)!=2);
  }
  //A player with RGB values ( 0, 0, 255) should be green with colorhash3 ,not 1 or 2
  {
    //0 is red, 1 is blue, 2 is green
    player p;
    p.set_color(color(0, 0, 255));
    assert(get_colorhash(p)!=0);
    assert(get_colorhash(p)!=1);
    assert(get_colorhash(p)==2);
  }
  //A player is initialized with an empty action set
  {
    player p;
    assert(p.get_action_set().empty());
  }

  //A player can add an action to its action set
  {
    player p;
    auto action = action_type::none;
    assert(p.get_action_set().empty());
    add_action(p, action);
    assert(!p.get_action_set().empty());
    assert(p.get_action_set().size() == 1);
    //Check there is at least one element of the specified key
    assert(p.get_action_set().count(action));
  }

  //A player can erase an action from its action set and keep the others
  {
    player p;
    auto action1 = action_type::none;
    auto action2 = action_type::brake;
    add_action(p, action1);
    add_action(p, action2);
    assert(!p.get_action_set().empty());
    assert(p.get_action_set().count(action1));
    assert(p.get_action_set().count(action2));
    remove_action(p, action1);
    assert(!p.get_action_set().count(action1));
    assert(p.get_action_set().count(action2));
  }
  // A player increases its speed by one 'acceleration' per acceleration
  {
      // RJCB: I see the point you try to make here:
      // this is a prelude to the next test.
      // I suggest to merge the two tests into one
      player p;
      p.accelerate();
      assert(p.get_speed() - p.get_acceleration() < 0.00000000001);
  }

  // A player increases its backward speed by one 'backward acceleration' per backward acceleration
  // or: a player decreases its speed by one 'backward acceleration' per backward acceleration
  {
      player p;
      p.acc_backward();
      // RJCB: I would prefer a
      // stdd::abs(p.get_speed() - p.get_acceleration_backward())
      // to show this is about a difference between twee values
      assert(p.get_speed() - p.get_acceleration_backward() < 0.00000000001);
  }
  // A players speed after one 'acceleration' is less than max_speed
  {
      player p;
      p.accelerate();
      assert(p.get_speed() < p.get_max_s());
  }
  // A players speed after one 'backward acceleration' is more than negative max_speed
  {
      player p;
      p.acc_backward();
      assert(p.get_speed() > -p.get_max_s());
  }
  //#define FIX_ISSUE_193
  #ifdef FIX_ISSUE_193
  // RJCB: my suggested test
  // A players goes ?right/?up upon acceleraton
  {
      player p_forward;
      p_forward.accelerate();
      assert(get_dx(p_forward) > 0.0); // Get the delta x, maybe needs to be added
      assert(get_dy(p_forward) > 0.0); // Get the delta x, maybe needs to be added
      player p_backward;
      p_backward.acc_backward();
      assert(get_dx(p_backward) < 0.0); // Signs should flip
      assert(get_dy(p_backward) < 0.0); // Signs should flip
  }
  // RJCB: another suggested test
  // A players actually goes backwards after some backwards accelerations
  {
      player p;
      p.accelerate();
      assert(get_dx(p) > 0.0); // Get the delta x, maybe needs to be added
      assert(get_dy(p) > 0.0); // Get the delta x, maybe needs to be added
      p.acc_backward();
      p.acc_backward();
      p.acc_backward();
      assert(get_dx(p) < 0.0); // Signs should flip
      assert(get_dy(p) < 0.0); // Signs should flip
  }
#endif
  //When a player is standing still,
  //braking will do nothing
  //counteract it by increasing its speed
  {
    player p;
    assert(p.get_speed() == 0.0);
    p.brake();
    assert(p.get_speed() == 0.0);
  }

  //When a player is accelerating backwards brake will
  //counteract it by increasing its speed
  {
    player p;
    p.acc_backward();
    auto full_back_speed = p.get_speed();
    assert (full_back_speed < 0);
    p.brake();
    auto brake_back_speed = p.get_speed();
    assert(brake_back_speed > full_back_speed);
  }

  //A player cannot surpass its positive max_speed
  {
    player p;
    int n_of_accelerations = 1000;
    assert(p.get_acceleration() * n_of_accelerations > p.get_max_s());
    for(int i = 0; i != n_of_accelerations; i++ )
      {
        p.accelerate();
      }
    assert(p.get_speed() - p.get_max_s() < 0.00001
           && p.get_speed() - p.get_max_s() > -0.00001);
  }

  //A player cannot surpass its negative max_speed
  {
    player p;
    int n_of_accelerations = 1000;
    assert(p.get_acceleration_backward() * n_of_accelerations < -p.get_max_s());
    for(int i = 0; i != n_of_accelerations; i++ )
    {
      p.acc_backward();
      auto full_back_speed = p.get_speed();
      assert (full_back_speed < 0);
      p.brake();
      auto brake_back_speed = p.get_speed();
      assert(brake_back_speed > full_back_speed);
    }
  }
    //A player cannot surpass its positive max_speed
  {
        player p;
        int n_of_accelerations = 1000;
        assert(p.get_acceleration() * n_of_accelerations > p.get_max_s());
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            p.accelerate();
        }
        assert(p.get_speed() - p.get_max_s() < 0.00001
               && p.get_speed() - p.get_max_s() > -0.00001);
  }

  //A player cannot surpass its negative max_speed
  {
        player p;
        int n_of_accelerations = 1000;
        assert(p.get_acceleration_backward() * n_of_accelerations < -p.get_max_s());
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            p.acc_backward();
        }

        assert(p.get_speed() + p.get_max_s() < 0.00001
               && p.get_speed() + p.get_max_s() > -0.00001);
  }

  //It is possible to establish how bluish, reddish and greenish a player is
  {
        player p;
        int blueness = 1;
        int greenness = 1;
        int redness = 1;
        p.set_color(
                    color{redness,
                          greenness,
                          blueness}
                    );
        assert(get_blueness(p) == blueness);
        assert(get_redness(p) == redness);
        assert(get_greenness(p) == greenness);
  }
  ///A player has an ID
  {
        std::string ID = "1";
        player p;
        p.set_ID(ID);
        assert(p.get_ID() == ID);
  }
  //A player is by default initiated with state == "active
  {
       const player p{};
       assert(p.get_state() == player_state::active);
   }

#ifdef FIX_ISSUE_193
   // A player object can be initialized to a stunned state
   {
       const player p{1.2, 3.4, player_shape::circle, player_state::stunned};
       assert(p.get_state() ==  player_state::stunned);
       assert(p.get_state() !=  player_state::active);
    assert(p.get_speed() + p.get_max_s() < 0.00001
           && p.get_speed() + p.get_max_s() > -0.00001);
  }
#endif
  //It is possible to establish how bluish, reddish and greenish a player is
  {
    player p;
    int blueness = 1;
    int greenness = 1;
    int redness = 1;
    p.set_color(
          color{redness,
                greenness,
                blueness}
          );
    assert(get_blueness(p) == blueness);
    assert(get_redness(p) == redness);
    assert(get_greenness(p) == greenness);
  }

  ///A player has an ID
  {
    std::string ID = "1";
    player p;
    p.set_ID(ID);
    assert(p.get_ID() == ID);
  }

#ifdef FIX_ISSUE_220
  ///A player can become stunned
  {
    player p;
    assert(is_active(p));
    stun(p);
    assert(is_stunned(p));
  }
#endif
}
