#include "event_type.h"
#include <cassert>
#include <sstream>

#ifdef HAS_MAGIC_ENUM // HAS_MAGIC_ENUM is defined in game.pro
#include "../magic_enum/include/magic_enum.hpp" // https://github.com/Neargye/magic_enum
#endif

void test_event_type()
{
  #ifndef NDEBUG // no tests is release
  // to_str
  {
    assert(to_str(event_type::eat_food) == "eat_food");
    assert(to_str(event_type::eat_a_player) == "eat_a_player");
    assert(to_str(event_type::been_eaten) == "been_eaten");
    assert(to_str(event_type::hit_a_player) == "hit_a_player");
    assert(to_str(event_type::been_hit) == "been_hit");
    assert(to_str(event_type::stun_a_player) == "stun_a_player");
    assert(to_str(event_type::been_stunned) == "been_stunned");
    assert(to_str(event_type::collect_an_item) == "collect_an_item");
    assert(to_str(event_type::win_a_game) == "win_a_game");
    assert(to_str(event_type::draw_a_game) == "draw_a_game");
    assert(to_str(event_type::lose_a_game) == "lose_a_game");
    assert(to_str(event_type::nothing) == "nothing");
  }
  //
  {
    std::stringstream s;
    s << event_type::eat_food;
    assert(!s.str().empty());
  }
#endif
}

std::ostream &operator<<(std::ostream &os, const event_type t)
{
  os << to_str(t);
  return os;
}

std::string to_str(const event_type this_event_type) noexcept
{
  #ifdef HAS_MAGIC_ENUM // HAS_MAGIC_ENUM is defined in game.pro
  return std::string(magic_enum::enum_name(this_event_type));
  #else
  switch (this_event_type)
  {
  case event_type::eat_food:
    return "eat_food";
  case event_type::eat_a_player:
    return "eat_a_player";
  case event_type::been_eaten:
    return "been_eaten";
  case event_type::hit_a_player:
    return "hit_a_player";
  case event_type::been_hit:
    return "been_hit";
  case event_type::stun_a_player:
    return "stun_a_player";
  case event_type::been_stunned:
    return "been_stunned";
  case event_type::collect_an_item:
    return "collect_an_item";
  case event_type::win_a_game:
    return "win_a_game";
  case event_type::draw_a_game:
    return "draw_a_game";
  case event_type::lose_a_game:
    return "lose_a_game";
  case event_type::nothing:
    return "nothing";
  default:
    return "nothing";
  }
  #endif
}
