#include "options_view.h"
#include "menu_button.h"
#include <cassert>

#ifndef LOGIC_ONLY // that is, NOT compiled on GitHub Actions

options_view::options_view(const game_options& options) :
  m_options{options},
  m_window(
    sf::VideoMode(1280, 720),
    "tresinformal game options"
  )
{
  // After setup, close window until executed
  m_window.close();
}

void options_view::exec()
{
  // Open window
  m_window.create(
    sf::VideoMode(1280, 720),
    "tresinformal game options"
  );
  while (m_window.isOpen())
  {
    // Process use input until told to exit options screen
    bool must_quit{process_events()};
    if (must_quit)
      return;
    show();
  }
}

bool options_view::process_events()
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      m_window.close();
      return true; // Game is done
    }
  }
  return false;
}

void options_view::show()
{
  // Start drawing the new frame, by clearing the screen
  m_window.clear();

  // Draw the background
  sf::Vector2f bg_dim(m_width, m_height);
  sf::RectangleShape background_sprite(bg_dim);
  auto bg_color = sf::Color{ 0, 0, 230, 255 }; // dark blue
  background_sprite.setFillColor(bg_color);
  m_window.draw(background_sprite);

  // Create the Music button sprite
  sf::Vector2f music_button_dim(200.0, 100.0);
  sf::Vector2f music_button_pos(m_width / 2.0, m_height / 5.0);
  sf::RectangleShape music_button_bg(music_button_dim);
  sf::Color music_button_color(0, 100, 255);
  music_button_bg.setFillColor(music_button_color);
  sf::Vector2f music_button_origin(music_button_bg.getSize().x / 2.0f,
                                   music_button_bg.getSize().y / 2.0f);
  music_button_bg.setOrigin(music_button_origin);
  music_button_bg.setPosition(music_button_pos);

  // Create the Music button text
  sf::Text music_button_text;
  music_button_text.setString("Music:");
  music_button_text.setFont(m_game_resources.get_font());
  //sf::FloatRect text_area = music_button_text.getLocalBounds();
  music_button_text.setCharacterSize(50);
  music_button_text.setOrigin(music_button_origin);
  music_button_text.setPosition(music_button_pos);

  m_window.draw(music_button_bg);
  m_window.draw(music_button_text);

  // Display all shapes
  m_window.display();
}

#ifndef NDEBUG // no tests in release
void test_options_view() //!OCLINT tests may be many
{
  // (496) There should be a member of type view_mode
  {
    options_view ov;
    view_mode expected_next_view = view_mode::quit;
    assert(ov.get_next_view() == expected_next_view);
  }
  // (545) An Options window doesn't open at construction
  {
    options_view ov;
    assert(!ov.is_window_open());
    // Ideally one should also test for the window opening during exec()
    // and closing after, but that is not possible AFAICS
    // bc exec() doesn't exit on its own
  }
  // (631) An options_view allows a user to modify game_options
  {
    const game_options options;
    const options_view view(options);
    const game_options options_again(view.get_options());
    assert(options == options_again);
  }

#ifdef FIX_ISSUE_630
  // (630) The options screen has a music on/off button
  {
    const options_view view;
    const menu_button mb = view.get_music_button();
    mb.get_label() == "";
  }
#endif

}
#endif // NDEBUG // No tests in release

#endif // LOGIC_ONLY



