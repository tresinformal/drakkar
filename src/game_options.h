#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H
#include "key_action_map.h"
#include "environment_type.h"

// Try to declare the class 'game_options' here yourself
class game_options
{
public:
  game_options(
    const int rng_seed = 0,
    const bool play_music = true,
    key_action_map player_1_kam = get_player_1_kam(),
    key_action_map player_2_kam = get_player_2_kam(),
    key_action_map player_3_kam = get_player_3_kam(),
    environment_type env_type = environment_type::empty,
    int max_time = 6000
  );

  ///Get the RNG seed
  int get_rng_seed() const noexcept { return m_rng_seed; }

  ///Checks if the game options have the m_play_music flag on
  bool is_playing_music() const noexcept { return m_play_music; }

  ///Turns the flag m_play_music to false
  void stop_music() noexcept {m_play_music = false;}

  ///Turns the flag m_play_music to true
  void play_music() noexcept {m_play_music = true;}

  const key_action_map& get_kam_1() const noexcept { return m_kam_1; };

  const key_action_map& get_kam_2() const noexcept { return m_kam_2; };

  const key_action_map& get_kam_3() const noexcept { return m_kam_3; };

  const environment_type& get_environment_type() const noexcept { return m_environment_type; };

  const int& get_max_time() const noexcept { return m_max_time; };

private:
  int m_rng_seed;
  bool m_play_music = true;
  key_action_map m_kam_1;
  key_action_map m_kam_2;
  key_action_map m_kam_3;
  environment_type m_environment_type;
  int m_max_time;
};

bool operator== (const game_options& lhs, const game_options& rhs) noexcept;
bool operator!= (const game_options& lhs, const game_options& rhs) noexcept;

/// Implement stream operator
std::ostream& operator << (std::ostream &out, const game_options &g_o);

game_options get_random_game_options(const int& rng_seed);

///Turns off the sound in options
void music_off(game_options& o) noexcept;

///Turns on the sound in options
void music_on(game_options& o) noexcept;

/// Test the 'game_options' class
void test_game_options();

#endif // GAME_OPTIONS_H
