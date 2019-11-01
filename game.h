#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "player_shape.h"
#include "player.h"
#include "environment_type.h"

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost

class game
{
public:
  game(const int n_ticks = 0,const environment_type environment = environment_type::empty);

  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  ///Get the player of the game
  const player& get_player() const { return m_player; }

  ///Get environemtn type of the game
   environment_type get_environment() const { return m_environment; }


private:

  ///the number of ticks
  int m_n_ticks;

  /// The player
  player m_player;

  /// the environment
  environment_type m_environment;

};

void test_game();

#endif // GAMELOGIC_H
