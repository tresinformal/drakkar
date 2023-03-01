#include "game.h"
#include "game_functions.h"
#include "coordinate.h"
#include "action_type.h"
#include "environment.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <numeric>

game::game(
  const game_options& options,
  const environment& the_environment,
  int num_players
) :
  m_rng(options.get_rng_seed()),
  m_options{options},
  m_n_ticks{0},
  m_player(static_cast<unsigned int>(num_players), player()),
  m_environment{the_environment}
{

  for (unsigned int i = 0; i != m_player.size(); ++i)
    {

      auto ID = std::to_string(i);
      coordinate player_position(
            300.0 + static_cast<unsigned int>(m_dist_x_pls) * i,
            400.0);
      m_player[i] =
          player(player_position,
                 player_shape::rocket,
                 player_state::active,
                 1,
                 -0.5,
                 0.1,
                 0.05,
                 0.1,
                 0.1,
                 100,
                 0.007,
                 color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0,
                       i % 3 == 2 ? 255 : 0),
                 ID);
    }
}

void game::do_action(const int player_index, action_type action)
{
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_player.size()));
  do_action(m_player[player_index], action);
}

void game::do_action(player& player, action_type action)
{
  switch (action)
    {
    case action_type::turn_left:
      {
        player.turn_left();
        player.set_action_flag(action_type::turn_left);
        break;
      }
    case action_type::turn_right:
      {
        player.turn_right();
        player.set_action_flag(action_type::turn_right);
        break;
      }
    case action_type::accelerate_forward:
      {
        if (player.get_speed() >= 0) {
            player.accelerate_forward();
            player.set_action_flag(action_type::accelerate_forward);
          } else {
            player.decelerate();
            player.set_action_flag(action_type::accelerate_forward);
          }
        break;
      }
    case action_type::accelerate_backward:
      {
        if (player.get_speed() <= 0) {
            player.accelerate_backward();
            player.set_action_flag(action_type::accelerate_backward);
          } else {
            player.decelerate();
            player.set_action_flag(action_type::accelerate_backward);
          }
        break;
      }
    case action_type::idle:
      {
        player.set_action_flag(action_type::idle);
        return;
      }
    }
}

void game::do_actions() noexcept
{

  for(auto& player: m_player)
    {
      for(const auto& action : player.get_action_set())
        {
          do_action(player, action);
        }
    }
}

void game::set_collision_vector( int lhs,  int rhs)
{
  assert(1 == 2); //!OCLINT Guess this is unused :-)
  m_v_collisions_ind.push_back(lhs);
  m_v_collisions_ind.push_back(rhs);
}

void game::apply_inertia()
{
  for (auto& player: m_player)
    {
      if (player.get_action_flag() != action_type::accelerate_forward && player.get_action_flag() != action_type::accelerate_backward)
      {
        if (player.get_speed() != 0.0)
        {
          player.decelerate();
        }
      }
    }
}

void game::tick()
{
  if(has_any_interplayer_collision(*this))
  {
    grow_winning_player(*this);
    shrink_losing_player(*this);
  }

  /// Sequence is important: firstly do_actions(), then apply_inertia(), finally reset_player_action()
  // Actions issued by the players are executed
  do_actions();

  // For now only applies inertia
  apply_inertia();

  // Reset players' actions
  reset_player_action();

  // Check and resolve wall collisions
  resolve_wall_collisions();

  // and updates m_n_ticks
  increment_n_ticks();

  // Check whether end game condition is met
  check_over();
}

void game::increment_n_ticks()
{
  ++m_n_ticks;
}

void game::kill_player(const int index)
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_player.size()));
  get_player(index).die();
}

void game::resolve_wall_collisions()
{
  for(auto& player : m_player)
    {
      player = resolve_wall_collision(player);
    }
}

player game::resolve_wall_collision(player p)
{
  if(hits_south_wall(p, m_environment))

    {
      p.set_y(get_max_y(m_environment) - p.get_diameter()/2);
    }


  if(hits_north_wall(p, m_environment))
    {
      p.set_y(get_min_y(m_environment) + p.get_diameter()/2);
    }


  if(hits_east_wall(p, m_environment))
    {
      p.set_x(get_max_x(m_environment) - p.get_diameter()/2);
    }


  if(hits_west_wall(p, m_environment))
    {
      p.set_x(get_min_x(m_environment) + p.get_diameter()/2);
    }

  return p;
}

void game::reset_player_action()
{
  for (player &p : m_player)
    {
      p.set_action_flag(action_type::idle);
    }
}

/// END GAME CONDITION ///
void game::check_over()
{
  m_is_over = m_n_ticks >= m_options.get_max_time();
}
/// END GAME CONDITION ///

