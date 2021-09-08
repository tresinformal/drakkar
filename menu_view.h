#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#ifndef LOGIC_ONLY // that is, compiled on GitHub Actions

#include "SFML/Graphics.hpp"
#include "menu.h"
#include "game_resources.h"
class menu_view
{
public:
  menu_view();

  /// Creates the menu and draws it
  void exec();

private:
  menu m_menu;
  sf::RenderWindow m_window;

  ///
  bool process_events();

  /// Draws the buttons
  void draw_buttons() noexcept;

  /// Shows the menu
  void show();
};

#endif // LOGIC_ONLY // that is, compiled on GitHub Actions

#endif // MENU_VIEW_H
