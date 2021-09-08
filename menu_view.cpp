#include "menu_view.h"

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
  sf::Color color;
  for ( int i = 0; i < static_cast<int>(m_menu.get_buttons().size()); ++i)
  {
    // assign different color for buttons
    // i = 0: Action "Green"
    // i = 1: About  "Blue"
    // i = 2: Quit   "Red"
    // Only three buttons implemented
    switch (i)
    {
    case 0:
    {
      color = sf::Color::Green;
      break;
    }
    case 1:
    {
      color = sf::Color::Blue;
      break;
    }
    case 2:
    {
      color = sf::Color::Red;
      break;
    }
    default:
    {
      color = sf::Color::Black;
      break;
    }
    }

    // Create the button sprite
    sf::RectangleShape rect(m_menu.get_button(i).get_body());
    rect.setFillColor(color);
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setPosition(static_cast<float>(m_menu.get_button(i).get_x()),
                     static_cast<float>(m_menu.get_button(i).get_y()));


    // Draw the rectangles
    m_window.draw(rect);

    //Add the text
    sf::Text text;
    text.setFont(m_game_resources.get_font());
    text.setString("Hello world");
    //text.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    sf::Color color_white = sf::Color::White;
    text.setFillColor(color_white);

    text.setPosition(m_menu.get_button(i).get_x(),
                     m_menu.get_button(i).get_y());
    //text.setPosition(0.0, 0.0);

    text.setFont(game_resources().get_font());
    //text.setCharacterSize(30.0);
    m_window.draw(text);


  }
}
