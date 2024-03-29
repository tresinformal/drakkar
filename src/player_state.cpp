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
  case player_state::dead:
    return "dead";
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
  {
    assert(player_state::dead != player_state::active);
  }

  // (509) operator<<
  {
    std::stringstream s;
    const player_state ps = player_state::active;
    s << ps;
    assert(!s.str().empty());
  }

  // (276) Conversion to string
  {
    assert(to_str(player_state::active) == "active");
    assert(to_str(player_state::dead) == "dead");
  }

  // #509: operator<<
  {
    std::stringstream s;
    const player_state ps = player_state::active;
    s << ps;
    assert(!s.str().empty());
  }
  #endif
}

