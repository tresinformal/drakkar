#include "game.h"
#include "game_functions.h"
#include "coordinate.h"
#include "projectile.h"
#include "projectile_type.h"
#include "action_type.h"
#include "environment.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>

game::game(
  const game_options& options,
  const environment& the_environment,
  int num_players,
  size_t n_shelters,
  int n_enemies,
  int n_food
) :
  m_rng(options.get_rng_seed()),
  m_options{options},
  m_n_ticks{0},
  m_player(static_cast<unsigned int>(num_players), player()),
  m_enemies(n_enemies, enemy()),
  m_environment{the_environment},
  m_food(n_food, food()),
  m_shelters(n_shelters, shelter())
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
      const double mid_x{1000.0};
      const double mid_y{500.0};
      const double spread{500.0};
      const double x{mid_x + (std::sin(angle) * spread)};
      const double y{mid_y - (std::cos(angle) * spread)};
      const coordinate c{x, y};
      const double radius{50.0};
      const color col(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0,
                      i % 3 == 2 ? 255 : 0, 128 + 64);
      this_shelter = shelter(c, radius, col);
      this_shelter.place_randomly(get_rng(), {get_min_x(*this), get_min_y(*this)}, {get_max_x(*this), get_max_y(*this)});
      ++i;
    }
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
        if (player.is_cool_down() == false)
        {
          player.shoot();
          player.shoot_cool_down();
        }
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
          //Player moves based on its speed and position
          player.move();
          //Then its speed gets decreased by attrition
          player.brake();

        }
    }
}

void game::move_shelter()
{
  for (auto & shelter: m_shelters)
    shelter.make_shelter_drift();
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

  // For every projectile ...
  for (int i = 0 ; i != count_n_projectiles(*this) ; ++i)
  {
    //For every player...
    const int n_players = static_cast<int>(get_v_player().size());
    for(int j = 0; j != n_players; ++j)
    {
      // if it is not the one that shot it ...
      if(!(this->get_projectiles()[i].get_owner_id() == m_player[j].get_ID()))
     {
      double player_radius = m_player[j].get_diameter() / 2.0;
      // If the projectile touches the player ...
      if( this->m_projectiles[i].get_x() > this-> m_player[j].get_x() - player_radius &&
          this-> m_projectiles[i].get_x() < this-> m_player[j].get_x() + player_radius)
        {
          if(this-> m_projectiles[i].get_y() > this-> m_player[j].get_y() - player_radius &&
             this-> m_projectiles[i].get_y() < this-> m_player[j].get_y() + player_radius)
            {

              // if the projectile is a stun rocket: stun the player
              if(this-> m_projectiles[i].get_type() == projectile_type::stun_rocket)  {
                  this-> m_player[j].set_state(player_state::stunned);

                  // projectile disappears
                  std::swap(m_projectiles[i], m_projectiles[m_projectiles.size()-1]);
                  this-> m_projectiles.pop_back();

                  // i can be invalid now, that is i can equal the number of projectiles
                  // one option is:
                  //
                  //  --i;
                  //
                  // but this would be dangerous if the last project has disappeared
                  //
                  // a simple solution is:
                  return;

            }
          }
        }
      }
    }
  }
}

void game::tick()
{
  if(has_any_interplayer_collision(*this))
  {
    //kill_losing_player(*this);
    grow_winning_player(*this);
    shrink_losing_player(*this);
  }

  // Moves the projectiles
  move_projectiles();

  //Projectiles hit the players
  projectile_collision();

  // For now only applies inertia
  apply_inertia();

  // Move shelters
  move_shelter();

  // Actions issued by the players are executed
  do_actions();

  // Check and resolve wall collisions
  resolve_wall_collisions();

  // Increment timers of shoot calm down
  // Increment timers of all food elements
  increment_food_timers();

  // Make players eat food
  make_players_eat_food();

  // Regenerate food items
  regenerate_food_items();

  increment_shoot_cool_down_timers();

  reset_shoot_cool_down_status();

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
          const double x{get_x(p) + (std::cos(d) * p.get_diameter() * 0.5)};
          const double y{get_y(p) + (std::sin(d) * p.get_diameter() * 0.5)};
          const coordinate c{x ,y};
          m_projectiles.push_back(projectile(c, d, projectile_type::stun_rocket, 100, p.get_ID()));
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

void game::kill_player(const int index)
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_player.size()));
  get_player(index).set_state(player_state::dead);
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