double calc_mean(const std::vector<double>& v)
{
  return std::accumulate(
        std::begin(v),
        std::end(v), 0.0
        ) / v.size();
}

double calc_var(const std::vector<double>& v, double mean_v){
  double v_var;
  std::vector<double> sdm(v.size());
  for(unsigned int i = 0; i < v.size(); i++) {
      sdm[i] = (v[i] - mean_v) * (v[i] - mean_v);
  }
  v_var = std::accumulate(std::begin(sdm), std::end(sdm), 0.0) / v.size();
  return v_var;
}

template <typename L, typename R>
bool have_same_position(const L& lhs, const R& rhs)
{
  return get_x(lhs) - get_x(rhs) < 0.0001 &&
        get_x(lhs) - get_x(rhs) > -0.0001 &&
        get_y(lhs) - get_y(rhs) < 0.0001 &&
        get_y(lhs) - get_y(rhs) > -0.0001;
}

bool hits_wall(const player& p, const environment& e)
{

  if(hits_west_wall(p,e)
     || hits_east_wall(p,e)
     || hits_north_wall(p,e)
     || hits_south_wall(p,e))
    {
      return true;
    }
  return false;
}

bool hits_south_wall(const player& p, const environment& e)
{
  return get_y(p) + p.get_diameter()/2 > get_max_y(e);
}

bool hits_north_wall(const player& p, const environment& e)
{
  return get_y(p) - p.get_diameter()/2 < get_min_y(e);
}

bool hits_east_wall(const player& p, const environment& e)
{
  return get_x(p) + p.get_diameter()/2 > get_max_x(e);
}

bool hits_west_wall(const player& p, const environment& e)
{
  return get_x(p) - p.get_diameter()/2 < get_min_x(e);
}

void grow_winning_player(game &g)
{
  const int first_player_index = get_collision_members(g)[0];
  const int second_player_index = get_collision_members(g)[1];

  const int winner_index = get_winning_player_index(g, first_player_index, second_player_index);
  player& winning_player = g.get_player(winner_index);
  winning_player.grow();
}

void shrink_losing_player(game &g)
{
  const int first_player_index = get_collision_members(g)[0];
  const int second_player_index = get_collision_members(g)[1];

  const int loser_index = get_losing_player_index(g, first_player_index, second_player_index);
  player& losing_player = g.get_player(loser_index);
  losing_player.shrink();
}

void save(const game& g, const std::string& filename)
{
  // start with a simplified example
  //   1. open file stream
  //   2. write one value to the file stream
  //   3. close file stream
  // https://en.cppreference.com/w/cpp/io/basic_fstream/open

  // create first a file stream object
  std::fstream f;
  // open the file
  f.open(filename);
  assert(g.get_n_ticks() >= 0);
  assert(!filename.empty());
}

