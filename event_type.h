#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

#include <iosfwd>
#include <string>

enum class event_type
{
  eat_food,
  eat_a_player,
  been_eaten,
  hit_a_player,
  been_hit,
  stun_a_player,
  been_stunned,
  collect_an_item,
  win_a_game,
  draw_a_game,
  lose_a_game,
  nothing
};

void test_event_type();
std::string to_str(const event_type this_event_type);
std::ostream &operator<<(std::ostream &os, const event_type t);

#endif // ACTION_TYPE_H