void game::eat_food(food& f)
{
  if(f.is_eaten()) {
      throw std::logic_error("You cannot eat food that already has been eaten!");
    }
  f.set_food_state(food_state::eaten);
  f.reset_timer();
}

void game::increment_shoot_cool_down_timers()
{
  for (player &p : m_player)
    {
      p.increment_shoot_cool_down_timer();
    }
}

void game::reset_shoot_cool_down_status()
{
  for (player &p : m_player)
    {
      float player_shoot_fire_rate = projectile::m_fire_rate / p.get_shoot_fire_rate_multiplier();
      if (p.is_cool_down() && p.get_shoot_cool_down_timer() >= player_shoot_fire_rate)
        {
          p.reset_shoot_cool_down_timer();
          p.stop_shoot_cool_down();
        }
    }
}

void game::increment_food_timers()
{
  for (food &f : m_food)
    {
      f.increment_timer();
    }
}

void game::regenerate_food_items()
{
  for (food &f : m_food)
    {
      if (f.is_eaten() && f.get_timer() >= f.get_regeneration_time())
        {
          f.set_food_state(food_state::uneaten);
          f.place_randomly(get_rng(), {get_min_x(*this), get_min_y(*this)}, {get_max_x(*this), get_max_y(*this)});
        }
   }
}

