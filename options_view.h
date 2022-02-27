#ifndef OPTIONS_VIEW_H
#define OPTIONS_VIEW_H

#ifndef LOGIC_ONLY // that is, NOT compiled on GitHub Actions

#include "SFML/Graphics.hpp"
#include "game_options.h"
#include "game_resources.h"

class options_view
{
public:
  options_view();

  /// Shows the options
  void show();

  /// Creates the menu and draws it
  void exec();

private:
  game_options m_options;
  sf::RenderWindow m_window;
  game_resources m_game_resources;
  bool process_events();
  double m_height = 720;
  double m_width = 1280;
};

void test_options_view();

#endif // LOGIC_ONLY

#endif // OPTIONS_VIEW_H
