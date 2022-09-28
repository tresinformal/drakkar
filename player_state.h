#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H
#include <string>
#include <iosfwd>

enum class player_state
{
  active,
  out,
  stunned
};

void test_player_state();
std::string to_str(player_state this_player_state);
std::ostream& operator << (std::ostream& os, const player_state& state);

/// implement << operator
std::ostream& operator << (std::ostream& os, const player_state& state);

#endif // PLAYER_STATE_H
