#include "game.h"
#include "projectile.h"
#include "projectile_type.h"
#include "action_type.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

game::game(double wall_short_side,
           int num_players,
           int n_ticks,
           size_t n_shelters,
           int n_enemies,
           int n_food):
  m_n_ticks{n_ticks},
  m_player(static_cast<unsigned int>(num_players), player()),
  m_enemies(n_enemies, enemy()),
  m_environment(wall_short_side),
  m_food(n_food, food()),
  m_shelters(n_shelters, shelter())
{

  for (unsigned int i = 0; i != m_player.size(); ++i)
    {

      auto ID = std::to_string(i);
      m_player[i] =
          player(300.0 + static_cast<unsigned int>(m_dist_x_pls) * i,
                 400.0,
                 player_shape::rocket,
                 player_state::active,
                 2,
                 0.1,
                 -0.0001,
                 -0.1,
                 100,
                 0.01,
                 color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0,
                       i % 3 == 2 ? 255 : 0),
                 ID);
    }

  // Set shelters
  {
    assert(m_shelters.size() == n_shelters);
    int i = 0;
    for (auto &this_shelter : m_shelters)
      {
        const double angle{2.0 * M_PI * static_cast<double>(i) /
              static_cast<double>(m_shelters.size())};
        const double mid_x{400.0};
        const double mid_y{300.0};
        const double radius{200.0};
        const double x{mid_x + (std::sin(angle) * radius)};
        const double y{mid_y - (std::cos(angle) * radius)};
        const color c(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0,
                      i % 3 == 2 ? 255 : 0, 128 + 64);
        this_shelter = shelter(x, y, 100.0, c);
        ++i;
      }
  }
}

void add_projectile(game &g, const projectile &p)
{
  g.get_projectiles().push_back(p);
}

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


double get_nth_player_size(const game& g, const int i)
{
  return g.get_player(i).get_diameter();
}

int count_alive_players(const game& g) noexcept
{
  return std::count_if(
        g.get_v_player().begin(),
        g.get_v_player().end(),
        [](const player& p)
  {return p.get_state() != player_state::dead;});
}

//Counts how many food items have been generated
int count_food_items(const game &g)
{
  return static_cast<int>(g.get_food().size());
}

//Checks if the game has food  -> should check if it has uneaten food instead
bool has_food(const game &g)
{
  std::vector<food> v_food{g.get_food()};
  int count = 0;
  for (unsigned int i = 0; i < v_food.size(); i++) {
      if (!v_food[i].is_eaten())
        {
          count++;
        }
    }
  return count > 0 ;
}

void eat_nth_food(game &g, const int n)
{
  if(g.get_food()[n].is_eaten()) {
      throw std::logic_error("You cannot eat food that already has been eaten!");
    }
  g.get_food()[n].set_food_state(food_state::eaten);
}

int count_n_projectiles(const game &g) noexcept
{
  return static_cast<int>(g.get_projectiles().size());
}

void game::do_action(const int player_index, action_type action)
{
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_player.size()));
  do_action(m_player[player_index], action);
}

