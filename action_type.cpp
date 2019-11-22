#include "action_type.h"
#include <assert.h>

void test_action_type()
{
  assert(to_str_act_type(action_type::turn_left) != to_str_act_type(action_type::turn_right));
  assert(to_str_act_type(action_type::accelerate) != to_str_act_type(action_type::brake));
  assert(1 == 2); // Issue 98
}

const std::string to_str_act_type(action_type this_action_type)

{

    switch (this_action_type)//!OCLINT
        //it might be wise to keep a default statement
        // in case for some reason an invalid input is given
{
    case action_type::turn_left:   return "turn_left";
    case action_type::turn_right:   return "turn_right";
    case action_type::accelerate:   return "accelerate";
    case action_type::brake:   return "brake";

    default:      return "[Unknown action_type]";
}

}
