#include "player_state.h"
#include "player.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <iostream>

std::string to_str(player_state this_player_state)
{
  switch (this_player_state)
  {
  case player_state::out:
    return "dead";
  case player_state::stunned:
    return "stunned";

  default:
    assert(this_player_state == player_state::active);
    return "active";
  }
}


std::ostream& operator << (std::ostream& os, const player_state& state)
{
    os << to_str(state);
    return os;
}

void test_player_state()
{
  #ifndef NDEBUG // no tests in release
  assert(player_state::active != player_state::stunned);
  {
    assert(player_state::out != player_state::stunned &&
              player_state::out != player_state::active);
  }

  #define FIX_ISSUE_509
  #ifdef FIX_ISSUE_509
  // operator<<
  {
    std::stringstream s;
    const player_state ps = player_state::active;
    s << ps;
    assert(!s.str().empty());
  }
  #endif // FIX_ISSUE_509

  #define FIX_ISSUE_276
  #ifdef FIX_ISSUE_276
  // Conversion to string
  {
    assert(to_str(player_state::active) == "active");
    assert(to_str(player_state::out) == "dead");
    assert(to_str(player_state::stunned) == "stunned");
  }
  #endif // FIX_ISSUE_276

  // #509: operator<<
  {
    std::stringstream s;
    const player_state ps = player_state::active;
    s << ps;
    assert(!s.str().empty());
  }

#define FIX_ISSUE_606
#ifdef FIX_ISSUE_606
  {
    // (606) When a player goes under some size, it is out
    player p;
    double death_size; // choose a value
    // smh make the player smaller
    while(p.get_diameter() > death_size)
      {
        assert(p.get_state() != player_state::out);
        p.shrink();
      }
    assert(p.get_state() == player_state::out);
  }
#endif

  #endif
}