void game::do_action(player& player, action_type action)
{
  if(!(player.get_state() == player_state::stunned))
  {
    switch (action)
    {
      case action_type::turn_left:
      {
        player.turn_left();
        break;
      }
      case action_type::turn_right:
      {
        player.turn_right();
        break;
      }
      case action_type::accelerate:
      {
        player.accelerate();
        break;
      }
      case action_type::brake:
      {
        player.brake();
        break;
      }
      case action_type::acc_backward:
      {
        player.acc_backward();
        break;
      }
      case action_type::shoot:
      {
        player.shoot();
        break;
      }
      case action_type::shoot_stun_rocket:
      {
        player.shoot_stun_rocket();
        break;
      }
      case action_type::none:
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

double game::get_player_direction( int player_ind)
{
  assert(1 == 2); //!OCLINT Guess this is unused :-)
  return get_player(player_ind).get_direction();
}

double get_player_direction(game g, int player_ind)
{
  return g.get_player(player_ind).get_direction();
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
      if (player.get_speed() != 0.0)
        {
          // And should this function take some value from environment?
          player.brake();

        }
    }
}

void game::move_shelter()
{
  for (auto & shelter: m_shelters)
    shelter.update_shelter_position();
}

void game::move_projectiles()
{
  for (auto &p : m_projectiles)
    {
//      p.set_type(projectile_type::rocket);
      p.move();
    }
}

void game::projectile_collision()
{

  const int n_projectiles = count_n_projectiles(*this);
  // For every projectile ...

  for (int i = 0 ; i != n_projectiles ; ++i)
  {
    //For every player...
    const int n_players = static_cast<int>(get_v_player().size());
    for(int j = 0; j != n_players; ++j)
    {
      // if it is not the one that shot it ...
      #ifdef NEED_TO_WRITE_THIS_ISSUE_241
      if(!(this->get_projectiles()[i].get_owner() == j))
      {

      }
      #endif // NEED_TO_WRITE_THIS_ISSUE_241
      // If the projectile touches the player ...

      // if the projectile is a stun rocket: stun the player

      // projectile disappears
    }
  }
}

void game::tick()
{
  if(has_collision(*this))
    {
      kill_losing_player(*this);
    }

  // Moves the projectiles
  move_projectiles();

  //Projectiles hit the players
  projectile_collision();

  // For now only applies inertia
  apply_inertia();

  //Move shelters
  move_shelter();

  //Actions issued by the players are executed
  do_actions();

  //Check and resolve wall collisions
  do_wall_collisions();

  // players that shoot must generate projectiles
  for (player &p : m_player)
    {
      // When a player shoots, 'm_is_shooting' is true for one tick.
      // 'game' reads 'm_is_shooting' and if it is true,
      // it (1) creates a projectile, (2) sets 'm_is_shooting' to false
      if (p.is_shooting())
        {
          put_projectile_in_front_of_player(m_projectiles, p);
        }
      p.stop_shooting();
      assert(!p.is_shooting());

      if (p.is_shooting_stun_rocket())
        {
          // Put the projectile just in front outside of the player
          const double d{p.get_direction()};
          const double x{p.get_x() + (std::cos(d) * p.get_diameter() * 1.1)};
          const double y{p.get_y() + (std::sin(d) * p.get_diameter() * 1.1)};
          const coordinate c{x ,y};
          m_projectiles.push_back(projectile(c, d, projectile_type::stun_rocket));
        }
      p.stop_shooting_stun_rocket();
      assert(!p.is_shooting_stun_rocket());
    }

  // and updates m_n_ticks
  increment_n_ticks();
}

void game::increment_n_ticks()
{
  ++m_n_ticks;
}

bool has_collision(const game &g) noexcept
{
  const auto n_players = static_cast<int>(g.get_v_player().size()) ;
  for (int i = 0; i < n_players; ++i)
    {
      auto& lhs_pl = g.get_player(i);

      if(is_alive(lhs_pl))
        {
          for (int j = i + 1; j < n_players; ++j)
            {
              auto& rhs_pl = g.get_player(j);
              if(is_alive(rhs_pl))
                {
                  if (are_colliding(lhs_pl, rhs_pl))
                    {
                      return true;
                    }
                }
            }
        }

    }
  return false;
}

bool has_collision(const player& pl, const projectile& p)
{
  //Player and projectile are circularal, so use pythagoras
  const double player_radius{pl.get_diameter()};
  const double projectile_radius{p.get_radius()};
  const double dx = std::abs(get_x(p) - pl.get_x());
  const double dy = std::abs(get_y(p) - pl.get_y());
  const double dist = std::sqrt((dx * dx) + (dy * dy));
  const double radii = player_radius + projectile_radius;
  return dist < radii;
}

bool has_collision_with_projectile(const game & g) noexcept
{
  const auto& projectiles = g.get_projectiles();
  const auto& players = g.get_v_player();

  for (const auto& p : projectiles)
    {
      for (const auto& pl : players)
        {
          if (has_collision(pl, p)) return true;
        }
    }
  return false;
}

bool has_wall_collision(const game& g)
{
  for(const auto& player : g.get_v_player())
    {
      if(hits_wall(player, g.get_env()))
        {
          return true;
        }
    }
  return false;
}

bool has_enemy_collision(const game&)
{
  return false;
}

bool has_food_collision(const game &) noexcept
{
  return false;
}

bool have_same_position(const player& p, const food& f)
{
  return p.get_x() - f.get_x() < 0.0001 &&
      p.get_x() - f.get_x() > -0.0001 &&
      p.get_y() - f.get_y() < 0.0001 &&
      p.get_y() - f.get_y() > -0.0001;
}

bool hits_south_wall(const player& p, const environment& e)
{
  return p.get_y() + p.get_diameter()/2 > e.get_max_y();
}

bool hits_north_wall(const player& p, const environment& e)
{
  return p.get_y() - p.get_diameter()/2 < e.get_min_y();
}

bool hits_east_wall(const player& p, const environment& e)
{
  return p.get_x() + p.get_diameter()/2 > e.get_max_x();
}

bool hits_west_wall(const player& p, const environment& e)
{
  return p.get_x() - p.get_diameter()/2 < e.get_min_x();
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

std::vector<int> get_collision_members(const game &g) noexcept
{
  std::vector<int> v_collisions;
  const auto n_players = static_cast<int>(g.get_v_player().size());
  for (int i = 0; i < n_players; ++i)
    {
      for (int j = i + 1; j < n_players; ++j)
        {
          if (are_colliding(g.get_player(i), g.get_player(j)))
            {
              v_collisions.push_back(i);
              v_collisions.push_back(j);
            }
        }
    }
  return v_collisions;
}

void kill_losing_player(game &g)
{
  const int first_player_index = get_collision_members(g)[0];
  const int second_player_index = get_collision_members(g)[1];
  const player& first_player = g.get_player(first_player_index);
  const player& second_player = g.get_player(second_player_index);
  const int c1 = get_colorhash(first_player);
  const int c2 = get_colorhash(second_player);

  // It is possible that this happens, no worries here :-)
  if (c1 == c2) return;
  else if (std::abs(c1-c2)==1)
    {
      if(c1<c2)
        g.kill_player(second_player_index);
      else
        g.kill_player(first_player_index);
    }
  else if(c1<c2)
    g.kill_player(first_player_index);
}
void put_player_on_food(player &p, const food &f)
{
  p.place_to_position(get_position(f));
}

void put_projectile_in_front_of_player(std::vector<projectile>& projectiles, const player& p)
{
  // Put the projectile just in front outside of the player
  const double d{p.get_direction()};
  const double x{p.get_x() + (std::cos(d) * p.get_diameter() * 1.1)};
  const double y{p.get_y() + (std::sin(d) * p.get_diameter() * 1.1)};
  const coordinate c{x, y};
  projectiles.push_back(projectile(c, d));
}

void game::kill_player(const int index)
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_player.size()));
  get_player(index).set_state(player_state::dead);
}

