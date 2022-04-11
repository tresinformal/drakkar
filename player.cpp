#include "player.h"
#include "player_shape.h"
#include "player_state.h"
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
}


/// Get the direction of player movement, in radians
double player::get_direction() const noexcept { return m_direction_radians; }

void player::decelerate() noexcept
{

    if(m_player_speed > 0.0)
    {
        m_player_speed -= m_player_deceleration_forward;
    }
    else if(m_player_speed < 0.0)
    {
        m_player_speed += m_player_deceleration_backward;
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
    const double dx = std::abs(get_x(lhs) - get_x(rhs));
    const double dy = std::abs(get_y(lhs) - get_y(rhs));
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
                0.01,
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
                    0.01,
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

void test_player() //!OCLINT tests may be long
{
#ifndef NDEBUG // no tests in release
//#define FIX_ISSUE_336
  #ifdef FIX_ISSUE_336
      {
        player p;
        cordinate predicted_player_position = predict_players_movement(p);
        p.move();
        assert(p.get_position()==predicted_player_position);
        assert(((predicted_player_position.m_x - get_x(p))<0.001)&&(((predicted_player_position.m_x - get_x(p))>-0.001)));
        assert(((predicted_player_position.m_x - get_y(p))<0.001)&&(((predicted_player_position.m_x - get_y(p))>-0.001)));
      }
  #endif

  {}
    // Can default construct a player
    {
        const player p;
        assert(get_x(p) == 0.0);
        assert(get_y(p) == 0.0);
        assert(p.get_shape() == player_shape::rocket); // Or your favorite shape
    }
  // A player has the same coordinats as set at construction
  {
      const coordinate c{12.34, 23.45};
      const player_shape s{player_shape::rocket};
      const player p(c, s);
      // Must be the same
      assert(std::abs(get_x(p) - c.get_x()) < 0.00001);
      assert(std::abs(get_y(p) - c.get_y()) < 0.00001);
#define FIX_ISSUE_337
#ifdef FIX_ISSUE_337
      assert(p.get_position() == c);
#endif
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
#define FIX_ISSUE_36
#ifdef FIX_ISSUE_36
    // A player starts with 1.0 (that is, 100%) health
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        // Health is 100% by default
        assert(std::abs(p.get_health() - 1.0) < 0.00001);
    }
#endif
    // A player has a speed of zero
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        assert(std::abs(p.get_speed() - 0.0) < 0.00001);
    }

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

    // A player has a forward max_speed of 20(arbitrary value for now)
    {
        const player p;
        assert(p.get_max_speed_forward() - 20 < 0.000000000001);
    }

    // A player has a backward max_speed of -15(arbitrary value for now)
    {
        const player p;
        assert(p.get_max_speed_backward() + 15 > -0.000000000001);
    }

    // A player has a default forward acceleration of 0.1 per frame
    {
        const player p;
        assert(p.get_acceleration_forward() - 0.1 < 0.00000000001);
    }

    // A player has a default backward acceleration of 0.05 per frame
    {
        const player p;
        assert(p.get_acceleration_backward() - 0.05 < 0.00000000001);
    }

    // A player has an initial size of one hundred
    {
        const player p{coordinate(1.2, 3.4), player_shape::rocket};
        assert(std::abs(p.get_diameter() - 100.0) < 0.00001);
    }
    // A player can update its position
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
#define FIX_ISSUE_231
#ifdef FIX_ISSUE_231
    // The correct player must win
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
#endif // FIX_ISSUE_231

    //#define FIX_ISSUE_232
    //#ifdef FIX_ISSUE_232
    // The correct player must lose
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
    // #endif // FIX_ISSUE_232

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

    // A player increases its speed by one 'acceleration' per forward acceleration
    {
        player p;
        p.accelerate_forward();
        assert(p.get_speed() - p.get_acceleration_forward() < 0.00000000001);
    }

    // A player increases its speed by one 'acceleration' per backward acceleration
    {
        player p;
        p.accelerate_backward();
        assert(p.get_acceleration_backward() + p.get_speed() > -0.00000000001);
    }

//#define FIX_ISSUE_270
#ifdef FIX_ISSUE_270
    // A player increases its backward speed by one 'backward acceleration' per backward acceleration
    // or: a player decreases its speed by one 'backward acceleration' per backward acceleration
    {
        player p;
        p.acc_backward();
        assert(std::abs(p.get_speed() - p.get_acceleration_backward()) < 0.00000000001);
    }
    // A players speed after one 'acceleration' is less than max_speed
    {
        player p;
        p.accelerate();
        assert(p.get_speed() < p.get_max_speed());
    }
    // A players speed after one 'backward acceleration' is more than negative max_speed
    {
        player p;
        p.acc_backward();
        assert(p.get_speed() > -p.get_max_speed());
    }
    // A players goes right/up upon acceleraton
    {
        player p_forward;
        coordinate c_before = get_coordinate(p_forward);
        p_forward.accelerate();
        p_forward.move();
        coordinate c_after = get_coordinate(p_forward);
        assert(p_forward.get_direction() > -0.00000000001 && p_forward.get_direction() < 0.00000000001);
        double dx = get_x(c_after) - get_x(c_before);
        double dy = get_y(c_after) - get_y(c_before);
        assert(dx > 0.00000000001);
        assert(dy > -0.00000000001 && dy < 0.00000000001);

        player p_backward;
        c_before = get_coordinate(p_backward);
        p_backward.acc_backward();
        p_backward.move();
        c_after = get_coordinate(p_backward);
        assert(p_backward.get_direction() > -0.00000000001 && p_backward.get_direction() < 0.00000000001);
        double dx = get_x(c_after) - get_x(c_before);
        double dy = get_y(c_after) - get_y(c_before);
        assert(dx < -0.00000000001);
        assert(dy > -0.00000000001 && dy < 0.00000000001);
    }
    // A players actually goes backwards after some backwards movements
    {
        player p;
        coordinate c_before = get_coordinate(p);
        p.accelerate();
        p.move();
        coordinate c_inbetween = get_coordinate(p);
        double dx_a = get_x(c_inbetween) - get_x(c_before);
        double dy_a = get_y(c_inbetween) - get_y(c_before);
        assert(dx_a > 0.00000000001);
        assert(dy_a > -0.00000000001 && dy_a < 0.00000000001);
        p.acc_backward();
        p.move();
        p.acc_backward();
        p.move();
        p.acc_backward();
        p.move();
        coordinate c_after = get_coordinate(p);
        double dx_b = get_x(c_after) - get_x(c_inbetween);
        double dy_b = get_y(c_after) - get_y(c_inbetween);
        assert(dx_b < -0.00000000001); // Signs should flip
        // it should not change in the y direction if the assumption about initial direction is correct
        assert(dy_b > -0.00000000001 && dy_b < 0.00000000001);
    }
#endif //FIX_ISSUE_270
    //When a player is standing still,
    //braking will do nothing
    //counteract it by increasing its speed
    {
        player p;
        assert(p.get_speed() == 0.0);
        p.decelerate();
        assert(p.get_speed() == 0.0);
    }

    //When a player is accelerating backwards brake will
    //counteract it by increasing its speed
    {
        player p;
        p.accelerate_backward();
        auto full_back_speed = p.get_speed();
        assert (full_back_speed < 0);
        p.decelerate();
        auto brake_back_speed = p.get_speed();
        assert(brake_back_speed > full_back_speed);
    }

    //A player cannot surpass its forward max_speed
    {
        player p;
        int n_of_accelerations = 1000;
        assert(p.get_acceleration_forward() * n_of_accelerations > p.get_max_speed_forward());
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            p.accelerate_forward();
        }
        assert(p.get_speed() - p.get_max_speed_forward() < 0.00001
               && p.get_speed() - p.get_max_speed_forward() > -0.00001);
    }

    //A player cannot surpass its backward max_speed
    {
        player p;
        int n_of_accelerations = 1000;
        assert(-p.get_acceleration_backward() * n_of_accelerations < -p.get_max_speed_backward());
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            p.accelerate_backward();
        }

        assert(p.get_speed() - p.get_max_speed_forward() < 0.00001
               && p.get_speed() - p.get_max_speed_backward() > -0.00001);
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
    // A player object can be initialized to a stunned state
    {
        const player p{coordinate(1.2, 3.4), player_shape::circle, player_state::stunned};
        assert(p.get_state() ==  player_state::stunned);
        assert(p.get_state() !=  player_state::active);
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

#ifdef FIX_ISSUE_220
    ///A player can become stunned
    {
        player p;
        assert(is_active(p));
        stun(p);
        assert(is_stunned(p));
    }
#endif

#define FIX_ISSUE_324
#ifdef FIX_ISSUE_324
  {
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};
        assert(p.get_position() == c);
  }
#endif

#define FIX_ISSUE_351
#ifdef FIX_ISSUE_351
  {
    assert(to_str(player_state::active) == "active");
  }
#endif

//#define FIX_ISSUE_401
#ifdef FIX_ISSUE_401
    {
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};
        assert(get_position(p) == c);
    }
#endif

//#define FIX_ISSUE_402
#ifdef FIX_ISSUE_402
    {
        auto x = 1.23456;
        auto  y = 123456.789;
        coordinate c{x, y};
        player p{c};

        ///you HAVE TO use the get_position(player)
        /// to implement get_x(player) and get_y(player)
        /// I do not know how to make it explicit in the test @Richel
        assert(get_x(p) == c.get_x());
        assert(get_y(p) == c.get_y());
    }
#endif


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

#define FIX_ISSUE_441
#ifdef FIX_ISSUE_441
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
#endif

//#define FIX_ISSUE_469
#ifdef FIX_ISSUE_469
  {
    // (469) Players have an invulnerability duration
    const player p;
    int p_di = p.get_duration_invulnerability();
  }
#endif

#endif // no tests in release
}


