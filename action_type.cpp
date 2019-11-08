#include "action_type.h"

void test_action_type()
{
  #ifdef FIX_ISSUE_67
  assert(action_type::turn_left != action_type::turn_right);
  assert(action_type::accelerate != action_type::brake);
  #endif
}