void game::do_wall_collisions()
{
  for(auto& player : m_player)
    {
      player = wall_collision(player);
    }
}

player game::wall_collision(player p)
{
  if(hits_south_wall(p, m_environment))

    {
      p.set_y(m_environment.get_max_y() - p.get_diameter()/2);
    }


  if(hits_north_wall(p, m_environment))
    {
      p.set_y(m_environment.get_min_y() + p.get_diameter()/2);
    }


  if(hits_east_wall(p, m_environment))
    {
      p.set_x(m_environment.get_max_x() - p.get_diameter()/2);
    }


  if(hits_west_wall(p, m_environment))
    {
      p.set_x(m_environment.get_min_x() + p.get_diameter()/2);
    }

  return p;
}

std::default_random_engine& game::get_rng() noexcept
{
  return m_rng;
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
        assert(g.get_player(static_cast<int>(i)).get_x() > -1234.5);
      }
  }
  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty());
  }
  // A game has enemies
  {
    const game g;
    assert(!g.get_enemies().empty());
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
        g.do_action(i, action_type::accelerate);
        const double after{g.get_player(i).get_speed()};
        assert(before - after < 0.01); // After should be > than before
      }
  }
  // A game responds to actions: player can break
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)

      {
        // give the player a speed of more than 0
        g.do_action(i, action_type::accelerate);
        const double before{g.get_player(i).get_speed()};
        g.do_action(i, action_type::brake);
        const double after{g.get_player(i).get_speed()};
        assert(before > after);
        // After should be < than before
      }
  }

  //A game responds to actions: player can accelerate backward
  {
    game g;
    for (unsigned int i = 0; i < g.get_v_player().size(); ++i)
      {
        // the player has a speed of 0
        const double before{g.get_player(i).get_speed()};
        assert(before == 0.0);
        g.do_action(i, action_type::acc_backward);
        const double after{g.get_player(i).get_speed()};
        assert(before - after > 0.0000000000000001);
      }
  }

  // A game responds to actions: player can shoot
  {
    game g;
    const int n_projectiles_before{count_n_projectiles(g)};
    g.do_action(0, action_type::shoot);
    // Without a tick, no projectile is formed yet
    const int n_projectiles_after{count_n_projectiles(g)};
    assert(n_projectiles_before == n_projectiles_after);
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
        const double before_x{g.get_player(i).get_x()};
        const double before_y{g.get_player(i).get_y()};

        //action_type::none does not change anyhthing in the player
        g.do_action(i, action_type::none);
        const double after_sp{g.get_player(i).get_speed()};
        const double after_dir{g.get_player(i).get_direction()};
        const double after_x{g.get_player(i).get_x()};
        const double after_y{g.get_player(i).get_y()};

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

  // Projectiles move
  {
    game g;
    // Create 1 projectile for sure (there may be more)
    g.do_action(0, action_type::shoot);
    g.tick();
    assert(count_n_projectiles(g) >= 1);
    const double x_before{get_x(g.get_projectiles()[0])};
    const double y_before{get_y(g.get_projectiles()[0])};
    g.tick();
    const double x_after{get_x(g.get_projectiles()[0])};
    const double y_after{get_y(g.get_projectiles()[0])};
    // coordinats should differ
    assert(std::abs(x_before - x_after) > 0.01 ||
           std::abs(y_before - y_after) > 0.01);
  }
  // Can get a player's direction by using a free function
  {
    const game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        const double a{g.get_player(i).get_direction()};
        const double b{get_player_direction(g, i)};
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
    assert(g.get_env().get_max_x() > -56465214.0);
  }

  // A game has enemies
  {
    const game g;
    assert(!g.get_enemies().empty());
  }

  // calling tick updates the counter and
  // callling tick() increases m_n_tick by one
  {
    game g;
    const int before = g.get_n_ticks();
    g.tick();
    assert(g.get_n_ticks() - before == 1);
  }
  // inertia  slows down players
  {
    game g;
    std::vector<double> before_v;
    std::vector<double> after_v;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        // give the player a speed of more than 0
        g.do_action(i, action_type::accelerate);
        before_v.push_back(g.get_player(i).get_speed());
      }
    g.apply_inertia();
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size()); ++i)
      {
        after_v.push_back(g.get_player(i).get_speed());
      }
    for (unsigned int i = 0; i < g.get_v_player().size(); ++i)
      {
        assert(before_v[i] - after_v[i] > 0.0000000000000001);
        // After should be < than before
      }

  }

  // players are placed at dist of 300 points
  // along the x axis at initialization
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_v_player().size() - 1); ++i)
      {
        assert(g.get_player(i).get_x() - g.get_player(i + 1).get_x() +
               g.get_dist_x_pls() <
               0.000001 &&
               g.get_player(i).get_x() - g.get_player(i + 1).get_x() +
               g.get_dist_x_pls() >
               -0.000001);
      }
  }

  // In the start of the game no players are colliding
  {
    game g;
    assert(!has_collision(g));
  }
  // two overlapping players signal a collision
  {
    game g;
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());

    assert(has_collision(g));
  }
  //#define FIX_ISSUE_233
