#include "game.h"
#include "projectile.h"
#include "projectile_type.h"

#include <cassert>
#include <cmath>
#include <iostream>

game::game(double wall_short_side, int num_players, int n_ticks , size_t n_shelters)
  :
    m_n_ticks{n_ticks},
    m_v_player(static_cast<unsigned int>(num_players), player()),
    m_enemies{1},
    m_environment(wall_short_side),
    m_food{1},
    m_shelters(n_shelters)
{
  for (unsigned int i = 0; i != m_v_player.size(); ++i)
    {
      m_v_player[i] =
          player(300.0 + static_cast<unsigned int>(m_dist_x_pls) * i, 400.0, player_shape::rocket);
    }
  // Set color
  {
    int i = 0;
    for (auto &player : m_v_player)
      {
        player.set_color(color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0,
                               i % 3 == 2 ? 255 : 0));
        ++i;
      }
  }
  // Set shelters
  {
    assert(m_shelters.size() == 3);
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

int count_n_projectiles(const game &g) noexcept
{
  return static_cast<int>(g.get_projectiles().size());
}

void game::do_action(const int player_index, action_type action)
{
  assert(player_index >= 0);
  assert(player_index < static_cast<int>(m_v_player.size()));
  do_action(m_v_player[player_index], action);
}

void game::do_action( player& player, action_type action)
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
    case action_type::none:
      return;
    }
}

void game::do_actions() noexcept
{
  for(auto& player: m_v_player)
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

  for (auto& player: m_v_player)
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
      p.set_type(projectile_type::rocket);
      p.move();
    }
}

void game::tick()
{
  //if collision abort game
  if(has_collision(*this))
    {
      kill_losing_player(*this);
    }

  // Moves the projectiles
  move_projectiles();

  // for now only applies inertia
  apply_inertia();

  //move shelters
  move_shelter();

  //Actions issued by the players are executed
  do_actions();

  // players that shoot must generate projectiles
  for (player &p : m_v_player)
    {
      // When a player shoots, 'm_is_shooting' is true for one tick.
      // 'game' reads 'm_is_shooting' and if it is true,
      // it (1) creates a projectile, (2) sets 'm_is_shooting' to false
      if (p.is_shooting())
        {
          // Put the projectile just in front outside of the player
          const double d{p.get_direction()};
          const double x{p.get_x() + (std::cos(d) * p.get_diameter() * 1.1)};
          const double y{p.get_y() + (std::sin(d) * p.get_diameter() * 1.1)};
          m_projectiles.push_back(projectile(x, y, d));
        }
      p.stop_shooting();
      assert(!p.is_shooting());
    }

  // and updates m_n_ticks
  ++get_n_ticks();
}

bool has_collision(const game &g) noexcept
{
  const auto n_players = static_cast<int>(g.get_v_player().size()) ;
  for (int i = 0; i < n_players; ++i)
    {
      for (int j = i + 1; j < n_players; ++j)
        {
          if (are_colliding(g.get_player(i), g.get_player(j)))
            {
              return true;
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
  const double dx = std::abs(p.get_x() - pl.get_x());
  const double dy = std::abs(p.get_y() - pl.get_y());
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

bool has_enemy_collision(const game&)
{
  return false;
}

bool has_food_collision(const game &) noexcept
{
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

void game::kill_player(const int index)
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_v_player.size()));
  this->m_v_player.erase(
        m_v_player.begin() + index
        );
}

void test_game() //!OCLINT tests may be many
{
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
  // A game responds to actions: player can turn left
  {
    game g;
    for (auto i = 0; i < static_cast< int>(g.get_v_player().size()); ++i)
      {
        const double before{g.get_player(i).get_direction()};
        g.do_action(i,action_type::turn_left);
        const double after{g.get_player(i).get_direction()};
        assert(std::abs(before - after) > 0.01); // Should be different
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
        assert(std::abs(before - after) > 0.01); // Should be different
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
    assert(count_n_projectiles(g) == 0);
    g.do_action(0, action_type::shoot);
    // Without a tick, no projectile is formed yet
    assert(count_n_projectiles(g) == 0);
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
    g.do_action(0, action_type::shoot);
    g.tick();
    assert(count_n_projectiles(g) == 1);
    const double x_before{g.get_projectiles()[0].get_x()};
    const double y_before{g.get_projectiles()[0].get_y()};
    g.tick();
    const double x_after{g.get_projectiles()[0].get_x()};
    const double y_after{g.get_projectiles()[0].get_y()};
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
  // A collision destroys a player
  {
    game g;
    const auto n_players_before = g.get_v_player().size();
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    const auto n_players_after = g.get_v_player().size();
    assert(n_players_after < n_players_before);
  }
  // A collision destroy one of the colliding player
  {
    game g;
    const auto n_players_before = g.get_v_player().size();
    g.get_player(1).set_x(g.get_player(0).get_x());
    g.get_player(1).set_y(g.get_player(0).get_y());
    assert(has_collision(g));
    g.tick();
    const auto n_players_after = g.get_v_player().size();
    assert(n_players_after < n_players_before);
    assert(!has_collision(g));
    g.tick();
    const auto n_player_afteragain = g.get_v_player().size();
    assert(n_player_afteragain == n_players_after);
  }

  // Blue (player index 2) defeats red (player index 0)
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
    assert(g.get_v_player().size() == 2); //Red has died!
    assert(is_green(g.get_player(0)));
    assert(is_blue(g.get_player(1)));
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
    add_projectile(g, projectile(x, y));
    assert(!g.get_projectiles().empty());
    assert(has_collision_with_projectile(g));
  }
  //If a projectile is 0.99 of its radius right of a player, there is a collision
  {
    game g;
    const double radius = 12.34;
    const auto x = g.get_player(0).get_x() + (0.99 * radius);
    const auto y = g.get_player(0).get_y();
    const projectile p(x, y, 0.0, projectile_type::rocket, radius);
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
    const projectile p(x, y, 0.0, projectile_type::rocket, radius);
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
    assert(is_red(g.get_player(0)));
    assert(is_blue(g.get_player(1)));
  }
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

  //shelter moves with ever tick
  {
    game g;
    for (auto i = 0; i < static_cast<int>(g.get_shelters().size()); ++i)
      {//selected shelter is moving with each tick
        double before=g.get_shelters()[i].get_x();
        g.tick();
        g.tick();
        double after=g.get_shelters()[i].get_x();
        assert(after-before > 0.0000000000000001);
      }
  }
}

