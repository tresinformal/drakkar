#include "game_view.h"
#include "game.h"
#include <SFML/Graphics.hpp>

game_view::game_view():
    m_window(sf::VideoMode(1280, 720), "tresinformal game")
{

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
      //Use interaction
      sf::Event event;
      while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
          m_window.close();
          return; //Game is done
        }
      }

      // Use the game_view's show member function here
      show();
    }
}
void game_view::show() noexcept
{


  //define angle of intial rectangle
  float angle_rad{0.0}; //SFML prefers floats

  //Draw the shapes
  sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
  rect.setPosition(300.0, 400.0);
  rect.setRotation(angle_rad);
  m_window.draw(rect);

  //Display all shapes
  m_window.display();
}
