#include "options_view.h"
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

  #ifdef FIX_ISSUE_640
  {
    const sf::Text& get_title_text(*this);
    m_window.draw(title_text);
  }
  #endif // FIX_ISSUE_640

  // Placeholder text
  sf::Text placeholder;

  placeholder.setFont(m_game_resources.get_font());
  placeholder.setString("We don't have an Options screen yet D:");
  placeholder.setCharacterSize(40);
  sf::FloatRect text_area = placeholder.getLocalBounds();
  placeholder.setOrigin(text_area.width / 2.0, text_area.height / 2.0);

#if SFML_VERSION_MAJOR > 2
    placeholder.setFillColor(sf::Color::Yellow);
#elif SFML_VERSION_MAJOR == 2 and SFML_VERSION_MINOR >= 4
    placeholder.setFillColor(sf::Color::Yellow);
#else
    placeholder.setColor(sf::Color::Yellow);
#endif


  placeholder.setPosition(m_width / 2.0, m_height / 2.0);
  m_window.draw(placeholder);

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
  //#define FIX_ISSUE_630
  #ifdef FIX_ISSUE_630
  // (630) One must be able to turn off the music in the options screen
  {
    const game_options options;
    assert(options.is_playing_music());
    options_view view(options);
    assert(view.get_options().is_playing_music());
    view.click_play_music_button();
    assert(!view.get_options().is_playing_music());
  }
  #endif // FIX_ISSUE_630
  //#define FIX_ISSUE_631
  #ifdef FIX_ISSUE_631
  // (631) An options_view allows a user to modify game_options
  {
    const game_options options;
    const options_view view(options);
    const game_options options_again(view.get_options());
    assert(options == options_again);
  }
  #endif // FIX_ISSUE_631
  //#define FIX_ISSUE_640
  #ifdef FIX_ISSUE_640
  // (640) Add a title
  {
    game_options options; //Cannot be const
    // The line below modifies the game_options,
    // as it will initialize the text with a font,
    // that is taken from the game_options' resources:
    // getting the sf::Font by reference is non-const
    const sf::Text title_text{
      create_title_text(options)
    };
    assert(title_text.getString() == "Drakkar.io");
    assert(title_text.getCharacterSize() > 20); //Bigger is OK
  }
  #endif // FIX_ISSUE_640

}
#endif // NDEBUG // No tests in release

#endif // LOGIC_ONLY