#ifndef FIX_ISSUE_233
  // [PRS] A collision kills a player
  {
    game g;
    const auto n_alive_players_before = count_alive_players(g);
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    const auto n_alive_players_after = count_alive_players(g);
    assert(n_alive_players_after < n_alive_players_before);
  }
  // [PRS]  A collision destroy one of the colliding player
  {
    game g;
    const auto n_players_before = count_alive_players(g);
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    const auto n_players_after = count_alive_players(g);
    assert(n_players_after < n_players_before);
    assert(!has_collision(g));
    g.tick();
    const auto n_player_afteragain = count_alive_players(g);
    assert(n_player_afteragain == n_players_after);
  }

  {
  //  The stun rocket should not be fired at the very beginning
  const game g;
  assert(count_n_projectiles(g) == 0);
  }

#else // FIX_ISSUE_233
  // [PRS] #233 make winning PRS player bigger
  {
    game g;
    // Make player 1 and 2 overlap
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    const int winning_player_index = get_winning_player_index(g, 0, 1);
    const int winning_player_size_before = get_nth_player_size(g, winning_player_index);
    // Here the magic happens
    g.tick();
    const int winning_player_size_after = get_nth_player_size(g, winning_player_index);
    assert(winning_player_size_after > winning_player_size_before);
  }
  //#define FIX_ISSUE_234
