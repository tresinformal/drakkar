#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

#include <iosfwd>
#include <string>

enum class action_type
{
  turn_left,
  turn_right,
  accelerate_forward,
  accelerate_backward,
  shoot,
  idle,
  shoot_stun_rocket
};

void test_action_type();
std::string to_str(const action_type this_action_type);
std::ostream &operator<<(std::ostream &os, const action_type t);

#endif // ACTION_TYPE_H
