#include "game_view.h"
#include "game.h"
#include "game_resources.h"
#include <SFML/Graphics.hpp>

game_view::game_view():
    m_window(sf::VideoMode(1280, 720), "tresinformal game")
{
  m_game_resources.get_ninja_gods().setLoop(true);
  m_game_resources.get_ninja_gods().play();
}

game_view::~game_view()
{
  m_game_resources.get_ninja_gods().stop();
}

void test_game_view()
{
  {
    //Show the game for one frame
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

void game_view::exec() noexcept
{
  while(m_window.isOpen()) {
    //User interaction
    sf::Event event;
    while(m_window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        m_window.close();
        return; //Game is done
      }
      #ifdef FIX_ISSUE_69
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::D)
        {
          m_game.do_action(action_type::turn_left);
        }
      }
      #endif
    }
    show();
  }
}

void game_view::show() noexcept
{
  // Start drawing the new frame, by clearing the screen
  m_window.clear();

  // Draw the background
  sf::Sprite background_sprite;
  background_sprite.setTexture(m_game_resources.get_heterogenous_landscape());
  m_window.draw(background_sprite);

  //Draw the player
  sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
  rect.setPosition(300.0, 400.0);
  rect.setRotation(static_cast<float>(m_game.get_player().get_direction()));
  m_window.draw(rect);

  //Display all shapes
  m_window.display();
}
