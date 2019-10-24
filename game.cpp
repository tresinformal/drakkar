#include "game.h"
#include <cassert>

game::game(const int n_ticks)
 : m_n_ticks{n_ticks}
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
  #ifdef FIX_ISSUE_37
  // A game has a player
  {
    const game g;
    assert(g.get_player().get_x() > -1234.5); // The value 1234.5 is irrelevant: just get this to compile
  }
  #endif
  #ifdef FIX_ISSUE_39
  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty);
  }
  #endif
}
