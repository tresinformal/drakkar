#include "player_profession.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <iostream>

std::string to_str(player_profession this_player_profession)
{
  switch (this_player_profession)
  {
  case player_profession::hitman:
    return "hitman";
  case player_profession::sprinter:
    return "sprinter";

  default:
    return "tank";
  }
}

std::ostream& operator << (std::ostream& os, const player_profession& pro)
{
    os << to_str(pro);
    return os;
}

void test_player_profession()
{
#ifndef NDEBUG // no tests in release
  #define FIX_ISSUE_537
  #ifdef FIX_ISSUE_537
  // Each profesion is unique
  {
    assert(player_profession::hitman != player_profession::sprinter);
    assert(player_profession::tank != player_profession::hitman &&
              player_profession::tank != player_profession::sprinter);
  }

  // operator<< works
  {
    std::stringstream s;
    const player_profession pro = player_profession::hitman;
    s << pro;
    assert(!s.str().empty());
  }

  // Conversion to string works
  {
    assert(to_str(player_profession::hitman) == "hitman");
    assert(to_str(player_profession::sprinter) == "sprinter");
    assert(to_str(player_profession::tank) == "tank");
  }

  #endif // FIX_ISSUE_537
#endif
}

