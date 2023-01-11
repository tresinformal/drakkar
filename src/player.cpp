#include "player.h"
#include "player_shape.h"
#include "player_state.h"
#include "game_functions.h"
#include "color.h"
#include <cassert>
#include <cmath>

player::player(const coordinate c,
               const player_shape shape,
               const player_state state,
               const double player_max_speed_forward,
               const double player_max_speed_backward,
               const double player_acceleration_forward,
               const double player_acceleration_backward,
               const double player_deceleration_forward,
               const double player_deceleration_backward,
               const double size,
               const double turn_rate,
               const color &any_color,
               const std::string& ID)
    : m_color{any_color},
      m_ID{ID},
      m_c{c},
      m_shape{shape},
      m_state{state},
      m_player_max_speed_forward{player_max_speed_forward},
      m_player_max_speed_backward{player_max_speed_backward},
      m_player_acceleration_forward{player_acceleration_forward},
      m_player_acceleration_backward{player_acceleration_backward},
      m_player_deceleration_forward{player_deceleration_forward},
      m_player_deceleration_backward{player_deceleration_backward},
      m_diameter{size},
      m_turn_rate{turn_rate}
{

}

//move a player
void player::move() noexcept
{
    double new_x = m_c.get_x() + cos(m_direction_radians) * m_player_speed;
    double new_y = m_c.get_y() + sin(m_direction_radians) * m_player_speed;
    m_c = coordinate(new_x, new_y);
}

/// Get the X coordinate of the player
double player::get_x() const noexcept { return m_c.get_x(); }

/// Get the Y coordinate of the player
double player::get_y() const noexcept { return m_c.get_y(); }

/// Get the radius of the player
double player::get_diameter() const noexcept { return m_diameter; }

/// Make the player grow
void player::grow()
{
  m_diameter *= m_growth_factor;
}

/// Make the player shrink
void player::shrink()
{
  m_diameter /= m_growth_factor;
  if(m_diameter < m_death_size)
  {
     m_state = player_state::dead;
  }
}


/// Get the direction of player movement, in radians
double player::get_direction() const noexcept { return m_direction_radians; }

void player::decelerate() noexcept
{
    if(m_player_speed > 0.0)
    {
        if(m_player_speed >= m_player_deceleration_forward)
        {
            m_player_speed -= m_player_deceleration_forward;
        }
        else
        {
            m_player_speed = 0;
        }
    }
    else if(m_player_speed < 0.0)
    {
        if(std::abs(m_player_speed) >= m_player_deceleration_backward)
        {
            m_player_speed += m_player_deceleration_backward;
        }
        else
        {
            m_player_speed = 0;
        }
    }
    move();
}

void player::accelerate_forward() noexcept
{
    if (m_player_speed < m_player_max_speed_forward)
    {
        m_player_speed += m_player_acceleration_forward;
    }
    else
    {
        m_player_speed = m_player_max_speed_forward;
    }
    move();
}

void player::accelerate_backward() noexcept
{
    if (m_player_speed > m_player_max_speed_backward)
    {
        m_player_speed -= m_player_acceleration_backward;
    }
    else
    {
        m_player_speed = m_player_max_speed_backward;
    }
    move();
}

void add_action(player& p, action_type action) noexcept
{
    p.get_action_set().insert(action);
}

