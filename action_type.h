#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

#include <string>

enum class action_type
{
  // Action types here
    turn_left,
    turn_right,
    accelerate,
    brake

};

void test_action_type();
const std::string to_str_act_type(action_type this_action_type);

#endif // ACTION_TYPE_H