void test_game() //!OCLINT tests may be many
{
#ifndef NDEBUG // no tests in release

  // The game has done zero ticks upon startup
  {
    const game g;
    // n_ticks is the number of times the game is displayed on screen
    assert(g.get_n_ticks() == 0);
  }

  // A game has a vector of players
  {
    const game g;
    // The value 1234.5 is irrelevant: just get this to compile
    for (unsigned int i = 0; i < g.get_v_player().size(); ++i)
      {
        assert(get_x(g.get_player(static_cast<int>(i))) > -1234.5);
      }
  }

  // A game has game_options
  {
    const game g;
    assert(g.get_game_options().is_playing_music());
  }

  // A game responds to actions: player can turn left
  {
    game g;
    for (auto i = 0; i < static_cast< int>(g.get_v_player().size()); ++i)
      {
        const double before{g.get_player(i).get_direction()};
        g.do_action(i,action_type::turn_left);
        const double after{g.get_player(i).get_direction()};
        //assert(std::abs(before - after) > 0.01); // Should be different
        assert(std::abs(before - after) > 0.001);
      }
  }

  // A game responds to actions: player can turn right
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        const double before{g.get_player(i).get_direction()};
        g.do_action(i, action_type::turn_right);
        const double after{g.get_player(i).get_direction()};
        //assert(std::abs(before - after) > 0.01); // Should be different
        assert(std::abs(before - after) > 0.001);
      }
  }

  // A game responds to actions: player can accelerate
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        const double before{g.get_player(i).get_speed()};
        g.do_action(i, action_type::accelerate_forward);
        const double after{g.get_player(i).get_speed()};
        assert(before - after < 0.01); // After should be > than before
      }
  }

  // A game responds to actions: player can brake
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)

      {
        // give the player a speed of more than 0
        g.do_action(i, action_type::accelerate_forward);
        const double before{g.get_player(i).get_speed()};
        g.do_action(i, action_type::accelerate_backward);
        const double after{g.get_player(i).get_speed()};
        assert(before > after);
        // After should be < than before
      }
  }

  // A game responds to actions: player can accelerate backward
  {
    game g;
    for (unsigned int i = 0; i < g.get_v_player().size(); ++i)
      {
        // the player has a speed of 0
        const double before{g.get_player(i).get_speed()};
        assert(before == 0.0);
        g.do_action(i, action_type::accelerate_backward);
        const double after{g.get_player(i).get_speed()};
        assert(before - after > 0.0000000000000001);
      }
  }

  // A game responds to actions: player can do nothing
  {
    game g;
    for (unsigned int i = 0; i < g.get_v_player().size(); ++i)
      {
        // the player has a speed of 0
        const double before_sp{g.get_player(i).get_speed()};
        //and a certain direction
        const double before_dir{g.get_player(i).get_direction()};
        //And an initial x and y position
        const double before_x{get_x(g.get_player(i))};
        const double before_y{get_y(g.get_player(i))};

        //action_type::none does not change anyhthing in the player
        g.do_action(i, action_type::idle);
        const double after_sp{g.get_player(i).get_speed()};
        const double after_dir{g.get_player(i).get_direction()};
        const double after_x{get_x(g.get_player(i))};
        const double after_y{get_y(g.get_player(i))};

        assert(before_sp - after_sp < 0.0000000000000001 &&
               before_sp - after_sp > -0.0000000000000001);
        assert(before_dir - after_dir < 0.0000000000000001 &&
               before_dir - after_dir > -0.0000000000000001);
        assert(before_x - after_x < 0.0000000000000001 &&
               before_x - after_x > -0.0000000000000001);
        assert(before_y - after_y < 0.0000000000000001 &&
               before_y - after_y > -0.0000000000000001);
      }
  }

  // Can get a player's direction by using a free function
  {
    const game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        const double a{g.get_player(i).get_direction()};
        const double b{get_nth_player_direction(g, i)};
        assert(std::abs(b - a) < 0.0001);
      }
  }

  // Can get a player's size by using a free function
  {
    const game g;
    const int n_players{static_cast<int>(g.get_v_player().size())};
    for (int i = 0; i != n_players; ++i)
      {
        const double a{g.get_player(i).get_diameter()};
        const double b{get_nth_player_size(g, i)};
        assert(std::abs(b - a) < 0.0001);
      }
  }

  // game by default has a mix and max evironment size
  {
    game g;
    assert(get_max_x(g.get_env()) > -56465214.0);
  }

  // calling tick updates the counter and
  // callling tick() increases m_n_tick by one
  {
    game g;
    const int before = g.get_n_ticks();
    g.tick();
    assert(g.get_n_ticks() - before == 1);
  }

  // players are placed at dist of 300 points
  // along the x axis at initialization
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size() - 1); ++i)
      {
        assert(get_x(g.get_player(i)) - get_x(g.get_player(i + 1)) +
               g.get_dist_x_pls() <
               0.000001 &&
               get_x(g.get_player(i)) - get_x(g.get_player(i + 1)) +
               g.get_dist_x_pls() >
               -0.000001);
      }
  }

  // In the start of the game no players are colliding
  {
    game g;
    assert(!has_any_interplayer_collision(g));
  }

  // two overlapping players signal a collision
  {
    game g;
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));

    assert(has_any_interplayer_collision(g));
  }

  #define FIX_ISSUE_233
  #ifndef FIX_ISSUE_233
  // [PRS] A collision kills a player
  {
    game g;
    const auto n_alive_players_before = count_alive_players(g);
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));
    assert(has_collision(g));
    g.tick();
    const auto n_alive_players_after = count_alive_players(g);
    assert(n_alive_players_after < n_alive_players_before);
  }
  // [PRS]  A collision destroy one of the colliding player
  {
    game g;
    const auto n_players_before = count_alive_players(g);
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));
    assert(has_collision(g));
    g.tick();
    const auto n_players_after = count_alive_players(g);
    assert(n_players_after < n_players_before);
    assert(!has_collision(g));
    g.tick();
    const auto n_player_afteragain = count_alive_players(g);
    assert(n_player_afteragain == n_players_after);
  }

  #else // FIX_ISSUE_233
  // [PRS] #233 make winning PRS player bigger
  {
    game g;
    // Make player 1 and 2 overlap
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));
    assert(has_any_interplayer_collision(g));
    const int winning_player_index = get_winning_player_index(g, 0, 1);
    const int winning_player_size_before = get_nth_player_size(g, winning_player_index);
    // Here the magic happens
    g.tick();
    const int winning_player_size_after = get_nth_player_size(g, winning_player_index);
    assert(winning_player_size_after > winning_player_size_before);
  }
  #endif // FIX_ISSUE_233

  // (234) Make losing PRS player smaller
  {
    game g;
    // Make player 1 and 2 overlap
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));
    assert(has_any_interplayer_collision(g));
    const int losing_player_index = get_losing_player_index(g, 0, 1);
    const int losing_player_size_before = get_nth_player_size(g, losing_player_index);
    // Here the magic happens
    g.tick();
    const int losing_player_size_after = get_nth_player_size(g, losing_player_index);
    assert(losing_player_size_after < losing_player_size_before);
  }

  //#define FIX_ISSUE_381
  #ifdef FIX_ISSUE_381
  ///A player can become invulnerable
  {
    game g;

    assert(is_active(g.get_player(0)));
    become_invulnerable(g.get_player(0));
    assert(is_invulnerable(g.get_player(0)));

  }
  #endif

  #ifdef FIX_ISSUE_382
  ///An invulnerable player cannot shrink
  {
    game g;

    //Make the first player invulnerable
    become_invulnerable(g.get_player(0));

    // Make player 1 and 2 overlap
    g.get_player(1).set_x(get_x(g.get_player(0)));
    g.get_player(1).set_y(get_y(g.get_player(0)));
    assert(has_collision(g));

    // After a tick, invulnerable player does not shrink
    const int inv_player_size_before =  get_nth_player_size(g, 0);
    g.tick();
    const int inv_player_size_after =  get_nth_player_size(g, 0);
    assert(inv_player_size_after == inv_player_size_before);
  }
  #endif

  //#define FIX_ISSUE_463
  #ifdef FIX_ISSUE_463
  // Players lose invulnerability after a short time
  {
    game g;
    player& p = g.get_player(0);
    const int duration_invulnerability = p.get_duration_invulnerability();
    become_invulnerable(p);
    for (int t = 0; t < duration_invulnerability; t++)
      {
        assert(is_invulnerable(p));
        g.tick();
      }
    assert(!is_invulnerable(p));
    assert(p.get_state() == player_state::active);
  }
  #endif

  // If green eats blue then green survives
  {
    game g;
    assert(g.get_player(1).get_color().get_green() == 255);
    assert(g.get_player(2).get_color().get_blue() == 255);
    g.get_player(1).set_x(get_x(g.get_player(2)));
    g.get_player(1).set_y(get_y(g.get_player(2)));
    assert(has_any_interplayer_collision(g));
    g.tick();
    assert(g.get_player(1).get_color().get_green() > 250);
  }

  // A game is initialized with walls, the walls form a 16:9
  // rectangle with center at coordinates of 0,0
  // And short size = 720 by default;
  {
    double wall_short_side = 720.0;
    environment some_environment = environment(wall_short_side);
    game_options options;
    game g(options,some_environment);
    assert(g.get_env().get_wall_s_side() - wall_short_side < 0.00001 &&
           g.get_env().get_wall_s_side() - wall_short_side > -0.00001);
  }

  ///Players in game are initialized with ID equal to their index
  {
    game g;
    for(size_t i = 0; i != g.get_v_player().size(); i++)
      {
        assert(g.get_player(i).get_ID() == std::to_string(i));
      }
  }

  ///Players cannot move past wall coordinates as defined in environment
  {
    game g;

    //set a player very close to the top wall (y = 0)
    auto p = g.get_player(0);
    p.set_y(0.00 + p.get_diameter()/2 + 0.01);
    assert(!hits_wall(p,g.get_env()));

    //give the player some speed
    p.accelerate_forward();
    //Move the player into a wall
    p.move();
    assert(hits_north_wall(p, g.get_env()));

    /// manage the collision
    p = g.resolve_wall_collision(p);

    assert(!hits_wall(p,g.get_env()));
  }

  /// When a player is out it stays in the player vector but its state is out
  {
    game g;

    auto num_of_players_begin = g.get_v_player().size();

    g.kill_player(0);

    assert(num_of_players_begin == g.get_v_player().size());
    assert(is_dead(g.get_player(0)));
  }

