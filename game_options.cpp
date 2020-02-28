#include "game_options.h"
#include <cassert>

// Try to define the class 'game_options' yourself
game_options::game_options(const bool play_music) : m_play_music{play_music} {}

bool operator == (const game_options& lhs, const game_options& rhs) noexcept {
  // Check if left-hand side is equal to the right-hand side
  return lhs.do_play_music()==rhs.do_play_music();
}

bool operator != (const game_options& lhs, const game_options& rhs) noexcept {
  return !(lhs==rhs);
}

void test_game_options()
{

  // By default, music is played
  {
    const game_options g;
    assert(g.do_play_music());
  }
  // Music can be switched off
  {
    const bool do_play_music = false;
    const game_options g(do_play_music);
    assert(!g.do_play_music());
  }

  // Test for equality
  {
    const game_options a(true);
    const game_options b(false);
    assert(a == a);
    assert(a != b);
  }
}