void game::make_players_eat_food()
{
  for(auto& player : m_player)
  {
    const int n_food = static_cast<int>(get_food().size());
    for(int i = 0; i < n_food; ++i)
    {
      if (are_colliding(player, get_food()[i]))
      {
        eat_food(get_food()[i]);
        player.grow();
        #ifdef FIX_ISSUE_440
        // #440 Food changes the color of the player
        player.set_color(get_food()[i].get_color());
        #endif // FIX_ISSUE_440
      }
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

bool is_in_food_radius(const player p, const food f) noexcept
{
    const double dx = std::abs(get_x(p) - get_x(f));
    const double dy = std::abs(get_y(p) - get_y(f));
    const double actual_distance = std::sqrt((dx * dx) + (dy * dy));
    const double collision_distance = p.get_diameter() / 2 + f.get_radius();
    return actual_distance < collision_distance;
}

bool are_colliding(const player &p, const food &f)
{
  return is_in_food_radius(p, f) && !f.is_eaten();
}

bool are_colliding(const player& pl, const projectile& p)
{
  //Player and projectile are circularal, so use pythagoras
  const double player_radius{pl.get_diameter()};
  const double projectile_radius{p.get_radius()};
  const double dx = std::abs(get_x(p) - get_x(pl));
  const double dy = std::abs(get_y(p) - get_y(pl));
  const double dist = std::sqrt((dx * dx) + (dy * dy));
  const double radii = player_radius + projectile_radius;
  return dist < radii;
}
void put_projectile_in_front_of_player(std::vector<projectile>& projectiles, const player& p)
{
  // Put the projectile just in front outside of the player
  const double d{p.get_direction()};
  const double x{get_x(p) + (std::cos(d) * p.get_diameter() * 1.1)};
  const double y{get_y(p) + (std::sin(d) * p.get_diameter() * 1.1)};
  const coordinate c{x, y};
  projectiles.push_back(projectile(c, d));
}

void eat_nth_food(game& g, const int n)
{
    if(g.get_food()[n].is_eaten()) {
        throw std::logic_error("You cannot eat food that already has been eaten!");
    }
    g.eat_food(g.get_food()[n]);
}

void place_nth_food_randomly(game &g, const int &n)
{
  g.get_food()[n].place_randomly(g.get_rng(), {get_min_x(g), get_min_y(g)}, {get_max_x(g), get_max_y(g)});
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

void put_player_on_food(player &p, const food &f)
{
  auto new_position = f.get_position();
  p.place_to_position(new_position);
}

void put_player_near_food(player &p, const food &f, const double distance)
{
  auto f_p = f.get_position();
  coordinate new_position = coordinate(get_x(f_p) + distance, get_y(f_p));
  p.place_to_position(new_position);
}

bool all_positions_equal(const std::vector<coordinate> &shelters, const std::vector<coordinate> &other_shelters) noexcept
{
    bool same_position = false;
    for (size_t i = 0; i < shelters.size(); i++)
    {
        if(have_same_position(shelters[i], other_shelters[i]))
        {
            same_position = true;
        }
    }
    return same_position;
}

void save(const game& g, const std::string& filename)
{
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
  // A game responds to actions: player can brake
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
        const double before_x{get_x(g.get_player(i))};
        const double before_y{get_y(g.get_player(i))};

        //action_type::none does not change anyhthing in the player
        g.do_action(i, action_type::none);
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
#define FIX_ISSUE_234
#ifdef FIX_ISSUE_234
  // [PRS] #234 make losing PRS player smaller
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
#endif // FIX_ISSUE_234
#endif // FIX_ISSUE_233

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
  //Initially, there is no collision with a projectile
  {
    game g;
    assert(!has_any_player_projectile_collision(g));
  }
  //If a projectile is put on top of a player, there is a collision
  {
    game g;
    const auto x = get_x(g.get_player(0));
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    add_projectile(g, projectile(c));
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
  }
  //If a projectile is 0.99 of its radius right of a player, there is a collision
  {
    game g;
    const double radius = 12.34;
    const auto x = get_x(g.get_player(0)) + (0.99 * radius);
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
  }
  //If a projectile is 1.01 of its radius right of a player, there is no collision
  {
    game g;
    const double radius = 12.34;
    const auto x = get_x(g.get_player(0)) + (1.01*radius);
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
  }

  // In the start of the game, there is no player-food collision
  {
    game g;
    assert(!has_any_player_food_collision(g));
  }

  //Can modify food items, for example, delete all food items
  {
    game g;
    g.get_food();
    assert(!g.get_food().empty());
    g.get_food().clear();
    assert(g.get_food().empty());
  }


  //Initially, there is no collision with a projectile
  {
    game g;
    assert(!has_any_player_projectile_collision(g));
  }
  //If a projectile is put on top of a player, there is a collision
  {
    game g;
    const auto x = get_x(g.get_player(0));
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    add_projectile(g, projectile(c));
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
  }
  //If a projectile is 0.99 of its radius right of a player, there is a collision
  {
    game g;
    const double radius = 12.34;
    const auto x = get_x(g.get_player(0)) + (0.99 * radius);
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
  }
  //If a projectile is 1.01 of its radius right of a player, there is no collision
  {
    game g;
    const double radius = 12.34;
    const auto x = get_x(g.get_player(0)) + (1.01*radius);
    const auto y = get_y(g.get_player(0));
    const coordinate c{x, y};
    const projectile p(c, 0.0, projectile_type::rocket, radius);
    add_projectile(g, p);
    assert(!g.get_projectiles().empty());
    assert(has_any_player_projectile_collision(g));
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
    assert(!has_any_player_food_collision(g));
  }

  //Can modify food items, for example, delete all food items
  {
    game g;
    g.get_food();
    assert(!g.get_food().empty());
    g.get_food().clear();
    assert(g.get_food().empty());
  }


#define FIX_ISSUE_VALENTINES_DAY
#ifdef FIX_ISSUE_VALENTINES_DAY
  //If green eats blue then green survives
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
#endif // FIX_ISSUE_VALENTINES_DAY

  //A game is initialized with walls, the walls form a 16:9
  //rectangle with center at coordinates of 0,0
  //And short size = 720 by default;
  {
    double wall_short_side = 720.0;
    environment some_environment = environment(wall_short_side);
    game_options options;
    game g(options,some_environment);
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
    const double before = get_x(g.get_shelters()[0]);
    g.tick();
    const double after = get_x(g.get_shelters()[0]);
    assert(std::abs(after - before) > 0.0);
  }

  #define FIX_ISSUE_405
  #ifdef FIX_ISSUE_405
  {
    // nth shelter position can be obtained
    game g;
    int n = 0;
    shelter first_shelter = g.get_shelters()[n];
    coordinate expected_c = first_shelter.get_position();

    coordinate c = get_nth_shelter_position(g, n);

    assert(c == expected_c);
  }
  #endif

  {
    // the position of all shelters can be obtained

    const double wall_short_side = 1600;
    const int num_players = 0;
    const int n_shelters = 5;

    const game g(game_options(), wall_short_side, num_players, n_shelters);

    std::vector<coordinate> expected_shelter_positions;
    for (int n = 0; n < n_shelters; ++n)
    {
      const coordinate nth_shelter_position = get_nth_shelter_position(g, n);
      expected_shelter_positions.push_back(nth_shelter_position);
    }

    std::vector<coordinate> shelter_positions = get_all_shelter_positions(g);

    assert(shelter_positions.size() == expected_shelter_positions.size());
    for (int n = 0; n < n_shelters; ++n)
    {
      assert(shelter_positions[n] == expected_shelter_positions[n]);
    }
  }

  // Initial shelters are at random locations over the whole arena
  {
    const game game_1(game_options(2));
    const game game_2(game_options(3));

    const auto shelter_positions_1 = get_all_shelter_positions(game_1);
    assert(!shelter_positions_1.empty());
    const auto shelter_positions_2 = get_all_shelter_positions(game_2);
    assert(shelter_positions_1.size() == shelter_positions_2.size());
    assert(!all_positions_equal(shelter_positions_1, shelter_positions_2));
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
    p.accelerate();
    //Move the player into a wall
    p.move();
    assert(hits_north_wall(p, g.get_env()));

    /// manage the collision
    p = g.resolve_wall_collision(p);

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

#define FIX_ISSUE_236
#ifdef FIX_ISSUE_236
  //When a player touches food it eats it
  {
    game g;
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    assert(has_uneaten_food(g));
    assert(has_any_player_food_collision(g));
    g.tick();
    assert(!has_uneaten_food(g));
    assert(!has_any_player_food_collision(g));
  }
#endif

  // #392: When a player gets within the radius of food it eats it
  {
    game g;
    food f = g.get_food()[0];
    double food_radius = f.get_radius();
    double player_radius = get_nth_player_size(g, 0) / 2;
    double no_collision_distance = food_radius + player_radius;

    // Player at food radius should not trigger collision
    put_player_near_food(g.get_player(0), f, no_collision_distance);
    assert(!has_any_player_food_collision(g));
    g.tick();
    assert(has_uneaten_food(g));
    // Player within food radius should trigger collision
    put_player_near_food(g.get_player(0), f, no_collision_distance - 1.0);
    assert(has_any_player_food_collision(g));
    g.tick();
    assert(!has_uneaten_food(g));
    assert(!has_any_player_food_collision(g));

  }
  #ifdef FIX_ISSUE_440
  // #440: Food changes the color of the player
  {
    game g;
    const food f = g.get_food()[0];
    // Food must be of a different color than the player,
    // else nothing happens to the color of the player
    const color food_color = f.get_color();
    const color player_color = g.get_player(0).get_color();
    assert(food_color != player_color);

    const color color_before = player_color;

    put_player_on_food(g.get_player(0), f);
    g.tick();

    const color color_after = g.get_player(0).get_color();
    assert(color_before != color_after);
  }
  #endif // FIX_ISSUE_440

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

#define FIX_ISSUE_238
#ifdef FIX_ISSUE_238
  // The game can be checked for any collision between food and players
  {
    game g;
    assert(!has_any_player_food_collision(g));
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    assert(has_any_player_food_collision(g));
  }
#endif

#define FIX_ISSUE_244
#ifdef FIX_ISSUE_244
  {
    game g;
    const auto init_player_size = get_nth_player_size(g,0);
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    g.tick();
    assert(g.get_player(0).get_diameter() > init_player_size);
  }

#endif

#define FIX_ISSUE_247
#ifdef FIX_ISSUE_247
  {
    coordinate c_p(0, 0);
    player p(c_p);
    coordinate c_f(1000, 0);
    food f{c_f};
    assert(!are_colliding(p, f));
    put_player_on_food(p, f);
    assert(are_colliding(p, f));
  }
#endif // FIX_ISSUE_247

#ifdef FIX_ISSUE_248

  {
    game g;
    auto first_player_diam = get_nth_player_size(g,0);
    assert(first_player_diam = g.get_player(0).get_diameter());
  }
#endif

#define FIX_ISSUE_254
#ifdef FIX_ISSUE_254
  {
    game g;
    put_player_on_food(g.get_player(0), g.get_food()[0]);
    g.tick();
    assert(g.get_food()[0].is_eaten());
  }
#endif

  // (340) make sure that eat_nth_food() throws a logic_error when the food is already eaten
  {
    game g; //by default one uneaten food
    assert(has_uneaten_food(g));
    eat_nth_food(g, 0);
    assert(!has_uneaten_food(g));
    try {
      eat_nth_food(g, 0); // throws exception
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
    assert(has_uneaten_food(g));
    eat_nth_food(g, 0);
    assert(!has_uneaten_food(g));
    assert(n_food_items_begin == count_food_items(g));
  }

#define FIX_ISSUE_256
#ifdef FIX_ISSUE_256
  {
    food f;
    player p;
    put_player_on_food(p, f);
    assert(are_colliding(p,f));
    f.set_food_state(food_state::eaten);
    assert(!are_colliding(p,f));
  }
#endif

#define FIX_ISSUE_259
#ifdef FIX_ISSUE_259
  {
    game g; //by default one uneaten food
    assert(has_uneaten_food(g));
    auto initial_value_timer = get_nth_food_timer(g, 0);
    eat_nth_food(g, 0);
    assert(!has_uneaten_food(g));
    g.tick();
    assert(initial_value_timer + 1  == get_nth_food_timer(g, 0));
  }
#endif

#define FIX_ISSUE_255
#ifdef FIX_ISSUE_255
  {
    game g;
    eat_nth_food(g, 0);
    assert(is_nth_food_eaten(g,0));
    for(int i = 0; i != get_nth_food_regeneration_time(g, 0); i++)
      {
        g.tick();
      }
    assert(!is_nth_food_eaten(g,0));
  }
#endif


#define FIX_ISSUE_394
#ifdef FIX_ISSUE_394
  {
    game g;
    food f = g.get_food()[0];
    int f_regen_time = f.get_regeneration_time();

    // Player on top of food should eat it
    assert(!is_nth_food_eaten(g, 0));
    put_player_on_food(g.get_player(0), f);
    g.tick();
    assert(is_nth_food_eaten(g, 0));
    // Get player away so it does not eat food again
    put_player_near_food(g.get_player(0), f, f.get_radius() * 2.0);

    // Food item should not regen before the regeneration time
    for(int i = 0; i != f_regen_time; i++)
      {
        assert(is_nth_food_eaten(g,0));
        g.tick();
      }
    // Food item should regen on the regeneration time
    assert(!is_nth_food_eaten(g,0));
  }
#endif

#define FIX_ISSUE_400
#ifdef FIX_ISSUE_400
  // A game's min and max coordinates can be accessed quickly
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
#endif


  //Food can be placed at a random location
  {
    const double wall_short_side = 1600;
    const int num_players = 3;
    const std::size_t n_shelters = 42;
    const int n_enemies = 1;
    const int n_food = 2;
    game g(
      game_options(),
      wall_short_side,
      num_players,
      n_shelters,
      n_enemies,
      n_food
    );
    assert(g.get_food().size() >= 2);

    // The two food items are still in the same spot
    assert(get_nth_food_x(g, 0) == get_nth_food_x(g, 1));
    assert(get_nth_food_y(g, 0) == get_nth_food_y(g, 1));

    place_nth_food_randomly(g, 0);
    // Food item 0 is no longer on the same spot
    assert(get_nth_food_x(g, 0) != get_nth_food_x(g, 1));
    assert(get_nth_food_y(g, 0) != get_nth_food_y(g, 1));

    place_nth_food_randomly(g, 1);
    // Food item 0 and 1 are not placed on the same spot
    assert(get_nth_food_x(g, 0) != get_nth_food_x(g, 1));
    assert(get_nth_food_y(g, 0) != get_nth_food_y(g, 1));
  }

  #define FIX_ISSUE_403
  #ifdef FIX_ISSUE_403
  {
    // Food item's state can be accessed easily
    game g;
    assert(!is_nth_food_eaten(g, 0));
    eat_nth_food(g, 0);
    assert(is_nth_food_eaten(g, 0));
  }
  #endif

  #define FIX_ISSUE_404
  #ifdef FIX_ISSUE_404
  {
    // Food item position can be accessed easily
    game g;
    coordinate default_food_position = coordinate(2000, 1000);
    assert(get_nth_food_position(g, 0) == default_food_position);
  }
  #endif

#define FIX_ISSUE_257
#ifdef FIX_ISSUE_257
  {
    // A food that returns to the uneaten state is relocated at random
    game g;
    assert(!is_nth_food_eaten(g, 0));
    coordinate food_pos_before = get_nth_food_position(g, 0);
    eat_nth_food(g, 0);
    // Tick until food regens
    while (is_nth_food_eaten(g, 0)) {
      g.tick();
    }
    coordinate food_pos_after = get_nth_food_position(g, 0);
    assert(food_pos_after != food_pos_before);
  }
#endif

// #define FIX_ISSUE_286
#ifdef FIX_ISSUE_286
  {
    // #286 Food items are placed at random at game initialization

    // default game arguments
    double short_wall_side = 1600;
    int n_players = 0;
    int n_ticks = 0;
    int n_shelters = 0;
    int n_enemies = 0;
    int n_food = 1;

    int a_seed = 1;
    game a_game(short_wall_side,
           n_players,
           n_ticks,
           n_shelters,
           n_enemies,
           n_food,
           a_seed
           );
    coordinate food_position = get_nth_food_position(a_game, 0);

    int another_seed = 2;
    game another_game(short_wall_side,
           n_players,
           n_ticks,
           n_shelters,
           n_enemies,
           n_food,
           another_seed
           );
    coordinate other_food_position = get_nth_food_position(another_game, 0);

    assert(food_position != other_food_position);
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

  {
    // default game arguments
    const double short_wall_side = 1600;
    const int n_players = 0;
    const int n_shelters = 0;
    const int n_enemies = 0;
    const int n_food = 0;

    const int seed = 123456789;
    game g(
      game_options(seed),
      short_wall_side,
      n_players,
      n_shelters,
      n_enemies,
      n_food
    );
    std::mt19937 expected_rng(seed);
    assert(g.get_rng()() - expected_rng() < 0.00001 &&
           g.get_rng()() - expected_rng() > -0.00001);
  }

#define FIX_ISSUE_321
#ifdef FIX_ISSUE_321
  {
    coordinate Some_random_point(1,1);
    food n_food(Some_random_point);
    player n_player(Some_random_point);
    projectile n_projectile(Some_random_point);
    shelter n_shelter(Some_random_point);
    enemy n_enemy(Some_random_point);

    assert(have_same_position(n_food, Some_random_point));
    assert(have_same_position(n_player, Some_random_point));
    assert(have_same_position(n_projectile, Some_random_point));
  }
#endif

  #define FIX_ISSUE_241
  #ifdef FIX_ISSUE_241
  //Player 1 can stun player 2 with a stun rocket
  {
    game g;

    // Shoot the stun rocket
    g.do_action(0, action_type::shoot_stun_rocket);
    g.tick();

    assert(count_n_projectiles(g) == 1 &&
           g.get_projectiles().back().get_type() == projectile_type::stun_rocket);

    // Put the stun rocket on top of player 2 (at index 1)
    g.get_projectiles().back().place({get_x(g.get_v_player()[1]), get_y(g.get_v_player()[1])});

    assert(get_x(g.get_projectiles().back()) == get_x(g.get_v_player()[1]));
    assert(get_y(g.get_projectiles().back()) == get_y(g.get_v_player()[1]));

    // Player 2 should not be stunned yet
    assert(!(is_stunned(g.get_v_player()[1])));

    // Stun rocket is there
    assert(count_n_projectiles(g) == 1);

    g.tick();

    // Stun rocket should disappear
    //THIS LINE DOESN't WORK
    assert(count_n_projectiles(g) == 0);

    // Player 2 is now stunned yet
    assert(is_stunned(g.get_v_player()[1]));
  }
  #endif // FIX_ISSUE_241

//#define FIX_ISSUE_457
#ifdef FIX_ISSUE_457
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
#endif

#define FIX_ISSUE_458
#ifdef FIX_ISSUE_458
  {
    // (458) The color of any food item can be accessed easily
    const game g;
    const color color_food = get_nth_food_color(g, 0);
    // Default color for the food item is black
    const color c;
    assert(color_food == c);
  }
#endif

#define FIX_ISSUE_471
#ifdef FIX_ISSUE_471
  {
    const game_options options;
    const game g(options);
    assert(g.get_game_options() == options);
  }
#endif

//#define FIX_ISSUE_472
#ifdef FIX_ISSUE_472
  {
    const game g;
    // Only check if this compiles, we do not care about the RNG seed
    assert(g.get_options().get_rng_seed() == 0
      || g.get_options().get_rng_seed() != 0);
  }
#endif

// #define FIX_ISSUE_464
#ifdef FIX_ISSUE_464
  {
    // (464) A player's state can be accessed easily
    const game g;
    assert(get_nth_player_state(g, 0) ==  g.get_players()[0].get_state());
  }
#endif

  //#define FIX_ISSUE_478
  #ifdef FIX_ISSUE_478
  // Saving a game and loading it, must result in the same game
  {
    const game g;
    const std::string filename = "test.txt";
    save(g, filename); // To prevent a bloated/Winnebago class
    const game h = load(filename);
    assert(g == h);
  }
  #endif // FIX_ISSUE_478

#endif // no tests in release
}


