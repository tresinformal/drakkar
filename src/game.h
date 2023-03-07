#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "action_type.h"
#include "environment.h"
#include "environment_type.h"
#include "game_options.h"
#include "player.h"
#include "player_shape.h"
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
    int num_players = 3
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

  /// Get environment size of the game
  const environment& get_env() const noexcept{ return m_environment; }

  /// Get the player at a specified index in the vector of players
  const player &get_player(int i) const { return m_player[static_cast<unsigned int>(i)]; }

  /// Get reference to player to change some parameters
  player &get_player(int i) {
    assert(i >= 0);
    assert(i < static_cast<int>(m_player.size()));
    return m_player[static_cast<unsigned int>(i)];
  }

  /// Returns const ref to the vector of players
  const std::vector<player> &get_v_player() const noexcept { return get_players(); }
  const std::vector<player> &get_players() const noexcept { return m_player; }

  /// Returns ref to the vector of players
  std::vector<player>& get_v_player() noexcept { return get_players(); }
  std::vector<player>& get_players() noexcept { return m_player; }

  /// Kills the index'th player (e.g. index 0 is the first player)
  /// Assumes that index exists, else crashes
  void kill_player(const int index);

  /// Apply inertia to player movement
  void apply_inertia();

  /// Applies default actions every tick
  void tick();

  /// Get initial x distance of players
  int get_dist_x_pls() const noexcept { return m_dist_x_pls; }

  /// Manages collisons with walls
  player resolve_wall_collision(player p);

  /// The options can be changed
  void set_options(const game_options& new_options) noexcept { m_options = new_options; }

  /// END GAME CONDITION ///
  /// Check whether the number of ticks >= max time, could extend this function in the future to detect more end game conditions
  void check_over();

  /// Return the flag to show whether the game is over
  bool is_over() const noexcept { return m_is_over; }
  /// END GAME CONDITION ///

  /// The biggest player wins
  std::string who_is_winning() const noexcept {
    auto p_biggest = m_player[0];
    for (auto& p : m_player) {
      if (p.get_diameter() > p_biggest.get_diameter())
        p_biggest = p;
    }
    return p_biggest.get_ID();
  }

private:

  /// The RNG engine
  std::mt19937 m_rng;

  /// The options of the game
  game_options m_options;

  /// The number of ticks
  int m_n_ticks;

  /// Vector of players
  std::vector<player> m_player;

  /// Vector of index of the players that collide
  std::vector<int> m_v_collisions_ind;

  /// The environment
  environment m_environment;

  /// Starting x distance between players
  const int m_dist_x_pls = 300;

  /// Flag to decide whether the game is over
  bool m_is_over = false;
};

/// Calculate a mean of a vector of numbers
double calc_mean(const std::vector<double>& v);

/// Calculate the variance of a vector of numbers
double calc_var(const std::vector<double>& v);

///Checks if two items have the same exact position
template <typename L, typename R>
bool have_same_position(const L& lhs, const R& rhs);

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

/// Save the game to file
void save(const game& g, const std::string& filename);

void test_game();

#endif // GAMELOGIC_H
