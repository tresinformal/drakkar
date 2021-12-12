#include "options_view.h"

options_view::options_view()
    : m_window(
          sf::VideoMode(m_menu.get_w_width(), m_menu.get_height()),
          "tresinformal game_menu")
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
  sf::Vector2f bg_dim(m_menu.get_height(), m_menu.get_height());
  sf::RectangleShape background_sprite(bg_dim);
  background_sprite.setPosition(10.0, 10.0);
  background_sprite.setFillColor(sf::Color::Black);
  m_window.draw(background_sprite);

  // Display all shapes
  m_window.display();
}