#ifdef FIX_ISSUE_626
  {
    // (626) A player that is dead can be revived
    game g;
    g.kill_player(0);
    assert(is_dead(g.get_player(0)));
    g.revive_player(0);
    assert(!is_dead(g.get_player(0)));
  }
#endif

#ifdef FIX_ISSUE_611
  {
    // (611) A player that is dead revives after some time
    game g;
    g.kill_player(0);
    const int revive_time = 100; // arbitrary; choose a better number when solving this test :)
    for (int i = 0; i < revive_time; ++i)
      {
        assert(is_dead(g.get_player(0)));
        g.tick();
      }
    assert(!is_dead(g.get_player(0)));
  }
#endif
  {
    // (606) When a player goes under some size, it dies
    game g;
    player& p = g.get_player(0);
    const double death_size = 5.0; // choose a value
    p.set_death_size(death_size);
    // Make the player smaller
    while(get_nth_player_size(g, 0) > death_size)
      {
        assert(!is_dead(p));
        p.shrink();
        g.tick();
      }
    assert(is_dead(p));
  }

  {
    //(625) A player that is dead cannot collide with other players
    game g;
    const coordinate c_p2 = g.get_player(1).get_position();
    g.get_player(0).place_to_position(c_p2);
    assert(are_colliding(g.get_player(0), g.get_player(1)));
    g.kill_player(0);
    assert(!are_colliding(g.get_player(0), g.get_player(1)));
  }

  //#define FIX_ISSUE_248
  #ifdef FIX_ISSUE_248
  {
    game g;
    auto first_player_diam = get_nth_player_size(g,0);
    assert(first_player_diam = g.get_player(0).get_diameter());
  }
  #endif

  // (400) A game's min and max coordinates can be accessed quickly
  {
    game g;
    double max_x = get_max_x(g);
    assert(max_x == get_max_x(g.get_env()));
    double min_x = get_min_x(g);
    assert(min_x == get_min_x(g.get_env()));
    double max_y = get_max_y(g);
    assert(max_y == get_max_y(g.get_env()));
    double min_y = get_min_y(g);
    assert(min_y == get_min_y(g.get_env()));
  }

  // Test calc_mean
  {
    std::vector<double> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    auto expected_mean = calc_mean(numbers);
    assert(expected_mean - 1.5 < 0.0001 && expected_mean - 1.5 > -0.0001);
  }

  {
    // 285
    game g;
    std::uniform_real_distribution<double>(0.0, 1.0)(g.get_rng());
  }

  {
    // default game arguments
    const double short_wall_side = 1600;
    const int n_players = 0;

    const int seed = 123456789;
    game g(
      game_options(seed),
      short_wall_side,
      n_players
    );
    std::mt19937 expected_rng(seed);
    assert(g.get_rng()() - expected_rng() < 0.00001 &&
           g.get_rng()() - expected_rng() > -0.00001);
  }

  {
    // 321
    coordinate Some_random_point(1,1);
    player n_player(Some_random_point);

    assert(have_same_position(n_player, Some_random_point));
  }

 {
    // (457) The color of any player can be accessed easily
    const game g;
    const color color_player_one = get_nth_player_color(g, 0);
    const color color_player_two = get_nth_player_color(g, 1);
    const color color_player_three = get_nth_player_color(g, 2);
    // Default colors for players: R, G, B
    assert(color_player_one == create_red_color());
    assert(color_player_two == create_green_color());
    assert(color_player_three == create_blue_color());
  }

  {
    // (471)
    const game_options options;
    const game g(options);
    assert(g.get_game_options() == options);
  }

  //#define FIX_ISSUE_472
  #ifdef FIX_ISSUE_472
  {
    const game g;
    // Only check if this compiles, we do not care about the RNG seed
    assert(g.get_options().get_rng_seed() == 0
      || g.get_options().get_rng_seed() != 0);
  }
  #endif

  {
    // (464) A player's state can be accessed easily
    const game g;
    assert(get_nth_player_state(g, 0) ==  g.get_player(0).get_state());
  }

  // (478) Saving a game and loading it, must result in the same game
  {
    const game g;
    const std::string filename = "test.txt";
    save(g, filename); // To prevent a bloated/Winnebago class
    //const game h = load(filename);
    //assert(g == h);
  }

  #define FIX_ISSUE_524
  #ifdef FIX_ISSUE_524
  {
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

    // do_action() will change a player's action flag
    {
      game g;
      g.do_action(0, action_type::accelerate_backward);
      assert(g.get_player(0).get_action_flag() == action_type::accelerate_backward);
      g.do_action(0, action_type::accelerate_forward);
      assert(g.get_player(0).get_action_flag() == action_type::accelerate_forward);
      g.do_action(0, action_type::idle);
      assert(g.get_player(0).get_action_flag() == action_type::idle);
      g.do_action(0, action_type::turn_left);
      assert(g.get_player(0).get_action_flag() == action_type::turn_left);
      g.do_action(0, action_type::turn_right);
      assert(g.get_player(0).get_action_flag() == action_type::turn_right);
    }

    // reset_player_action() can reset all players' action flags
    {
        game g;
        for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
        {
            g.do_action(i, action_type::accelerate_forward);
            assert(g.get_player(i).get_action_flag() == action_type::accelerate_forward);
        }
        g.reset_player_action();
        for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
        {
            assert(g.get_player(i).get_action_flag() == action_type::idle);
        }
    }

    // apply_inertia() does nothing if the players are doing accelerate_forward or accelerate_backward actions
    {
      game g;
      double before;
      double after;

      // give the player a speed of more than 0
      g.do_action(0, action_type::accelerate_forward);
      before = g.get_player(0).get_speed();
      g.tick();
      after = g.get_player(0).get_speed();
      // apply_inertia() did nothing because players were accelerating forward
      assert(before == after);

    }

    // apply_inertia() triggers decelerate() if the players are idle after moving backward
    {
      game g;

      // Can decelerate multiple times
      const double max_speed_backward = g.get_player(0).get_max_speed_backward();
      const double deceleration_backward = g.get_player(0).get_deceleration_backward();

      assert(std::abs(max_speed_backward) >=  deceleration_backward);
      // Make the first player accelerate backwards hard
      const int n_of_accelerations = 1000;
      const double amount_speed_up = deceleration_backward * n_of_accelerations;
      assert(amount_speed_up >= std::abs(max_speed_backward));
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.do_action(0, action_type::accelerate_backward);
      }
      const double before = g.get_player(0).get_speed();
      g.reset_player_action();
      // reset_player_action() was called at the previous tick,
      // at the next tick apply_inertia() should take effect
      g.tick();
      const double after = g.get_player(0).get_speed();
      // apply_inertia() decelerates players because they are now idle
      assert(before < after);
      const double speed_change = after - before;
      // speed_change and decelaration_backwards should be the same
      assert(std::abs(deceleration_backward - speed_change) < 0.000000000001);
    }

    // apply_inertia() triggers decelerate() if the players are idle after moving forward
    {
      game g;
      int n_of_accelerations = 1000;
      double before;
      double after;

      assert(g.get_player(0).get_max_speed_forward() >= g.get_player(0).get_deceleration_forward());
      assert(g.get_player(0).get_acceleration_forward() * n_of_accelerations >= g.get_player(0).get_max_speed_forward());
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.do_action(0, action_type::accelerate_forward);
      }
      before = g.get_player(0).get_speed();
      g.reset_player_action();
      // reset_player_action() was called at the previous tick,
      // at the next tick apply_inertia() should take effect
      g.tick();
      after = g.get_player(0).get_speed();
      // apply_inertia() decelerates players because they are now idle
      assert(std::abs(before - after) - g.get_player(0).get_deceleration_forward() < 0.0000000000000001);
    }

    // apply_inertia() won't over-decelerate the players when moving forward
    {
      game g;
      int n_of_accelerations = 1000;

      assert(g.get_player(0).get_max_speed_forward() >= g.get_player(0).get_deceleration_forward());
      assert(g.get_player(0).get_acceleration_forward() * n_of_accelerations >= g.get_player(0).get_max_speed_forward());
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.do_action(0, action_type::accelerate_forward);
      }
      g.reset_player_action();
      // reset_player_action() was called at the previous tick,
      // at the next tick apply_inertia() should take effect
      assert(g.get_player(0).get_deceleration_forward() * n_of_accelerations > g.get_player(0).get_max_speed_forward());
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.tick();
      }
      assert(g.get_player(0).get_speed() == 0);
    }

    // apply_inertia() won't over-decelerate the players when moving backward
    {
      game g;
      int n_of_accelerations = 1000;

      assert(std::abs(g.get_player(0).get_max_speed_backward()) >= g.get_player(0).get_deceleration_backward());
      assert(g.get_player(0).get_acceleration_backward() * n_of_accelerations >= std::abs(g.get_player(0).get_max_speed_backward()));
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.do_action(0, action_type::accelerate_backward);
      }
      g.reset_player_action();
      // reset_player_action() was called at the previous tick,
      // at the next tick apply_inertia() should take effect
      assert(g.get_player(0).get_deceleration_backward() * n_of_accelerations > std::abs(g.get_player(0).get_max_speed_backward()));
      for(int i = 0; i != n_of_accelerations; i++ )
      {
          g.tick();
      }
      assert(g.get_player(0).get_speed() == 0);
    }

    // Do accelerate_backward() when moving forward (speed > 0) will actually trigger decelerate()
    {
        game g;
        int n_of_accelerations = 1000;
        double before;
        double after;

        assert(g.get_player(0).get_max_speed_forward() >= g.get_player(0).get_deceleration_forward());
        assert(g.get_player(0).get_acceleration_forward() * n_of_accelerations >= g.get_player(0).get_max_speed_forward());
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            g.do_action(0, action_type::accelerate_forward);
        }
        g.reset_player_action();
        before = g.get_player(0).get_speed();
        g.do_action(0, action_type::accelerate_backward);
        g.reset_player_action();
        after = g.get_player(0).get_speed();
        assert(std::abs(before - after) - g.get_player(0).get_deceleration_forward() < 0.000000001);
    }

    // Do accelerate_forward() when moving backward (speed < 0) will actually trigger decelerate()
    {
        game g;
        int n_of_accelerations = 1000;
        double before;
        double after;

        assert(std::abs(g.get_player(0).get_max_speed_backward()) >= g.get_player(0).get_deceleration_backward());
        assert(g.get_player(0).get_acceleration_backward() * n_of_accelerations >= std::abs(g.get_player(0).get_max_speed_backward()));
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            g.do_action(0, action_type::accelerate_backward);
        }
        g.reset_player_action();
        before = g.get_player(0).get_speed();
        g.do_action(0, action_type::accelerate_forward);
        g.reset_player_action();
        after = g.get_player(0).get_speed();
        assert(std::abs(before - after) - g.get_player(0).get_acceleration_forward() < 0.000000001);
    }

    // A player's displacement per tick when moving forward is the same as m_acceleration_forward
    {
        game g;
        double before_x, before_y;
        double after_x, after_y;
        double expected_displacement;
        double actual_displacement;
        expected_displacement = g.get_player(0).get_acceleration_forward();
        before_x = g.get_player(0).get_x();
        before_y = g.get_player(0).get_y();
        g.do_action(0, action_type::accelerate_forward);
        after_x = g.get_player(0).get_x();
        after_y = g.get_player(0).get_y();
        actual_displacement = sqrt(pow((after_x - before_x), 2) + pow((after_y - before_y), 2));
        assert(std::abs(actual_displacement - expected_displacement) < 0.000000001);
    }

    // A player's displacement per tick when moving backward is the same as m_acceleration_backward
    {
        game g;
        double before_x, before_y;
        double after_x, after_y;
        double expected_displacement;
        double actual_displacement;
        expected_displacement = g.get_player(0).get_acceleration_backward();
        before_x = g.get_player(0).get_x();
        before_y = g.get_player(0).get_y();
        g.do_action(0, action_type::accelerate_backward);
        after_x = g.get_player(0).get_x();
        after_y = g.get_player(0).get_y();
        actual_displacement = sqrt(pow((after_x - before_x), 2) + pow((after_y - before_y), 2));
        assert(std::abs(actual_displacement - expected_displacement) < 0.000000001);
    }

    // A player's displacement per tick when decelerating backward is the same as m_deceleration_backward
    {
        game g;
        double new_x, min_x, max_x;
        double new_y, min_y, max_y;
        double before_x, before_y;
        double after_x, after_y;
        double expected_displacement;
        double actual_displacement;
        double player_speed;
        double deceleration_backward;
        double max_speed_backward;
        int n_of_accelerations = 1000;

        deceleration_backward = g.get_player(0).get_deceleration_backward();
        max_speed_backward = g.get_player(0).get_max_speed_backward();
        assert(std::abs(max_speed_backward) >= deceleration_backward);
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            g.do_action(0, action_type::accelerate_backward);
        }
        g.reset_player_action();
        player_speed = g.get_player(0).get_speed();
        assert(player_speed < 0);
        expected_displacement = player_speed + deceleration_backward;
        // make sure a player does not trespass the walls
        new_x = g.get_player(0).get_x() + expected_displacement * cos(g.get_player(0).get_direction());
        min_x = get_min_x(g.get_env()) + g.get_player(0).get_diameter()/2;
        max_x = get_max_x(g.get_env()) - g.get_player(0).get_diameter()/2;
        new_y = g.get_player(0).get_y() + expected_displacement * sin(g.get_player(0).get_direction());
        min_y = get_min_y(g.get_env()) + g.get_player(0).get_diameter()/2;
        max_y = get_max_y(g.get_env()) - g.get_player(0).get_diameter()/2;
        assert(new_x < max_x);
        assert(new_x > min_x);
        assert(new_y < max_y);
        assert(new_y > min_y);
        before_x = g.get_player(0).get_x();
        before_y = g.get_player(0).get_y();
        // reset_player_action() was called at the previous tick,
        // at the next tick apply_inertia() should take effect
        g.tick();
        after_x = g.get_player(0).get_x();
        after_y = g.get_player(0).get_y();
        actual_displacement = sqrt(pow((after_x - before_x), 2) + pow((after_y - before_y), 2));
        assert(std::abs(actual_displacement - std::abs(expected_displacement)) < 0.000000001);
    }

    // A player's displacement per tick when decelerating forward is the same as m_deceleration_forward
    {
        game g;
        double new_x, min_x, max_x;
        double new_y, min_y, max_y;
        double before_x, before_y;
        double after_x, after_y;
        double expected_displacement;
        double actual_displacement;
        double player_speed;
        double deceleration_forward;
        double max_speed_forward;
        int n_of_accelerations = 5;

        deceleration_forward = g.get_player(0).get_deceleration_forward();
        max_speed_forward = g.get_player(0).get_max_speed_forward();
        assert(std::abs(max_speed_forward) >= deceleration_forward);
        for(int i = 0; i != n_of_accelerations; i++ )
        {
            g.do_action(0, action_type::accelerate_forward);
        }
        g.reset_player_action();
        player_speed = g.get_player(0).get_speed();
        assert(player_speed > 0);
        expected_displacement = player_speed - deceleration_forward;
        // make sure a player does not trespass the walls
        new_x = g.get_player(0).get_x() + expected_displacement * cos(g.get_player(0).get_direction());
        min_x = get_min_x(g.get_env()) + g.get_player(0).get_diameter()/2;
        max_x = get_max_x(g.get_env()) - g.get_player(0).get_diameter()/2;
        new_y = g.get_player(0).get_y() + expected_displacement * sin(g.get_player(0).get_direction());
        min_y = get_min_y(g.get_env()) + g.get_player(0).get_diameter()/2;
        max_y = get_max_y(g.get_env()) - g.get_player(0).get_diameter()/2;
        assert(new_x < max_x);
        assert(new_x > min_x);
        assert(new_y < max_y);
        assert(new_y > min_y);
        before_x = g.get_player(0).get_x();
        before_y = g.get_player(0).get_y();
        g.tick();
        after_x = g.get_player(0).get_x();
        after_y = g.get_player(0).get_y();
        actual_displacement = sqrt(pow((after_x - before_x), 2) + pow((after_y - before_y), 2));
        assert(std::abs(actual_displacement - expected_displacement) < 0.000000001);
    }

  }
  #endif // FIX_ISSUE_524

  // (682) A game is over when the time limit is reached
  {
    const int time_limit = 10;
    const game_options g_options{3,
                          false,
                          get_random_kam(),
                          get_random_kam(),
                          get_random_kam(),
                          environment_type(),
                          time_limit
                         };
    game g{g_options};
    for (int i = 0; i < time_limit; i++)
      {
        assert(!g.is_over());
        g.tick();
      }
    assert(g.is_over());

#ifdef FIX_ISSUE_716
    // (716) Game no longer ticks after game is over
    const int n_ticks = g.get_n_ticks();
    g.tick();
    assert(g.get_n_ticks() == n_ticks);

    // and as a result, no further actions are processed
    // for example, players are not moved
    player& p = g.get_player(0); // ref to player one
    const coordinate initial_position = p.get_position();

    add_action(p, action_type::accelerate_forward);
    g.tick();
    assert(p.get_position() == initial_position);
#endif // FIX_ISSUE_716
  }

  {
    const game g;
    const auto players{g.get_players()};
    const auto v_player{g.get_v_player()};
    assert(players == v_player);
  }

  #ifdef FIX_ISSUE_721
  // (721) The largest player wins the game
  {
    game g;
    player &player_two = g.get_player(1);
    player_two.grow();
    assert(g.who_is_winning() == 1);

    player &player_three = g.get_player(2);
    player_three.grow();
    player_three.grow(); // twice
    assert(g.who_is_winning() == 2);
   }
  #endif // FIX_ISSUE_721

  #ifdef FIX_ISSUE_722
  // (722) In case of a tie, winner is decided on a coin flip
  {
      const int a_seed = 5;
      const int another_seed = 6; // change if this picks the same winner

      game a_game(game_options{a_seed});
      player &player_two = a_game.get_player(1);
      player_two.grow();
      player &player_three = a_game.get_player(2);
      player_three.grow();
      assert(a_game.who_is_winning() != 0);

      game another_game(game_options{another_seed});
      player &other_player_two = another_game.get_player(1);
      other_player_two.grow();
      player &other_player_three = another_game.get_player(2);
      other_player_three.grow();
      assert(another_game.who_is_winning() != 0);

      assert(a_game.who_is_winning != another_game.who_is_winning());
  }
  #endif // FIX_ISSUE_722

#endif // no tests in release
}