#ifdef FIX_ISSUE_234
  // [PRS] #234 make losing PRS player smaller
  {
    game g;
    // Make player 1 and 2 overlap
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    const int losing_player_index = get_losing_player_index(g, 0, 1);
    const int losing_player_size_before = get_nth_player_size(g, losing_player_index);
    // Here the magic happens
    g.tick();
    const int losing_player_size_after = get_nth_player_size(g, losing_player_index);
    assert(losing_player_size_after < losing_player_size_before);
  }
#endif // FIX_ISSUE_234
#endif // FIX_ISSUE_233


  // Blue defeats red
  {
    game g;
    g.get_player(2).set_x(g.get_player(0).get_x());
    g.get_player(2).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    assert(is_red(g.get_player(0)));
    assert(is_green(g.get_player(1)));
    assert(is_blue(g.get_player(2)));
    assert(g.get_v_player().size() == 3); //All three still live
    g.tick();
    assert(count_alive_players(g) == 2);
    //Red has died!
    auto& red = g.get_player(0);
    assert(is_dead(red) && is_red(red));
    // Green and blue survive
    auto& green = g.get_player(1);
    auto& blue = g.get_player(2);
    assert(is_alive(green) && is_green(green) &&
           is_alive(blue) && is_blue(blue));
  }


  //Initially, there is no collision with a projectile
  {
    game g;
    assert(!has_collision_with_projectile(g));
  }
  //If a projectile is put on top of a player, there is a collision
  {
    game g;
    const auto x = g.get_player(0).get_x();
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    add_projectile(g, projectile(c));
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  //If a projectile is 0.99 of its radius right of a player, there is a collision
  {
    game g;
    const double radius = 12.34;
    const auto x = g.get_player(0).get_x() + (0.99 * radius);
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  //If a projectile is 1.01 of its radius right of a player, there is no collision
  {
    game g;
    const double radius = 12.34;
    const auto x = g.get_player(0).get_x() + (1.01*radius);
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }

  // In the start of the game, there is no player-food collision
  {
    game g;
    assert(!has_food_collision(g));
  }

  //Can modify food items, for example, delete all food items
  {
    game g;
    g.get_food();
    assert(!g.get_food().empty());
    g.get_food().clear();
    assert(g.get_food().empty());
  }
  // In the start of the game, there is no player-enemy collision
  {
    game g;
    assert(!has_enemy_collision(g));
  }
  //If red eats green then red survives
  {
    game g;
    assert(is_red(g.get_player(0)));
    assert(is_green(g.get_player(1)));
    assert(is_blue(g.get_player(2)));
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    assert(is_alive(g.get_player(0)));
    assert(is_dead(g.get_player(1)));
  }
  // Blue defeats red
  {
    game g;
    g.get_player(2).set_x(g.get_player(0).get_x());
    g.get_player(2).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    assert(is_red(g.get_player(0)));
    assert(is_green(g.get_player(1)));
    assert(is_blue(g.get_player(2)));
    assert(g.get_v_player().size() == 3); //All three still live
    g.tick();
    assert(count_alive_players(g) == 2);
    //Red has died!
    auto& red = g.get_player(0);
    assert(is_dead(red) && is_red(red));
    // Green and blue survive
    auto& green = g.get_player(1);
    auto& blue = g.get_player(2);
    assert(is_alive(green) && is_green(green) &&
           is_alive(blue) && is_blue(blue));
  }


  //Initially, there is no collision with a projectile
  {
    game g;
    assert(!has_collision_with_projectile(g));
  }
  //If a projectile is put on top of a player, there is a collision
  {
    game g;
    const auto x = g.get_player(0).get_x();
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    add_projectile(g, projectile(c));
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  //If a projectile is 0.99 of its radius right of a player, there is a collision
  {
    game g;
    const double radius = 12.34;
    const auto x = g.get_player(0).get_x() + (0.99 * radius);
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  //If a projectile is 1.01 of its radius right of a player, there is no collision
  {
    game g;
    const double radius = 12.34;
    const auto x = g.get_player(0).get_x() + (1.01*radius);
    const auto y = g.get_player(0).get_y();
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  #ifdef FIX_ISSUE_348
  {
    const food f;
    assert(f == f);
  }
  #endif
  // In the start of the game, there is no player-food collision
  {
    game g;
    assert(!has_food_collision(g));
  }

  //Can modify food items, for example, delete all food items
  {
    game g;
    g.get_food();
    assert(!g.get_food().empty());
    g.get_food().clear();
    assert(g.get_food().empty());
  }
  // In the start of the game, there is no player-enemy collision
  {
    game g;
    assert(!has_enemy_collision(g));
  }
  //If red eats green then red survives
  {
    game g;
    assert(is_red(g.get_player(0)));
    assert(is_green(g.get_player(1)));
    assert(is_blue(g.get_player(2)));
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    assert(is_alive(g.get_player(0)));
    assert(is_dead(g.get_player(1)));
  }

#define FIX_ISSUE_VALENTINES_DAY
#ifdef FIX_ISSUE_VALENTINES_DAY
  //If green eats blue then green survives
  {
    game g;
    assert(g.get_player(1).get_color().get_green() == 255);
    assert(g.get_player(2).get_color().get_blue() == 255);
    g.get_player(1).set_x(g.get_player(2).get_x());
    g.get_player(1).set_y(g.get_player(2).get_y());
    assert(has_collision(g));
    g.tick();
    assert(g.get_player(1).get_color().get_green() > 250);
  }
#endif // FIX_ISSUE_VALENTINES_DAY

  //A game is initialized with walls, the walls form a 16:9
  //rectangle with center at coordinates of 0,0
  //And short size = 720 by default;
  {
    auto wall_short_side = 720.0;
    game g(wall_short_side);
    assert(g.get_env().get_wall_s_side() - wall_short_side < 0.00001 &&
           g.get_env().get_wall_s_side() - wall_short_side > -0.00001);
  }
  // The game has 42 shelters
  {
    const game g;
    assert(g.get_shelters().size() == 42);
  }
  // There are 42 shelters
  {
    const int n_shelters{42};
    const game g(1600, 3, 0, n_shelters);
    assert(g.get_shelters().size() == n_shelters);
  }
  // All shelters have a different location
  //  {
  //    const int n_shelters{42};
  //    const game g(1600, 3, 0, n_shelters);
  //    assert(g.get_shelters().size() == n_shelters);
  //  }

  //The first shelter moves with a tick
  {
    game g;
    assert(g.get_shelters().size() > 0);
    const double before = g.get_shelters()[0].get_x();
    g.tick();
    const double after = g.get_shelters()[0].get_x();
    assert(std::abs(after - before) > 0.0);
  }
#ifdef FIX_ISSUE_315
  // Initial shelters are at random locations over the whole arena
  {
    const game g;
    assert(g.get_shelters().size() > 0);
    // TODO: write test here
  }
#endif // FIX_ISSUE_315

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

    ///move the player into the wall
    p.accelerate();
    assert(hits_north_wall(p, g.get_env()));

    /// manage the collision
    p = g.wall_collision(p);

    assert(!hits_wall(p,g.get_env()));
  }


  ///A stunned player cannot perform actions
  {
    game g;
    player p;
    //make a copy of double get_nth_player_size(const game &in_game, const int &id)

    //the player in its initial state
    player player_copy = p;

    g.do_action(p, action_type::turn_right);
    g.do_action(p, action_type::accelerate);
    assert(player_copy.get_direction() != p.get_direction());
    assert(player_copy.get_speed() != p.get_speed());

    //Reset player back to initial conditions
    p = player_copy;

    //When stunned a player cannot turn (or do any other action)
    stun(p);
    g.do_action(p, action_type::turn_left);
    g.do_action(p, action_type::accelerate);
    g.do_action(p, action_type::shoot);
    assert(!p.is_shooting());
    assert(player_copy.get_direction() == p.get_direction());
    assert(player_copy.get_speed() == p.get_speed());
  }

  /// When a player is killed it stays in the player vector but its state is dead
  {
    game g;

    auto num_of_players_begin = g.get_v_player().size();

    //kill the first player
    g.kill_player(0);

    assert(num_of_players_begin == g.get_v_player().size());
    assert(is_dead(g.get_player(0)));
  }

#ifdef FIX_ISSUE_236
  //When a player touches food it destroys it
  {

    game g;
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    assert(has_food(g))
        assert(has_player_food_collision(g));
    g.tick();
    assert(!has_food(g));
    assert(!has_player_food_collision(g));

  }
#endif

#define FIX_ISSUE_237
#ifdef FIX_ISSUE_237
  //Food and player can be overlapped
  {
    food f;
    player p;
    put_player_on_food(p, f);
    assert(have_same_position(p,f));
  }
#endif

#ifdef FIX_ISSUE_238
  //Food and player can be overlapped
  {
    game g;
    assert(!has_player_food_collision(g));
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    assert(has_player_food_collision(g));
  }
#endif

#ifdef FIX_ISSUE_244

  {
    game g;
    const auto init_player_size = get_nth_player_size(g,0);
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    g.tick();
    assert(g.get_player(0).get_diameter() > init_player_size);

  }

#endif

#ifdef FIX_ISSUE_247
  {
    player p;
    food f;
    assert(!player_and_food_are_colliding(p,f));
    put_player_on_food(p,f);
    assert(player_and_food_are_colliding(p,f));

  }
#endif

#ifdef FIX_ISSUE_248

  {
    game g;
    auto first_player_diam = get_nth_player_size(g,0);
    assert(first_player_diam = g.get_player(0).get_diameter());
  }
#endif

#ifdef FIX_ISSUE_254
  {
    game g;
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    g.tick();
    assert(is_eaten(g.get_food()[0]))
  }
#endif

  // make sure that eat_nth_food() throws a logic_error when the food is already eaten
  {
    game g; //by default one uneaten food
    assert(has_food(g));
    eat_nth_food(g,0);
    assert(!has_food(g));
    try {
      eat_nth_food(g,0); // throws exception
    }
    catch ( const std::exception& e ) {
      assert(std::string(e.what()) == std::string("You cannot eat food that already has been eaten!"));
    }
  }
  // number of food item stays the same,
  // only the state of food item changes after they are eaten
  // eaten food items are ?probably removed by game::tick
  {
    game g; //by default one uneaten food
    const int n_food_items_begin = count_food_items(g);
    assert(has_food(g));
    eat_nth_food(g,0);
    assert(!has_food(g));
    assert(n_food_items_begin == count_food_items(g));
  }

#ifdef FIX_ISSUE_256
  {
    food f;
    player p;
    put_player_on_food(p, f);
    assert(player_and_food_are_colliding(p,f));
    eat_nth_food(g,0);
    assert(!player_and_food_are_colliding(p,f));
  }
#endif

#ifdef FIX_ISSUE_259
  {
    game g; //by default one uneaten food
    assert(has_food(g));
    auto initial_value_timer = get_nth_food_timer(g, 0);
    eat_nth_food(g,0);
    assert(!has_food(g));
    g.tick();
    assert(init_value_timer + 1  == get_nth_food_timer(g, 0));
  }
#endif

#ifdef FIX_ISSUE_255
  {
    game g;
    eat_nth_food(g, 0);
    assert(nth_food_is_eaten(g,0));
    for(int i = 0; i != get_nth_food_regeneration_time(g, 0); i++)
      {
        g.tick();
      }
    assert(!nth_food_is_eaten(g,0));
  }
#endif

#ifdef FIX_ISSUE_250
  //Food can be placed at a random location
  {

    game g;
    std::vector<double> food_x;
    std::vector<double> food_y;

    int repeats = 1000;

    for(int i = 0; i != repeats; i++)
      {
        place_nth_food_randomly(g,0);
        food_x.push_back(get_nth_food_x(g,0));
        food_y.push_back(get_nth_food_y(g,0));
      }
    auto mean_x = calc_mean(food_x);
    auto mean_y = calc_mean(food_y);

    assert(mean_x > -0.01 && mean_x < 0.01);
    assert(mean_y > -0.01 && mean_y < 0.01);

    auto var_x = calc_var(food_x, mean_x);
    auto var_y = calc_var(food_y, mean_y);

    assert(var_x < 0.01 && var_x > -0.01);
    assert(var_y < 0.01 && var_y > -0.01);
  }
#endif

#ifdef FIX_ISSUE_286
  {
    std::vector<double> food_x;
    std::vector<double> food_y;
    int repeats = 1000;
    for(int rng_seed = 0; rng_seed != repeats; rng_seed++)
      {
        game g(1,1,1,1,1,1, rng_seed);
        food_x.push_back(get_nth_food_x(g,0));
        food_y.push_back(get_nth_food_y(g,0));
      }
    auto mean_x = calc_mean(food_x);
    auto mean_y = calc_mean(food_y);

    assert(mean_x > -0.01 && mean_x < 0.01);
    assert(mean_y > -0.01 && mean_y < 0.01);

    auto var_x = calc_var(food_x, mean_x);
    auto var_y = calc_var(food_y, mean_y);

    assert(var_x < 0.01 && var_x > -0.01);
    assert(var_y < 0.01 && var_y > -0.01);
  }
#endif
  // Test calc_mean
#define FIX_ISSUE_285

  {
    std::vector<double> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    auto expected_mean = calc_mean(numbers);
    assert(expected_mean - 1.5 < 0.0001 && expected_mean - 1.5 > -0.0001);
  }

#ifdef FIX_ISSUE_285
  {
    game g;
    std::uniform_real_distribution<double>(0.0, 1.0)(g.get_rng());
  }
#endif

#ifdef FIX_ISSUE_288
  {
    int seed = 123456789;
    game g{0,0,0,0,0,0, seed};
    auto expected_rng = std::minstd_rand(seed);
    assert(g.get_rng() - expected_rng() < 0.00001 &&
           g.get_rng() - expected_rng() > -0.00001);
  }
#endif

#ifdef FIX_ISSUE_321
  {
    coordinate Some_random_point(1,1);
    food n_food;
    player n_player;
    projectile n_projectile;
    shelter n_shelter;
    enenemy n_enemy;


    n_food.set_position(Some_random_point);
    n_player.set_position(Some_random_point);
    n_projectile.set_position(Some_random_point);
    assert(have_same_position(n_food,Some_random_point));
    assert(have_same_position(n_player,Some_random_point));
    assert(have_same_position(n_projectile,Some_random_point));
  }
#endif

  //#define FIX_ISSUE_241
  #ifdef FIX_ISSUE_241
  //Player 1 can stun player 2 with a stun rocket
  {
    game g;

    // Shoot the stun rocket
    g.do_action(0, action_type::shoot_stun_rocket);
    g.tick();
    assert(count_n_projectiles(g) == 1);

    // Put the stun rocket on top of player 2 (at index 1)
    g.get_projectiles().back().set_x(g.get_v_player()[1].get_x());
    g.get_projectiles().back().set_y(g.get_v_player()[1].get_y());

    // Player 2 should not be stunned yet
    assert(!(is_stunned(g.get_v_player()[1])));

    // Stun rocket is there
    assert(count_n_projectiles(g) == 1);

    g.tick();

    // Stun rocket should disappear
    assert(count_n_projectiles(g) == 0);

    // Player 2 is now stunned yet
    assert(is_stunned(g.get_v_player()[1]));
  }
  #endif // FIX_ISSUE_241

#endif // no tests in release
}


