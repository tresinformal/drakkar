#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game.h"
#include "game_resources.h"
#include "game_options.h"
#include "view_mode.h"
#include <SFML/Graphics.hpp>
#include "key_action_map.h"

/// The game's main window
/// Displays the game class
class game_view
{
public:
  game_view(
          game_options options = game_options(),
          sf::Vector2f window_size = sf::Vector2f(1280, 720)
  );
  ~game_view();

  /// Show one frame
  void show() noexcept;

  /// Draws players
  void draw_players() noexcept;

  /// Run the game until the window is closed
  void exec() noexcept;

  /// Get const reference to m_game_options
  const game_options& get_options() const noexcept {return get_game().get_game_options();}

  void set_options(const game_options& new_options) noexcept { m_game.set_options(new_options); }

  /// Processes events in game and ouputs false if quit
  /// is inputted
  bool process_events();

  /// Process one timestep
  void tick() { m_game.tick(); }

  ///Gets a const ref to m_game
  const game& get_game() const noexcept {return m_game; }

  /// Get next view
  view_mode get_next_view() const
  {
    return m_next_view;
  }

  // Get the size of the window
  const sf::Vector2f& get_window_size() const noexcept { return m_window_size; }

  // Get the window's state, for testing purposes only
  bool is_window_open() const { return m_window.isOpen(); }

#ifdef VIEW_SWITCH
  // Returns what view should come next
  const view_mode& what_next() const noexcept { return m_next_view; }
#endif // VIEW_SWITCH
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

  // The size of the window to draw
  sf::Vector2f m_window_size;

  /// The window to draw to
  sf::RenderWindow m_window;

  ///The views of each player
  std::vector<sf::View> m_v_views;

  /// Next view to switch to
  view_mode m_next_view = view_mode::quit;

  /// Parses input for player 1
  void pl_1_stop_input(sf::Event event) noexcept;

  /// Parses input for player 2
  void pl_2_stop_input(sf::Event event) noexcept;

  /// Parses input for player 3
  void pl_3_stop_input(sf::Event event) noexcept;

  ///Draws the background
  void draw_background() noexcept;

  /// Set fourth view for players coordinates
  void set_player_info_view() noexcept;

  /// Draw player coordinates
  void draw_player_info() noexcept;
};

key_action_map get_player_kam(const player& p);

/// Parses input for a player
player player_input(player p, sf::Event event);

void test_game_view();

#endif // GAME_VIEW_H