bool are_colliding(const player &lhs, const player &rhs) noexcept
{
  if (lhs.get_state() == player_state::active
     && rhs.get_state() == player_state::active)
  {
    const double dx = std::abs(get_x(lhs) - get_x(rhs));
    const double dy = std::abs(get_y(lhs) - get_y(rhs));
    const double actual_distance = std::sqrt((dx * dx) + (dy * dy));
    const double collision_distance = (lhs.get_diameter() + rhs.get_diameter()) / 2;
    return actual_distance < collision_distance;
  }
  return false;
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

// The player can die
void player::die()
{
  m_state = player_state::dead;
  m_a = 100;

}

// The player can revive
void player::revive()
{
  m_state = player_state::active;
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

player create_player_with_id(const std::string& id)

{
    return player{
                coordinate(0.0, 0.0),
                player_shape::rocket,
                player_state::active,
                1,
                -0.5,
                0.1,
                0.05,
                0.1,
                0.1,
                100.0,
                0.007,
                color(),
                id
                };
}

player create_player_with_color(const color &in_color)
{
    {
        return player{
                    coordinate(0.0, 0.0),
                    player_shape::rocket,
                    player_state::active,
                    1,
                    -0.5,
                    0.1,
                    0.05,
                    0.1,
                    0.1,
                    100.0,
                    0.007,
                    in_color
                    };
    }
}

player create_red_player()
{
    return  create_player_with_color(color(255,0,0));

}
player create_green_player()
{
    return create_player_with_color(color(0,255,0));
}
player create_blue_player()
{
     return create_player_with_color(color(0,0,255));
}

bool is_first_player_loser(const player& player_one, const player& player_two)
{
    if(player_one.get_color()==color(255,0,0))
    {
        if(player_two.get_color()!=color(0,0,255))
            return false;
        else
            return true;
    }
    if(player_one.get_color()==color(0,255,0))
    {
        if(player_two.get_color()!=color(255,0,0))
            return false;
        else
            return true;
    }
    if(player_one.get_color()==color(0,0,255))
    {
        if(player_two.get_color()!=color(0,255,0))
            return false;
        else
            return true;
    }
    return false;
}

bool is_first_player_winner (const player& player_one, const player& player_two)
{
 const color color1 = player_one.get_color();
 const color color2 = player_two.get_color();
 return is_first_color_winner(color1,color2);
}

bool operator==(const player& lhs, const player& rhs) noexcept
{
  return lhs.get_x() == rhs.get_x() &&
         lhs.get_y() == rhs.get_y() &&
         lhs.get_ID() == rhs.get_ID() &&
         lhs.get_color() == rhs.get_color() &&
         lhs.get_shape() == rhs.get_shape() &&
         lhs.get_speed() == rhs.get_speed() &&
         lhs.get_state() == rhs.get_state() &&
         lhs.get_health() == rhs.get_health() &&
         lhs.get_diameter() == rhs.get_diameter() &&
         lhs.get_position() == rhs.get_position() &&
         lhs.get_direction() == rhs.get_direction() &&
         lhs.get_action_set() == rhs.get_action_set() &&
         lhs.get_action_flag() == rhs.get_action_flag() &&
         lhs.get_max_speed_forward() == rhs.get_max_speed_forward() &&
         lhs.get_max_speed_backward() == rhs.get_max_speed_backward() &&
         lhs.get_acceleration_forward() == rhs.get_acceleration_forward() &&
         lhs.get_deceleration_forward() == rhs.get_deceleration_forward() &&
         lhs.get_acceleration_backward() == rhs.get_acceleration_backward() &&
         lhs.get_deceleration_backward() == rhs.get_deceleration_backward();
}

void test_player() //!OCLINT tests may be long
{
#ifndef NDEBUG // no tests in release

  #define FIX_ISSUE_336
  #ifdef FIX_ISSUE_336
    {
        player p;
        coordinate predicted_player_position = predict_players_movement(p);
        p.move();
        assert(p.get_position() == predicted_player_position);
        const double error_x = abs(predicted_player_position.get_x() - get_x(p));
        const double error_y = abs(predicted_player_position.get_y() - get_y(p));
        assert(error_x < 0.001);
        assert(error_y < 0.001);
    }
  #endif

    // Can default construct a player
    {
        const player p;
        assert(get_x(p) == 0.0);
        assert(get_y(p) == 0.0);
        assert(p.get_shape() == player_shape::rocket); // Or your favorite shape
    }

    // (337) A player has the same coordinats as set at construction
    {
        const coordinate c{12.34, 23.45};
        const player_shape s{player_shape::rocket};
        const player p(c, s);
        // Must be the same
        assert(std::abs(get_x(p) - c.get_x()) < 0.00001);
        assert(std::abs(get_y(p) - c.get_y()) < 0.00001);
        assert(p.get_position() == c);
    }

    // A player constructed with a rocket shape, must have a rocket shape
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        assert(p.get_shape() == player_shape::rocket);
    }

    // A player constructed with a circle shape, must have a circle shape
    {
        const player p{coordinate(1.2, 3.4), player_shape::circle};
        assert(p.get_shape() == player_shape::circle);
    }

    // (36) A player starts with 1.0 (that is, 100%) health
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        // Health is 100% by default
        assert(std::abs(p.get_health() - 1.0) < 0.00001);
    }

    // A player has an initial size of one hundred
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        assert(std::abs(p.get_diameter() - 100.0) < 0.00001);
    }

    // two players(assuming they are not rotated) collide when they are less than
    // their size away
    {
        const player p1(coordinate(0.0, 0.0));
        assert(p1.get_diameter() == 100.0);
        // So, 90 pixels is a collision then
        const player p2(coordinate(90.0, 0.0));
        assert(are_colliding(p1, p2));
    }

    // A player of RGB values (255, 0, 0) should be red, not green, not blue
    {
        player p = create_player_with_color(color(255, 0, 0));
        assert(is_red(p));
        assert(!is_green(p));
        assert(!is_blue(p));
    }

    // A player of RGB values (0, 255, 0) should be green, not red, not blue
    {
        player p = create_player_with_color(color(0, 255, 0));
        assert(!is_red(p));
        assert(is_green(p));
        assert(!is_blue(p));

    }

    // A player of RGB values (0, 0, 255) should be blue, not red, not green
    {
        player p = create_player_with_color(color(0, 0, 255));
        assert(!is_red(p));
        assert(!is_green(p));
        assert(is_blue(p));

    }

    //A player with RGB values (255, 0, 0) should be red with colorhash1 ,not 2 or 3
    {
        //0 is red, 1 is blue, 2 is green
        player p = create_player_with_color(color(255, 0, 0));
        assert(get_colorhash(p)==0);
        assert(get_colorhash(p)!=1);
        assert(get_colorhash(p)!=2);
    }

    //A player with RGB values (0,255, 0) should be blue with colorhash2 ,not 1 or 3
    {
        //0 is red, 1 is blue, 2 is green
        player p = create_player_with_color(color(0, 255, 0));
        assert(get_colorhash(p)!=0);
        assert(get_colorhash(p)==1);
        assert(get_colorhash(p)!=2);
    }

    //A player with RGB values ( 0, 0, 255) should be green with colorhash3 ,not 1 or 2
    {
        //0 is red, 1 is blue, 2 is green
        player p = create_player_with_color(color(0, 0, 255));
        assert(get_colorhash(p)!=0);
        assert(get_colorhash(p)!=1);
        assert(get_colorhash(p)==2);
    }

   // (231) The correct player must win
    {
        const player paper = create_red_player();
        const player rock = create_green_player();
        const player scissors = create_blue_player();
        assert(is_first_player_winner(paper, rock));
        assert(is_first_player_winner(scissors, paper));
        assert(is_first_player_winner(rock, scissors));
        assert(!is_first_player_winner(rock, paper));
        assert(!is_first_player_winner(paper, scissors));
        assert(!is_first_player_winner(scissors, rock));
    }

    // (232) The correct player must lose
    {
        const player paper = create_red_player();
        const player rock = create_green_player();
        const player scissors = create_blue_player();
        assert(!is_first_player_loser(paper, rock));
        assert(!is_first_player_loser(scissors, paper));
        assert(!is_first_player_loser(rock, scissors));
        assert(is_first_player_loser(rock, paper));
        assert(is_first_player_loser(paper, scissors));
        assert(is_first_player_loser(scissors, rock));
    }

    //A player is initialized with an empty action set
    {
        player p;
        assert(p.get_action_set().empty());
    }

    //A player can add an action to its action set
    {
        player p;
        auto action = action_type::idle;
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
        auto action1 = action_type::idle;
        auto action2 = action_type::accelerate_backward;
        add_action(p, action1);
        add_action(p, action2);
        assert(!p.get_action_set().empty());
        assert(p.get_action_set().count(action1));
        assert(p.get_action_set().count(action2));
        remove_action(p, action1);
        assert(!p.get_action_set().count(action1));
        assert(p.get_action_set().count(action2));
    }

    //It is possible to establish how bluish, reddish and greenish a player is
    {

        int blueness = 1;
        int greenness = 1;
        int redness = 1;
        player p = create_player_with_color(
                    color{redness,
                          greenness,
                          blueness}
                    );
        assert(get_blueness(p) == blueness);
        assert(get_redness(p) == redness);
        assert(get_greenness(p) == greenness);
    }

    //A player is by default initiated with state == "active
    {
        const player p{};
        assert(p.get_state() == player_state::active);
    }

    //It is possible to establish how bluish, reddish and greenish a player is
    {

        int blueness = 1;
        int greenness = 1;
        int redness = 1;
        player p = create_player_with_color(
                    color{redness,
                          greenness,
                          blueness}
                    );
        assert(get_blueness(p) == blueness);
        assert(get_redness(p) == redness);
        assert(get_greenness(p) == greenness);
    }

    ///A player has an ID
    ///#1
    {
        const std::string id = "31415";
        const player p = create_player_with_id(id);
        assert(p.get_ID() == id);
    }

    {
    // (324)
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};
        assert(p.get_position() == c);
    }

    {
      // (351)
        assert(to_str(player_state::active) == "active");
    }

  {
    // (627) A player's state is changed by specific functions
    player p;
    p.die();
    assert(p.get_state() == player_state::dead);
    p.revive();
    assert(p.get_state() == player_state::active);
  }

  {
    // (627) A player's state is changed by specific functions, by default a player is active
    const player p;
    assert(p.get_state() == player_state::active);
  }

  //#ifdef FIX_ISSUE_609
  {
    // (609) A player that is dead becomes transparent
    player p;
    assert(p.get_color().get_opaqueness() == 255);
    p.die();
    assert(p.get_color().get_opaqueness() == 100);
  }
  //#endif

