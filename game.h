#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include "player_shape.h"
#include "player.h"
#include "environment.h"
#include "environment_type.h"
#include "action_type.h"
#include "food.h"
#include "enemy.h"

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost
class game
{
public:
  game(const int n_ticks = 0,
       const environment_type environment = environment_type::empty,
       unsigned int num_players = 2);



  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  ///Gets reference adress of number of ticks
  int& get_n_ticks() noexcept { return m_n_ticks; }

  ///Gets the player direction
  double get_player_direction(unsigned int player_ind);

  ///Get the vector of players
  const std::vector<player>& get_v_player() const {return m_v_player;}

  ///Get the player at a specified index in the vector of players
  const player& get_player(unsigned int i) const { return m_v_player[i]; }

  ///Get reference to player to change some parameters
  player& get_player(unsigned int i) { return m_v_player[i]; }

  ///Get environment type of the game
  environment_type get_environment_type() const { return m_environment_type; }

  ///Get environment size of the game
  environment get_environment() const { return m_environment; }

  ///Get food
  std::vector<food> get_food() const {return m_food; }

  ///Get enemies
  std::vector<enemy> get_enemies() const{return m_enemies;}

  ///Apply inertia to player movement
  void apply_inertia();

  ///Applies default actions every tick
  void tick();

  ///Get initial x distance of players
  unsigned int get_dist_x_pls() const noexcept{return m_dist_x_pls;}

private:

  ///the number of ticks
  int m_n_ticks;

  /// The player
  std::vector<player> m_v_player;

  /// the environment
  environment_type m_environment_type;

  /// the environment
  environment m_environment;

  /// the food
  std::vector<food> m_food;

  /// the enemies
  std::vector<enemy>m_enemies;

  /// starting x distance between players
  unsigned int m_dist_x_pls = 100;
};

void test_game();


#endif // GAMELOGIC_H
