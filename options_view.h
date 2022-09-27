#ifndef OPTIONS_VIEW_H
#define OPTIONS_VIEW_H

#include "SFML/Graphics.hpp"
#include "game_options.h"
#include "game_resources.h"
#include "view_mode.h"

class options_view
{
public:
  options_view();

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

private:
  game_options m_options;
  sf::RenderWindow m_window;
  game_resources m_game_resources;
  bool process_events();
  double m_height = 720;
  double m_width = 1280;
  view_mode m_next_view = view_mode::quit;
};

void test_options_view();

#endif // OPTIONS_VIEW_H
