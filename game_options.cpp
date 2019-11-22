#include "game_options.h"

// Try to declare the class 'game_options' here yourself

void test_game_options()
{
  #ifdef FIX_ISSUE_88
  //By default, music is played
  {
    const game_options g;
    assert(g.do_play_music());
  }
  //Music can be switched off
  {
    const bool do_play_music = false;
    const game_options g(do_play_music);
    assert(!g.do_play_music());
  }
  #endif // FIX_ISSUE_88
}
