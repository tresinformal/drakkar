#include "menu_view.h"
#include "coordinate.h"

#ifndef LOGIC_ONLY // that is, NOT compiled on GitHub Actions

menu_view::menu_view()
    : m_window(
          sf::VideoMode(m_menu.get_w_width(), m_menu.get_height()),
          "tresinformal game_menu")
{
}

void menu_view::exec()
{
  while (m_window.isOpen())
  {
    bool must_quit{process_events()};
    if (must_quit)
      return;
    show();
  }
}

bool menu_view::process_events()
{
  sf::Event event;
  while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        {
          m_window.close();
          return true; // Game is done
        }
      else if (event.type == sf::Event::MouseButtonPressed)
        {
          coordinate mouse_position(
                static_cast<double>(event.mouseButton.x),
                static_cast<double>(event.mouseButton.y)
                );
          const menu_button mb_action = m_menu.get_button("action");
          if (is_inside_button(mouse_position, mb_action))
            {
              // switches to game_view
            }
          const menu_button mb_about = m_menu.get_button("about");
          if (is_inside_button(mouse_position, mb_about))
            {
              // switches to menu_view
            }
          const menu_button mb_quit = m_menu.get_button("quit");
          if (is_inside_button(mouse_position, mb_quit))
            {
              m_window.close();
              return true;
            }
        }
    }
  return false;
}

void menu_view::show()
{
  // Start drawing the new frame, by clearing the screen
  m_window.clear();

  // Draw the background
  sf::Vector2f bg_dim(m_menu.get_height(), m_menu.get_height());
  sf::RectangleShape background_sprite(bg_dim);
  background_sprite.setPosition(10.0, 10.0);
  background_sprite.setFillColor(sf::Color::Black);
  m_window.draw(background_sprite);

  // Draw buttons
  draw_buttons();

  // Display all shapes
  m_window.display();
}

void menu_view::draw_buttons() noexcept
{

  for ( int i = 0; i < static_cast<int>(m_menu.get_buttons().size()); ++i)
  {
    // Extract button's attributes
    const menu_button this_button = m_menu.get_button(i);
    const std::string button_label = this_button.get_label();

    const int r = this_button.get_color().get_red();
    const int g = this_button.get_color().get_green();
    const int b = this_button.get_color().get_blue();
    const sf::Uint8 red{static_cast<sf::Uint8>(r)};
    const sf::Uint8 green{static_cast<sf::Uint8>(g)};
    const sf::Uint8 blue{static_cast<sf::Uint8>(b)};
    const sf::Color button_color(red, green, blue);

    const coordinate button_position = this_button.get_position();

    // Create the button sprite
    sf::RectangleShape rect(this_button.get_body());
    rect.setFillColor(button_color);
    rect.setOrigin(rect.getSize().x / 2.0f, rect.getSize().y / 2.0f);
    rect.setPosition(static_cast<float>(button_position.get_x()),
                     static_cast<float>(button_position.get_y()));

    // Create the button text
    sf::Text button_text;
    button_text.setString(button_label);
    button_text.setFont(m_game_resources.get_font());
    sf::FloatRect text_area = button_text.getLocalBounds();
    button_text.setOrigin(text_area.width / 2.0f, text_area.height / 2.0f);
    button_text.setPosition(static_cast<float>(button_position.get_x()),
                     static_cast<float>(button_position.get_y()));
    button_text.setCharacterSize(30);
#if SFML_VERSION_MAJOR > 2
    button_text.setFillColor(sf::Color::White);
#elif SFML_VERSION_MAJOR == 2 and SFML_VERSION_MINOR >= 4
    button_text.setFillColor(sf::Color::White);
#else
    button_text.setColor(sf::Color::White);
#endif

    // Draw the buttons
    m_window.draw(rect);
    m_window.draw(button_text);
  }
}

void test_menu_view() //!OCLINT tests may be many
{
#ifndef NDEBUG // no tests in release

#ifdef FIX_ISSUE_495
// (495) There should be a member of type view_mode
{
  menu_view mv;
  view_mode expected_next_view = view_mode::quit;
  assert(mv.what_next() == expected_next_view);
}
#endif

#endif // NDEBUG
}

#endif // LOGIC_ONLY // that is, compiled on GitHub Actions
