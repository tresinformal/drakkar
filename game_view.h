#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>
#include "game.h"
#include "game_resources.h"

/// The game's main window
/// Displays the game class
class game_view
{
public:
  game_view();

  /// Show one frame
  void show() noexcept;

  /// Run the game until the window is closed
  void exec() noexcept;

private:
  /// The game logic
  game m_game;

  /// The resources (images, sounds, etc.) of the game
  game_resources m_game_resources;

  /// The window to draw to
  sf::RenderWindow m_window;
};


void test_game_view();

#endif // GAME_VIEW_H
