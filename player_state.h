#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H
#include <string>
enum class player_state
{
  active,
  dead,
  stunned
};

void test_player_state();

/// implement << operator
std::ostream& operator << (std::ostream& os, const player_state& state);

#endif // PLAYER_STATE_H
