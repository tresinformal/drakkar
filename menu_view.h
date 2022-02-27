#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#ifndef LOGIC_ONLY // so this is NOT compiled on GitHub Actions

#include "SFML/Graphics.hpp"
#include "game_resources.h"
#include "menu.h"

class menu_view
{
public:
  menu_view();

  /// Creates the menu and draws it
  void exec();

private:
  menu m_menu;
  sf::RenderWindow m_window;
  game_resources m_game_resources;

  ///
  bool process_events();

  /// Draws the buttons
  void draw_buttons() noexcept;

  /// Shows the menu
  void show();
};

void test_menu_view();

#endif // LOGIC_ONLY

#endif // MENU_VIEW_H
