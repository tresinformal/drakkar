#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "player_shape.h"
#include "player.h"
#include "environment.h"
#include "environment_type.h"
#include "action_type.h"

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost

class game
{
public:
  game(const int n_ticks = 0,const environment_type environment = environment_type::empty);

  ///makes the player in the game execute an action
  void do_action(action_type action);

  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  ///Get the player of the game
  const player& get_player() const { return m_player; }

  ///Get reference to player to change some parameters
  player& get_ref_player() { return m_player; }

  ///Get environment type of the game
   environment_type get_environment_type() const { return m_environment_type; }

   ///Get environment size of the game
   environment get_environment() const { return m_environment; }





private:

  ///the number of ticks
  int m_n_ticks;

  /// The player
  player m_player;

  /// the environment
  environment_type m_environment_type;

  /// the environment
  environment m_environment;
};

void test_game();

#endif // GAMELOGIC_H

///Get player directions
double get_player_direction(const game g);
