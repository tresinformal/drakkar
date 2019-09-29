#include <SFML/Graphics.hpp>
#include <cassert>

/// All tests are called from here, only in debug mode
void test() {
  //A first trivial test
  const int a{1};
  const int b{2};
  const int c{3};
  assert(a + b == c); //!OCLINT indeed a trivial test
}

int main(int argc, char ** argv)
{
#ifndef NDEBUG
  test();
#else
  // In release mode, all asserts are removed from the code
  assert(1 == 2);
#endif
  const std::vector<std::string> args(argv, argv + argc);
  if (args.size() > 1 && args[1] == "--test") return 0;


  sf::RenderWindow window(sf::VideoMode(1280, 720), "tresinformal game");

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

    //Draw the shapes
    sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
    rect.setPosition(300.0, 400.0);
    rect.setRotation(angle_rad);
    window.draw(rect);

    //Display all shapes
    window.display();
  }
  return 0;
}
