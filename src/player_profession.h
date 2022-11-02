#ifndef PLAYER_PROFESSION_H
#define PLAYER_PROFESSION_H

#include <string>
#include <iosfwd>

enum class player_profession
{
  hitman,
  sprinter,
  tank,
};

void test_player_profession();
std::string to_str(player_profession this_player_profession);
std::ostream& operator << (std::ostream& os, const player_profession& pro);

#endif // PLAYER_PROFESSION_H
