#include "options_view.h"

options_view::options_view()
    :  m_window(
          sf::VideoMode(1280, 720),
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
  sf::Vector2f bg_dim(m_width, m_height);
  sf::RectangleShape background_sprite(bg_dim);
  auto bg_color = sf::Color{ 0, 0, 230, 255 }; // dark blue
  background_sprite.setFillColor(bg_color);
  m_window.draw(background_sprite);

  // Placeholder text
  sf::Text placeholder;
  placeholder.setFont(m_game_resources.get_font());
  placeholder.setString("Exit status 1 was never an option.");
  placeholder.setCharacterSize(40);
  sf::FloatRect text_area = placeholder.getLocalBounds();
  placeholder.setOrigin(text_area.width / 2.0, text_area.height / 2.0);
  placeholder.setFillColor(sf::Color::Yellow);
  placeholder.setPosition(m_width / 2.0, m_height / 2.0);
  m_window.draw(placeholder);

  // Display all shapes
  m_window.display();
}

