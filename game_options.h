#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

// Try to declare the class 'game_options' here yourself
class game_options
{
public:
  game_options(const bool play_music = true);
  bool do_play_music() const noexcept { return m_play_music; }
private:
  bool m_play_music = true;
};


/// Test the 'game_options' class
void test_game_options();

#endif // GAME_OPTIONS_H
