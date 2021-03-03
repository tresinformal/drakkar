#include "player_state.h"
#include <cassert>

void test_player_state()
{
  assert(player_state::active != player_state::stunned);
}
