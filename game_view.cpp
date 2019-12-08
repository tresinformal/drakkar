#include "game_view.h"
#include "food.h"
#include "game.h"
#include "game_resources.h"
#include <SFML/Graphics.hpp>
#include <cmath>

game_view::game_view() : m_window(sf::VideoMode(1280, 720), "tresinformal game")
{
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  m_game_resources.get_wonderland().setLoop(true);
  m_game_resources.get_wonderland().play();
#endif
}

game_view::~game_view()
{
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  m_game_resources.get_wonderland().stop();
#endif // IS_ON_TRAVIS
}

void test_game_view()
{
  {
    // Show the game for one frame
    // (there will be a member function 'exec' for running the game)
    game_view v;
    v.show();
  }
#ifdef FIX_ISSUE_34
  {
    const game_view v;
    assert(v.get_game().get_n_ticks() == 0);
  }
#endif
}

void game_view::pl_1_input(sf::Event event) noexcept
{
  // buttons for  player1
  if (event.key.code == sf::Keyboard::D)
  {
    m_game.get_player(0).do_action(action_type::turn_left);
  }
  else if (event.key.code == sf::Keyboard::A)
  {
    m_game.get_player(0).do_action(action_type::turn_right);
  }
  else if (event.key.code == sf::Keyboard::W)
  {
    m_game.get_player(0).do_action(action_type::accelerate);
  }
  else if (event.key.code == sf::Keyboard::S)
  {
    m_game.get_player(0).do_action(action_type::brake);
  }
}

void game_view::pl_2_input(sf::Event event) noexcept
{
  // buttons for  player2
  if (event.key.code == sf::Keyboard::L)
  {
    m_game.get_player(1).do_action(action_type::turn_left);
  }
  else if (event.key.code == sf::Keyboard::J)
  {
    m_game.get_player(1).do_action(action_type::turn_right);
  }
  else if (event.key.code == sf::Keyboard::I)
  {
    m_game.get_player(1).do_action(action_type::accelerate);
  }
  else if (event.key.code == sf::Keyboard::K)
  {
    m_game.get_player(1).do_action(action_type::brake);
  }
}

bool game_view::process_events()
{

  // User interaction
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      m_window.close();
      return true; // Game is done
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      pl_1_input(event);
      pl_2_input(event);
    }
  }
  return false; // if no events proceed with tick
}

void game_view::exec() noexcept
{
  while (m_window.isOpen())
  {
    bool must_quit{process_events()};
    if (must_quit)
      return;
    m_game.tick();
    show();
  }
}

void game_view::draw_franjo() noexcept
{
  // The part below is mostly showing off and how to draw a sprite
  sf::Sprite franjo;
  franjo.setPosition(400.0, 200.0);
  franjo.setTexture(m_game_resources.get_franjo());
  static double franjo_rotation =
      0.0; //!OCLINT indeed, should nearly ever use a static
  franjo_rotation += 0.01;
  franjo.setRotation(franjo_rotation);
  m_window.draw(franjo);
}

void game_view::draw_players() noexcept
{
  sf::Color color;
  for (unsigned int i = 0; i < m_game.get_v_player().size(); ++i)
  {

    // assign different color for different players,
    // max 5 players handled for now.
    switch (i)
    {

    case 1:
    {
      color = sf::Color::Red;
      break;
    }
    case 2:
    {
      color = sf::Color::Blue;
      break;
    }
    case 3:
    {
      color = sf::Color::Black;
      break;
    }
    case 4:
    {
      color = sf::Color::Green;
      break;
    }
    case 0:
    default:
    {
      color = sf::Color::White;
      break;
    }
    }

    // Create the player sprite
    sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
    rect.setFillColor(color);
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setPosition(static_cast<float>(m_game.get_player(i).get_x()),
                     static_cast<float>(m_game.get_player(i).get_y()));
    rect.setRotation(static_cast<float>((m_game.get_player(i).get_direction()) *
                                        180 / M_PI));
    rect.setTexture(&m_game_resources.get_franjo());

    // Draw the player
    m_window.draw(rect);
  }
}

void game_view::show() noexcept
{
  // Start drawing the new frame, by clearing the screen
  m_window.clear();

  // Draw the background
  sf::Sprite background_sprite;
  background_sprite.setPosition(10.0, 10.0);
  background_sprite.setTexture(m_game_resources.get_grass_landscape());
  m_window.draw(background_sprite);

  draw_franjo();
  draw_players();

  // Create food sprite
  sf::CircleShape foodsprite(25.0);
  // Get position of food
  std::vector<food> foods = m_game.get_food();
  // Position in landscape
  foodsprite.setPosition(static_cast<float>(foods[0].get_x()),
                         static_cast<float>(foods[0].get_y()));
  foodsprite.setFillColor(sf::Color(0, 0, 0));
  m_window.draw(foodsprite);

  // Draw some semitransparent circles to see how well RGB/opsin-based vision
  // works out
  sf::CircleShape circle(200.0);
  // Red
  circle.setPosition(600.0, 200.0);
  circle.setFillColor(sf::Color(255, 0, 0, 128));
  m_window.draw(circle);
  // Green
  circle.setPosition(600.0, 500.0);
  circle.setFillColor(sf::Color(0, 255, 0, 128));
  m_window.draw(circle);
  // Blue
  circle.setPosition(800.0, 350.0);
  circle.setFillColor(sf::Color(0, 0, 255, 128));
  m_window.draw(circle);

  // Display all shapes
  m_window.display();
}
