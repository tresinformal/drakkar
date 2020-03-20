#include "program_state.h"
#include <cassert>
#include <sstream>

void test_program_state()
{
  assert(to_str_prog_state(program_state::menu) !=
         to_str_prog_state(program_state::paused));
  assert(to_str_prog_state(program_state::paused) !=
         to_str_prog_state(program_state::playing));
  assert(to_str_prog_state(program_state::playing) !=
         to_str_prog_state(program_state::menu));
  {
    std::stringstream s;
    s << program_state::menu;
  }
}

std::ostream &operator<<(std::ostream &os, const program_state t)
{
  os << to_str_prog_state(t);
  return os;
}

const std::string to_str_prog_state(program_state this_program_state)
{
  switch (this_program_state)
  {
  case program_state::paused:
    return "paused";
  case program_state::playing:
    return "playing";
  default:
    assert(this_program_state == program_state::menu);
    return "menu";
  }
}
