#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "player.h"

/// Contains the game logic.
/// All data types used by this class are STL and/or Boost
class game
{
public:
  game(const int n_ticks = 0);

  /// return the number of ticks
  int get_n_ticks() const noexcept { return m_n_ticks; }

  ///Get the player of the game
  const player& get_player() const { return m_player; }

private:

  ///the number of ticks
  int m_n_ticks;

  /// The player
  player m_player;

};

void test_game();

#endif // GAMELOGIC_H
