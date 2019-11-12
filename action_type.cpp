#include "action_type.h"
#include<assert.h>
void test_action_type()
{

  assert(action_type::turn_left != action_type::turn_right);
  assert(action_type::accelerate != action_type::brake);
}
