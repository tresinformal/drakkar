#include "action_type.h"
#include <cassert>
#include <sstream>

void test_action_type()
{
  #ifndef NDEBUG // no tests is release
  // to_str
  {
    assert(to_str(action_type::turn_left) == "turn_left");
    assert(to_str(action_type::turn_right) == "turn_right");
    assert(to_str(action_type::accelerate_forward) == "accelerate_forward");
    assert(to_str(action_type::accelerate_backward) == "accelerate_backward");
    assert(to_str(action_type::shoot) == "shoot");
    assert(to_str(action_type::none) == "none");
    assert(to_str(action_type::shoot_stun_rocket) == "shoot_stun_rocket");
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
  case action_type::shoot:
      return "shoot";
  case action_type::shoot_stun_rocket:
      return "shoot_stun_rocket";
  default:
    assert(this_action_type == action_type::none );
  return "none";
  }
}
