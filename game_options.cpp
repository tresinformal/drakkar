#include "game_options.h"
#include <cassert>

// Try to define the class 'game_options' yourself
game_options::game_options(const bool play_music) : m_play_music{play_music} {}

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
}
