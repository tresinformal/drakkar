#include "enemy_behavior_type.h"

#include <cassert>
void test_enemy_behavior_type()
{
  enemy_behavior_type t = enemy_behavior_type::gezellig;
  enemy_behavior_type u = enemy_behavior_type::shy;
  assert(t != u);
}
