#include "action_type.h"
#include <cassert>
#include <sstream>

#ifdef HAS_MAGIC_ENUM // HAS_MAGIC_ENUM is defined in game.pro
#include "../magic_enum/include/magic_enum.hpp" // https://github.com/Neargye/magic_enum
#endif

void test_action_type()
{
  #ifndef NDEBUG // no tests is release
  // to_str
  {
    assert(to_str(action_type::turn_left) == "turn_left");
    assert(to_str(action_type::turn_right) == "turn_right");
    assert(to_str(action_type::accelerate_forward) == "accelerate_forward");
    assert(to_str(action_type::accelerate_backward) == "accelerate_backward");
    assert(to_str(action_type::idle) == "idle");
  }
  //
  {
    std::stringstream s;
    s << action_type::accelerate_backward;
    assert(!s.str().empty());
  }
#endif
}

std::ostream &operator<<(std::ostream &os, const action_type t)
{
  os << to_str(t);
  return os;
}

std::string to_str(const action_type this_action_type)
{
  #ifdef HAS_MAGIC_ENUM // HAS_MAGIC_ENUM is defined in game.pro
  return std::string(magic_enum::enum_name(this_action_type));
  #else
  switch (this_action_type)
  {
  case action_type::turn_left:
    return "turn_left";
  case action_type::turn_right:
    return "turn_right";
  case action_type::accelerate_forward:
    return "accelerate_forward";
  case action_type::accelerate_backward:
    return "accelerate_backward";
  default:
    assert(this_action_type == action_type::idle);
  return "idle";
  }
  #endif
}
