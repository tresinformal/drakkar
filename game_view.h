#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game.h"
#include "game_resources.h"
#include "game_options.h"
#include <SFML/Graphics.hpp>

/// The game's main window
/// Displays the game class
class game_view
{
public:

  game_view(game_options options = game_options());
  ~game_view();

  /// Show one frame
  void show() noexcept;

  /// Draws players
  void draw_players() noexcept;

  /// Run the game until the window is closed
  void exec() noexcept;

  /// Get const reference to m_game_options
  const game_options& get_options() const noexcept {return m_options;}

  /// Processes events in game and ouputs false if quit
  /// is inputted
  bool process_events();

  ///Gets a const ref to m_game
  const game& get_game() const noexcept {return m_game; }

  ///Gets option settings of the game
  const game_options get_options() {return m_options;}

  ///Gets the const reference to the vector of sf::Views m_v_views
  const std::vector<sf::View>& get_v_views() const noexcept {return  m_v_views; }

  ///Gets the reference to a view in m_v_views
  sf::View& get_view(int i) {return m_v_views[static_cast<unsigned int>(i)]; }

  ///Gets constant ref to sf::RenderWindow m_window
  const sf::RenderWindow& get_window() const noexcept {return m_window; }

private:
  /// The game logic
  game m_game;

  /// The resources (images, sounds, etc.) of the game
  game_resources m_game_resources;

  /// The window to draw to
  sf::RenderWindow m_window;

  ///The views of each player
  std::vector<sf::View> m_v_views;

  /// Parses input for player 1
  void pl_1_input(sf::Event event) noexcept;

  /// Parses input for player 2
  void pl_2_input(sf::Event event) noexcept;

  /// Parses input for player 1
  void pl_1_stop_input(sf::Event event) noexcept;

  /// Parses input for player 2
  void pl_2_stop_input(sf::Event event) noexcept;

  /// The options of the game
  game_options m_options;

  ///Draws the background
  void draw_background() noexcept;

  ///Draws food
  void draw_food() noexcept;

  /// Draws projectiles
  void draw_projectiles() noexcept;

  /// Draws shelters
  void draw_shelters() noexcept;

};

void test_game_view();

#endif // GAME_VIEW_H
