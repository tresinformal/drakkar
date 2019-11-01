#include <SFML/Graphics.hpp>
#include <cassert>
#include "player_shape.h"
#include "player.h"
#include "game.h"
#include "game_view.h"
#include "game_resources.h"
#include "environment_type.h"
/// All tests are called from here, only in debug mode
void test() {
  test_player_shape();
  test_player();
  test_game();
  test_game_view();
  test_game_resources();
}
int main(int argc, char ** argv) //!OCLINT tests may be long
{
#ifndef NDEBUG
  test();
#else
  // In release mode, all asserts are removed from the code
  assert(1 == 2);
#endif
  const std::vector<std::string> args(argv, argv + argc);

  //We've already tested, so the program is done
  if (args.size() > 1 && args[1] == "--test") return 0;

  #ifdef FIX_ISSUE_33
  game_view v;
  v.exec();
  #else
  sf::RenderWindow window(sf::VideoMode(1280, 720), "tresinformal game");

  // g must not go out of scope.
  // If the textures turn white, you know it did
  game_resources g;
  sf::Sprite background_sprite;
  background_sprite.setTexture(g.get_heterogenous_landscape());

  float angle_rad{0.0}; //SFML prefers floats

  while(window.isOpen()) {
    //Use interaction
    sf::Event event;
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) window.close();
    }

    //Game events
    angle_rad += 0.1f;

    // Start drawing the new frame, by clearing the screen
    window.clear();

    // Draw the background
    window.draw(background_sprite);

    //Draw the shapes
    sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
    rect.setPosition(300.0, 400.0);
    rect.setRotation(angle_rad);
    rect.setFillColor(sf::Color::Red);

    window.draw(rect);

    //Display all shapes
    window.display();
  }
  #endif
  return 0;
}
