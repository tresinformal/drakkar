#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H
#include "key_action_map.h"
// Try to declare the class 'game_options' here yourself
class game_options
{
public:
  game_options(const bool play_music = true);

  ///checks if the game options have the m_play_music flag on
  bool is_playing_music() const noexcept { return m_play_music; }

  ///Turns the flag m_play_music to false
  void stop_music() noexcept {m_play_music = false;}

  ///Turns the flag m_play_music to true
  void play_music() noexcept {m_play_music = true;}

  const key_action_map& get_kam_1() const noexcept { return m_kam_1; };

private:
  bool m_play_music = true;
  key_action_map m_kam_1;
};

bool operator == (const game_options& lhs, const game_options& rhs) noexcept;

///Turns off the sound in options
void music_off(game_options& o) noexcept;

///Turns on the sound in options
void music_on(game_options& o) noexcept;

/// Test the 'game_options' class
void test_game_options();

#endif // GAME_OPTIONS_H
