#include "game_view.h"
#include "game.h"
#include <SFML/Graphics.hpp>

game_view::game_view()
{

}

void test_game_view()
{
  {
    //Show the game for one frame
    // (there will be a member function 'exec' for running the game)
    const game_view v;
    v.show();
  }
  #ifdef FIX_ISSUE_34
  {
    const game_view v;
    assert(v.get_game().get_n_ticks() == 0);
  }
  #endif
}

void game_view::show() const
{

  sf::RenderWindow window(sf::VideoMode(1280, 720), "tresinformal game");

  //define angle of intial rectangle
  float angle_rad{0.0}; //SFML prefers floats

  //Draw the shapes
  sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
  rect.setPosition(300.0, 400.0);
  rect.setRotation(angle_rad);
  window.draw(rect);

  //Display all shapes
  window.display();
}
