#include "options_view.h"

options_view::options_view()
    :  m_window(
          sf::VideoMode(720, 1280),
          "tresinformal game options")
{
}

void options_view::exec()
{
  while (m_window.isOpen())
  {
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
  sf::Vector2f bg_dim(m_height, m_width);
  sf::RectangleShape background_sprite(bg_dim);
  background_sprite.setPosition(10.0, 10.0);
  auto bg_color = sf::Color{ 0x000066 }; // dark blue
  background_sprite.setFillColor(bg_color);
  m_window.draw(background_sprite);

  // Placeholder text
  sf::Text placeholder;
  placeholder.setFont(m_game_resources.get_font());
  placeholder.setString("Options were never an option.");
  placeholder.setFillColor(sf::Color::Yellow);
  placeholder.setPosition(m_width / 2.0, m_height / 2.0);

  // Display all shapes
  m_window.display();
}

