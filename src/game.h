#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "action_type.h"
#include "environment.h"
#include "environment_type.h"
#include "food.h"
#include "game_options.h"
#include "player.h"
#include "player_shape.h"
#include "shelter.h"
#include <vector>
#include <cassert>
#include <random>

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost
class game
{
public:
  game(
    const game_options& options = game_options(),
    const environment& the_environment = environment(),
    int num_players = 3,
    std::size_t n_shelters = 42,
    int n_food = 1
  );

  ///makes a player do an action
  void do_action(int player_index, action_type action);

  ///makes a player do an action
  void do_action(player& player_index, action_type action);

  /// Reset players' actions
  void reset_player_action();

  ///Executes all actions issued by all players, called in tick()
  void do_actions() noexcept;

  ///Executes for wall collision for all players
  void resolve_wall_collisions();

  ///returns the collision vector
  const std::vector<int>& get_collision_vec(){return m_v_collisions_ind;}

  /// Get the game's options
  const game_options& get_game_options() const noexcept { return m_options; }

  /// Get the random number generator engine
  std::mt19937& get_rng() noexcept { return m_rng; }

  ///sets the collision vector
  void set_collision_vector(int lhs, int rhs);

  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  /// Increment the number of ticks
  void increment_n_ticks();
    
  // Switch a food item's state to eaten
  void eat_food(food& f);

  /// Get environment size of the game
  const environment& get_env() const noexcept{ return m_environment; }

  /// Get const reference to food vector
  const std::vector<food>& get_food() const noexcept { return m_food; }

  /// Get reference to food vector
  std::vector<food>& get_food()  noexcept { return m_food; }

  /// Get the player at a specified index in the vector of players
  const player &get_player(int i) const { return m_player[static_cast<unsigned int>(i)]; }

  /// Get reference to player to change some parameters
  player &get_player(int i) {
    assert(i >= 0);
    assert(i < static_cast<int>(m_player.size()));
    return m_player[static_cast<unsigned int>(i)];
  }

  /// Returns const ref to the vector of players
  const std::vector<player> &get_v_player() const { return m_player; }

  /// Returns ref to the vector of players
  std::vector<player>& get_v_player() { return m_player; }

  /// Get shelters
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
  player resolve_wall_collision(player p);
  
  /// The options can be changed
  void set_options(const game_options& new_options) noexcept { m_options = new_options; }

private:

  /// The RNG engine
  std::mt19937 m_rng;

  /// the options of the game
  game_options m_options;

  /// the number of ticks
  int m_n_ticks;

  /// Vector of players
  std::vector<player> m_player;

  ///Vector of index of the players that collide
  std::vector<int> m_v_collisions_ind;

  /// the environment
  environment m_environment;

  /// the food
  std::vector<food> m_food;

  /// the shelters
  std::vector<shelter> m_shelters;

  /// starting x distance between players
  const int m_dist_x_pls = 300;

  /// Increment timers of food items
  void increment_food_timers();

  /// Make players eat food items they are on top of
  void make_players_eat_food();

  /// Regenerate food items where relevant
  void regenerate_food_items();
};

/// Calculate a mean of a vector of numbers
double calc_mean(const std::vector<double>& v);

/// Calculate the variance of a vector of numbers
double calc_var(const std::vector<double>& v);

// Eat nth food item
void eat_nth_food(game& g, const int n);

///Checks if two items have the same exact position
template <typename L, typename R>
bool have_same_position(const L& lhs, const R& rhs);

bool is_in_food_radius(const player p, const food f) noexcept;

///Signal if a player hits a wall in an environment
bool hits_wall(const player& p, const environment& e);
bool hits_south_wall(const player& p, const environment& e);
bool hits_north_wall(const player& p, const environment& e);
bool hits_east_wall(const player& p, const environment& e);
bool hits_west_wall(const player& p, const environment& e);

///Upon a collision, grows the size of the winning player
void grow_winning_player(game &g);

///Upon a collision, shrink the size of the losing player
void shrink_losing_player(game &g);

///Puts a player on food
void put_player_on_food(player& p, const food &f);

///Puts a player on food
void put_player_near_food(player& p, const food &f, const double distance = 0.0);

/// Check that player and food are in collision, i.e. same position and food uneaten
bool are_colliding(const player &p, const food &f);

/// Place a food item at a random position
void place_nth_food_randomly(game &g, const int &n);

/// Check if one or more shelters share the same position
bool all_positions_equal(const std::vector<coordinate> &shelters, const std::vector<coordinate> &other_shelters) noexcept;

/// Save the game to file
void save(const game& g, const std::string& filename);

void test_game();

#endif // GAMELOGIC_H
