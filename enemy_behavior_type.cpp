#include "enemy_behavior_type.h"

#include <cassert>
#include <sstream>
#include <vector>

void test_enemy_behavior_type()
{
  const enemy_behavior_type t{enemy_behavior_type::gezellig};
  const enemy_behavior_type u{enemy_behavior_type::shy};
  assert(t != u);
  //#define FIX_ISSUE_159
  #ifdef FIX_ISSUE_159
  {
    std::stringstream s;
    s << enemy_behavior_type::gezellig;
  }
  #endif //FIX_ISSUE_159
}
