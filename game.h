#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "action_type.h"
#include "enemy.h"
#include "environment.h"
#include "environment_type.h"
#include "food.h"
#include "player.h"
#include "player_shape.h"
#include "projectile.h"
#include "shelter.h"
#include <vector>

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost
class game
{
public:
  game(double wall_short_side = 1600, int num_players = 3, int n_ticks = 0, std::size_t n_shelters = 3);

  ///makes a player do an action
  void do_action(int player_index, action_type action);

  ///makes a player do an action
  void do_action(player& player_index, action_type action);

  ///Executes all actions issued by all players, called in tick()
  void do_actions() noexcept;

  ///Executes for wall collision for all players
  void do_wall_collisions();

  ///returns the collision vector
  const std::vector<int>& get_collision_vec(){return m_v_collisions_ind;}

  ///sets the collision vector
  void set_collision_vector(int lhs, int rhs);

  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  /// Gets reference adress of number of ticks
  int &get_n_ticks() noexcept { return m_n_ticks; }

  /// Get environment size of the game
  const environment& get_env() const noexcept{ return m_environment; }

  /// Get enemies
  const std::vector<enemy>& get_enemies() const noexcept { return m_enemies; }

  /// Get const reference to food vector
  const std::vector<food>& get_food() const noexcept { return m_food; }

  /// Get reference to food vector
  std::vector<food>& get_food()  noexcept { return m_food; }

  /// Get the player at a specified index in the vector of players
  const player &get_player(int i) const { return m_player[static_cast<unsigned int>(i)]; }

  /// Get reference to player to change some parameters
  player &get_player(int i) { return m_player[static_cast<unsigned int>(i)]; }

  /// Gets the player direction
  double get_player_direction(int player_ind);

  /// Returns const ref to the vector of players
  const std::vector<player> &get_v_player() const { return m_player; }

  /// Returns ref to the vector of players
  std::vector<player>& get_v_player() { return m_player; }

  /// Get the projectiles
  const std::vector<projectile> &get_projectiles() const noexcept
  {
    return m_projectiles;
  }

  /// Get the projectiles
  std::vector<projectile> &get_projectiles() noexcept
  {
    return m_projectiles;
  }

  /// Get enemies
  const std::vector<shelter>& get_shelters() const noexcept { return m_shelters; }

  /// Kills the index'th player (e.g. index 0 is the first player)
  /// Assumes that index exists, else crashes
  void kill_player(const int index);

  /// Apply inertia to player movement
  void apply_inertia();

  /// Move shelter around - for simplicity, in straight line back and forth
  void move_shelter();

  /// Applies default actions every tick
  void tick();

  /// Get initial x distance of players
  int get_dist_x_pls() const noexcept { return m_dist_x_pls; }

  ///Manages collisons with walls
  player wall_collision(player p);

private:
  /// the number of ticks
  int m_n_ticks;

  /// Vector of players
  std::vector<player> m_player;

  ///Vector of index of the players that collide
  std::vector<int> m_v_collisions_ind;

  /// the enemies
  std::vector<enemy> m_enemies;

  /// the environment
  environment m_environment;

  /// the food
  std::vector<food> m_food;

  /// the projectiles
  std::vector<projectile> m_projectiles;

  /// the shelters
  std::vector<shelter> m_shelters;

  /// starting x distance between players
  const int m_dist_x_pls = 300;

  /// Moves the projectiles
  void move_projectiles();
};

/// Add a projectile to the game
void add_projectile(game& g, const projectile& p);

/// Count the number of projectiles in the game
int count_n_projectiles(const game &g) noexcept;

/// checks if there is at least one collision between players in the game
bool has_collision(const game &g) noexcept;

/// Determines if the player and projectile collide
bool has_collision(const player& pl, const projectile& p);

/// Is there a collision between an enemy and player?
bool has_enemy_collision(const game& g);

///Checks if there are collisions with food items
bool has_food_collision(const game &) noexcept;

/// checks if there is at least one collision between a player
/// and a projectile in the game
bool has_collision_with_projectile(const game &) noexcept;

///Signal if a player hits a wall in an environment
bool hits_wall(const player& p, const environment& e);

std::vector<int> get_collision_members(const game &g) noexcept;

/// Upon a collision, kills the player that loser
/// Assumes there is a collision
void kill_losing_player(game &);

void test_game();

#endif // GAMELOGIC_H