#ifdef FIX_ISSUE_612
{
  // (612) A player that revives gets a new colour at random
  player p;
  color c;
  int n_red = 0;
  int n_green = 0;
  int n_blue = 0;
  const color r = create_red_color();
  const color g = create_green_color();
  const color b = create_blue_color();

  for (int i = 0; i < 100; ++i)
    {
      p.die();
      p.revive();
      c = p.get_color();
      if (c == r) { ++n_red; }
      else if (c == g) { ++n_green; }
      else if (c == b) { ++n_blue; }
      else { throw("A player should not revive with any other color than r, g, b"); }
    }

  assert(n_red > 0 && n_green > 0 && n_blue > 0);
}
#endif

    // (401) can get the position of player through global function
    {
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};
        assert(get_position(p) == c);
    }

    // (402) can get the x and y of player through global function
    {
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};
        assert(get_x(p) == c.get_x());
        assert(get_y(p) == c.get_y());
    }

  //#define FIX_ISSUE_367
  #ifdef FIX_ISSUE_367
    {
      {
        // Moving or turning with speed = 0 does not change position
        player p;
        const coordinate starting_position = p.get_coordinate();
        assert(p.get_speed() < 0.0000000001 && p.get_speed() > -0.00000000001);
        p.move();
        assert(starting_position == p.get_coordinate());
        p.turn_left();
        assert(starting_position == p.get_coordinate());
      }
      {
        player p;
        const coordinate starting_position = p.get_coordinate();
        assert(p.get_speed() < 0.0000000001 && p.get_speed() > -0.00000000001);

        // a player with direction 0 and speed 1 moves one unit of space along the x-axis
        while(p.get_speed() <= 1) {
          p.accelerate();
        }
        assert(p.get_speed() < 1.00000000000001 && p.get_speed() > 0.999999999999999);
        // acceleration alone should not change player position
        assert(starting_position == p.get_coordinate());
        assert(p.get_direction() < 0.0000000001 && p.get_direction() > -0.00000000001);
        p.move();
        const double delta_x = get_x(starting_position) - get_x(p.get_coordinate());
        const double delta_y = get_y(starting_position) - get_y(p.get_coordinate());
        assert(delta_x < 1.00000000000001 && delta_x > 0.999999999999999);
        assert(delta_y < 0.00000000000001 && delta_y > -0.00000000000001);
      }
    }
  #endif

    {
        // #441 A player's color can be set
        player p;
        // Turn the player green
        const color green = create_green_color();
        p.set_color(green);
        assert(p.get_color() == green);
        // Turn the player red
        const color red = create_red_color();
        p.set_color(red);
        assert(p.get_color() == red);
    }

  //#define FIX_ISSUE_469
  #ifdef FIX_ISSUE_469
    {
        // (469) Players have an invulnerability duration
        const player p;
        int p_di = p.get_duration_invulnerability();
    }
  #endif

    {
      // (524)
        //#define DBG // Add ASSERT() for debugging purpose
        #ifdef DBG
            #define ASSERT(condition, message) \
            do { \
                if (! (condition)) { \
                    std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                              << " line " << __LINE__ << ": " << message << std::endl; \
                    std::terminate(); \
                } \
            } while (false)
        #endif

        // A player has an initial direction of 270 degrees (facing up)
        {
            const player p{coordinate(1.2, 3.4), player_shape::rocket};
            assert(std::abs(p.get_direction() - 270 * M_PI / 180) < 0.00001);
        }

        // A player has an initial speed of zero
        {
            const player p{coordinate(1.2, 3.4), player_shape::rocket};
            assert(std::abs(p.get_speed() - 0.0) < 0.00001);
        }

        // A player has a default maximum forward speed of 1
        {
            const player p;
            assert(p.get_max_speed_forward() == 1);
        }

        // A player has a default maximum backward speed of -0.5
        {
            const player p;
            assert(p.get_max_speed_backward() == -0.5);
        }

        // A player has a default forward acceleration of 0.1 per tick
        {
            const player p;
            assert(p.get_acceleration_forward() == 0.1);
        }

        // A player has a default backward acceleration of 0.05 per tick
        {
            const player p;
            assert(p.get_acceleration_backward() == 0.05);
        }

        // A player can actually move
        {
            player p;
            //give some speed to the player
            p.accelerate_forward();
            // with initial position only x will change since sin of 0 is 0
            double a_x = get_x(p);
            double a_y = get_y(p);
            p.move(); // move the player
            double b_x = get_x(p);
            double b_y = get_y(p);
            assert(std::abs(a_x - b_x) < 0.0000001);
            assert(std::abs(a_y - b_y) > 0.0000001);
        }
        {
            player p;
            //give some speed to the player
            p.accelerate_forward();
            // change direction a little bit
            // otherwise default direction would not show
            // a change in y
            p.turn_left();

            double a_x = get_x(p);
            double a_y = get_y(p);
            p.move(); // move the player
            double b_x = get_x(p);
            double b_y = get_y(p);
            assert(std::abs(a_x - b_x) > 0.0000001);
            assert(std::abs(a_y - b_y) > 0.0000001);
        }


        // A player increases its forward speed by one 'acceleration' per forward acceleration
        {
            player p;
            p.accelerate_forward();
            assert(p.get_speed() - p.get_acceleration_forward() < 0.00000000001);
            assert(p.get_speed() - p.get_acceleration_forward() > -0.00000000001);
        }

        // A player increases its backward speed by one 'acceleration' per backward acceleration
        {
            player p;
            p.accelerate_backward();
            assert(p.get_acceleration_backward() + p.get_speed() > -0.00000000001);
            assert(p.get_acceleration_backward() + p.get_speed() < 0.00000000001);
        }

        // A player cannot surpass its maximum forward speed
        {
            player p;
            int n_of_accelerations = 1000;
            assert(p.get_acceleration_forward() * n_of_accelerations > p.get_max_speed_forward());
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.accelerate_forward();
            }
            assert(p.get_speed() == p.get_max_speed_forward());
        }

        // A player cannot surpass its maximum backward speed
        {
            player p;
            int n_of_accelerations = 1000;
            assert(-p.get_acceleration_backward() * n_of_accelerations < -p.get_max_speed_backward());
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.accelerate_backward();
            }
            assert(p.get_speed() == p.get_max_speed_backward());
        }

        // A player will decelerate to speed 0, but not 'over-decelerate', in both directions
        {
            player p;
            int n_of_accelerations = 1000;

            assert(p.get_acceleration_forward() * n_of_accelerations > p.get_max_speed_forward());
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.accelerate_forward();
            }
            assert(p.get_speed() == p.get_max_speed_forward());
            assert(p.get_deceleration_forward() * n_of_accelerations > p.get_speed());
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.decelerate();
            }
            assert(p.get_speed() == 0);

            assert(-p.get_acceleration_backward() * n_of_accelerations < p.get_max_speed_backward());
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.accelerate_backward();
            }
            assert(p.get_speed() == p.get_max_speed_backward());
            assert(p.get_deceleration_backward() * n_of_accelerations > abs(p.get_speed()));
            for(int i = 0; i != n_of_accelerations; i++ )
            {
                p.decelerate();
            }
            assert(p.get_speed() == 0);
        }
    }
  // (676) Can compare players for equality
  {
    const player a;
    const player b;
    assert(a == b);
  }
#endif // no tests in release
}


