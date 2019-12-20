#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game.h"
#include "game_resources.h"
#include <SFML/Graphics.hpp>

/// The game's main window
/// Displays the game class
class game_view
{
public:
  game_view();
  ~game_view();

  /// Show one frame
  void show() noexcept;

  /// Draws players
  void draw_players() noexcept;

  /// Run the game until the window is closed
  void exec() noexcept;

  /// Parses input for player 1
  void pl_1_input(sf::Event event) noexcept;

  /// Parses input for player 2
  void pl_2_input(sf::Event event) noexcept;

  /// Processes events in game and ouputs false if quit
  /// is inputted
  bool process_events();

private:
  /// The game logic
  game m_game;

  /// The resources (images, sounds, etc.) of the game
  game_resources m_game_resources;

  /// The window to draw to
  sf::RenderWindow m_window;

  /// Draws shelters
  void draw_shelters() noexcept;

};

void test_game_view();

#endif // GAME_VIEW_H
