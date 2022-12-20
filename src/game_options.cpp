#include "game_options.h"
#include "key_action_map.h"
#include "environment_type.h"
#include <cassert>
#include <sstream>

// Try to define the class 'game_options' yourself
game_options::game_options(
    const int rng_seed,
    const bool play_music,
    key_action_map player_1_kam,
    key_action_map player_2_kam,
    key_action_map player_3_kam,
    environment_type env_type
    ) :
  m_rng_seed{rng_seed},
  m_play_music{play_music},
  m_kam_1{player_1_kam},
  m_kam_2{player_2_kam},
  m_kam_3{player_3_kam},
  m_environment_type{env_type}
{

}

bool operator== (const game_options& lhs, const game_options& rhs) noexcept {
  // Check if left-hand side is equal to the right-hand side
  return lhs.get_kam_1() == rhs.get_kam_1()
      && lhs.get_kam_2() == rhs.get_kam_2()
      && lhs.get_kam_3() == rhs.get_kam_3()
      && lhs.get_rng_seed() == rhs.get_rng_seed()
      && lhs.is_playing_music() == rhs.is_playing_music();
}

bool operator!= (const game_options& lhs, const game_options& rhs) noexcept {
  return !(lhs==rhs);
}

std::ostream &operator <<(std::ostream &out, const game_options &g_o)
{
  return out << g_o.get_rng_seed();
}

void music_off(game_options& o) noexcept
{
  o.stop_music(); //ok maybe this is redundant @swom
}

void music_on(game_options& o) noexcept
{
  o.play_music();
}

game_options get_random_game_options(const int& rng_seed) {
  std::srand(rng_seed);
  // Need to create all KAMs at once to ensure all keys are unique over all KAMs
  std::vector<key_action_map> random_kams = get_n_random_kams(2);
  game_options random_game_options = game_options(
        rng_seed,
        true,
        random_kams[0],
      random_kams[1]
      );
  // assert that kam 1 and kam 2 don't have the same keys
  return random_game_options;
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
    const int rng_seed = 0;
    const game_options g(rng_seed, do_play_music);
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
  // (289) Player 3 has a key action map
  {
    const game_options a;
    const auto m = a.get_kam_3();
    const auto m_again = get_player_3_kam(); // Naming is confusing, this is the KAM for the first player
    assert(m == m_again);
  }

  // (303) Two random game options are the same, when the same seed is used
  {
    const int rng_seed = 271;
    const game_options a = get_random_game_options(rng_seed);
    const game_options b = get_random_game_options(rng_seed);
    assert(a == b);
  }
  // (303) Two random game options differ in general
  {
    const int rng_seed = 314;
    const game_options a = get_random_game_options(rng_seed);
    const game_options b = get_random_game_options(rng_seed + 1);
    assert(a != b);
  }
  // (303) Two random game options differ in their key-action maps especially
  {
    const int rng_seed = 111;
    const game_options a = get_random_game_options(rng_seed);
    const game_options b = get_random_game_options(rng_seed + 1);
    assert(a.get_kam_1() != b.get_kam_1());
    assert(a.get_kam_2() != b.get_kam_2());
  }

  {
    // (353) Random game options should not draw keys already used by another player
    const int rng_seed = 271;
    const game_options rgo = get_random_game_options(rng_seed);
    key_action_map map_1 = rgo.get_kam_1();
    key_action_map map_2 = rgo.get_kam_2();
    std::vector<sf::Keyboard::Key> keys_in_1;
    for (auto& this_row : map_1.get_raw_map())
      {
        sf::Keyboard::Key key_in_1 = this_row.first;
        assert(!map_2.has_key(key_in_1));
      }
  }

  // (383) A game_options has an environment_type member
  {
    game_options go;
    assert(go.get_environment_type() == environment_type::empty);
  }
//#define FIX_ISSUE_681
#ifdef FIX_ISSUE_681
  // (681) The game_options set a time limit
  {
    const int max_time = 500; // change if too long/short
    const int seed = 3;
    const bool music_on = false;
    const key_action_map any_kam_will_do = get_random_kam();

    game_options random_game_options = game_options(
          seed,
          music_on,
          any_kam_will_do,
          any_kam_will_do,
          any_kam_will_do,
          environment_type(),
          max_time
          );
    assert(game_options.get_max_time() == max_time);
  }
#endif // FIX_ISSUE_681

#endif // NDEBUG
}
