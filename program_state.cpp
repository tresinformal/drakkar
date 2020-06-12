#include "program_state.h"
#include <cassert>
#include <sstream>

void test_program_state()
{
  assert(to_str(program_state::menu) !=
         to_str(program_state::paused));
  assert(to_str(program_state::paused) !=
         to_str(program_state::playing));
  assert(to_str(program_state::playing) !=
         to_str(program_state::menu));
  {
    std::stringstream s;
    s << program_state::menu;
  }
}

std::ostream &operator<<(std::ostream &os, const program_state t)
{
  os << to_str(t);
  return os;
}

std::string to_str(const program_state this_program_state) noexcept
{
  if(this_program_state == program_state::paused)
  {
    return "paused";
  }
  else if(this_program_state == program_state::playing)
  {
    return "playing";
  }
  assert(this_program_state == program_state::menu);
  return "menu";
}
