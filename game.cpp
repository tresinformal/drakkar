#include "game.h"
#include <cassert>
#include "player_shape.h"

game::game(const int n_ticks)
 : m_n_ticks{n_ticks},
   m_player{0.0, 0.0, player_shape::rocket}
{

}

void test_game()
{
  // The game has done zero ticks upon startup
  {
    const game g;
    // n_ticks is the number of times the game is displayed on screen
    assert(g.get_n_ticks() == 0);
  }
  // A game has a player
  {
    const game g;
    // The value 1234.5 is irrelevant: just get this to compile
    assert(g.get_player().get_x() > -1234.5);
  }
  #ifdef FIX_ISSUE_39
  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty);
  }
  #endif
}
