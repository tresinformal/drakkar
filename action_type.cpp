#include "action_type.h"
#include <cassert>
#include <sstream>

void test_action_type()
{
  // to_str
  {
    assert(to_str(action_type::turn_left) == "turn_left");
    assert(to_str(action_type::turn_right) == "turn_right");
    assert(to_str(action_type::accelerate) == "accelerate");
    assert(to_str(action_type::brake) == "brake");
    assert(to_str(action_type::acc_backward) == "acc_backward");
    assert(to_str(action_type::shoot) == "shoot");
    assert(to_str(action_type::none) == "none");
    #ifdef FIX_ISSUE_225
    assert(to_str(action_type::stun) == "stun");
    #endif // FIX_ISSUE_225
  }
  //
  {
    std::stringstream s;
    s << action_type::brake;
    assert(!s.str().empty());
  }
}

std::ostream &operator<<(std::ostream &os, const action_type t)
{
  os << to_str(t);
  return os;
}

const std::string to_str(action_type this_action_type)
{
  switch (this_action_type)
  {
  case action_type::turn_left:
    return "turn_left";
  case action_type::turn_right:
    return "turn_right";
  case action_type::accelerate:
    return "accelerate";
  case action_type::brake:
    return "brake";
  case action_type::acc_backward:
      return "acc_backward";
  case action_type::shoot:
      return "shoot";
  default:
    assert(this_action_type == action_type::none );
  return "none";
  }
}
