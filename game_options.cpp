#include "game_options.h"
#include "key_action_map.h"
#include <cassert>

// Try to define the class 'game_options' yourself
game_options::game_options(
  const bool play_music
) : m_play_music{play_music},
    m_kam_1{get_player_1_kam()},
    m_kam_2{get_player_2_kam()}
{

}

bool operator == (const game_options& lhs, const game_options& rhs) noexcept {
  // Check if left-hand side is equal to the right-hand side
  return lhs.is_playing_music()==rhs.is_playing_music();
}

bool operator != (const game_options& lhs, const game_options& rhs) noexcept {
  return !(lhs==rhs);
}

void music_off(game_options& o) noexcept
{
  o.stop_music(); //ok maybe this is redundant @swom
}

void music_on(game_options& o) noexcept
{
  o.play_music();
}

void test_game_options()
{
  #ifndef NDEBUG // no tests in release
  // By default, music is played
  {
    const game_options g;
    assert(g.is_playing_music());

  }
  // Music can be switched off
  {
    const bool do_play_music = false;
    const game_options g(do_play_music);
    assert(!g.is_playing_music());
  }

  // Test for equality
  {
    const game_options a(true);
    const game_options b(false);
    assert(a == a);
    assert(a != b);
  }

  //Sound can be turned down
  {
    game_options o;
    assert(o.is_playing_music());
    music_off(o);
    assert(!o.is_playing_music());
    music_on(o);
    assert(o.is_playing_music());
  }
  // A game options has a seed for the random number generator
  {
    const game_options a;
    assert(a.get_rng_seed() == 0);
  }
  // Player 1 has a key action map
  {
    const game_options a;
    const auto m = a.get_kam_1();
    const auto m_again = get_player_1_kam(); // Naming is confusing, this is the KAM for the first player
    assert(m == m_again);
  }
  // Player 2 has a key action map
  {
    const game_options a;
    const auto m = a.get_kam_2();
    const auto m_again = get_player_2_kam(); // Naming is confusing, this is the KAM for the first player
    assert(m == m_again);
  }
  #ifdef FIX_ISSUE_289
  // Player 3 has a key action map
  {
    const game_options a;
    const auto m = a.get_kam_3();
    const auto m_again = get_player_3_kam(); // Naming is confusing, this is the KAM for the first player
    assert(m == m_again);
  }
  #endif // FIX_ISSUE_289
  #endif
}
