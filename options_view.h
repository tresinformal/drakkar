#ifndef OPTIONS_VIEW_H
#define OPTIONS_VIEW_H

#ifndef LOGIC_ONLY // that is, compiled on GitHub Actions

#include "SFML/Graphics.hpp"
#include "game_options.h"

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
  bool process_events();
};

#endif // LOGIC_ONLY // that is, compiled on GitHub Actions

#endif // OPTIONS_VIEW_H
