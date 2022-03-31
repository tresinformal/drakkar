#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <iosfwd>

enum class player_state
{
  active,
  dead,
  stunned
};

void test_player_state();

std::ostream& operator << (std::ostream& os, const player_state& state);

#endif // PLAYER_STATE_H
