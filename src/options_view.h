#ifndef OPTIONS_VIEW_H
#define OPTIONS_VIEW_H

#include "SFML/Graphics.hpp"
#include "game_options.h"
#include "game_resources.h"
#include "view_mode.h"
#include "menu_button.h"

class options_view
{
public:
  /// The initial options to display
  options_view(const game_options& options = game_options());

  /// Shows the options
  void show();

  /// Creates the options window and draw it
  void exec();

  /// Get next view
  view_mode get_next_view() const
  {
      return m_next_view;
  }

  // Get the window's state, for testing purposes only
  bool is_window_open() { return m_window.isOpen(); }

  // Get the game options
  const game_options& get_options()const noexcept { return m_options; }

  // Get the music button
  const menu_button& get_music_button() const noexcept { return m_music_button; }

  // Click the music button to turn music on/off
  void click_play_music_button();

private:
  game_options m_options;
  sf::RenderWindow m_window;
  game_resources m_game_resources;
  bool process_events();
  double m_height = 720;
  double m_width = 1280;
  view_mode m_next_view = view_mode::quit;
  const color pick_music_button_color() const noexcept;

  // Music button
  menu_button m_music_button = menu_button(
        "Music:",
        pick_music_button_color(),
        coordinate(m_width / 2.0, m_height / 5.0),
        200.0, 100.0
        );
};

void test_options_view();

#endif // OPTIONS_VIEW_H
