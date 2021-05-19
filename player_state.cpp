#include "player_state.h"
#include <cassert>
#include <sstream>

std::string to_str(player_state this_env_type)
{
  switch (this_env_type)
  {
  case player_state::empty:
    return "empty";
  case player_state::quiet:
    return "quiet";
  case player_state::random:
    return "random";
  case player_state::attractive:
    return "attractive";
  case player_state::repellent:
    return "repellent";

  default:
    assert(this_env_type == player_state::wormhole);
    return "wormhole";
  }
}


void test_player_state()
{
  #ifndef NDEBUG // no tests in release
  assert(player_state::active != player_state::stunned);
  {
    assert(player_state::dead != player_state::stunned &&
              player_state::dead != player_state::active);
  }




  #define FIX_ISSUE_276
  #ifdef FIX_ISSUE_276
  // Conversion to string
  {
    assert(to_str(player_state::active) == "active");
    assert(to_str(player_state::dead) == "dead");
    assert(to_str(player_state::stunned) == "stunned");
  }
  #endif // FIX_ISSUE_276
  #endif
}
