#include "game.h"
#include <cassert>

game::game(const int n_ticks)
    :m_n_ticks{n_ticks}
{

}

void test_game() {
  const game g;
  // n_ticks is the number of times the game is displayed on screen
  assert(g.get_n_ticks() == 0);
}
