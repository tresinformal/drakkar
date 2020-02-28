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
    m_game.do_action(0, action_type::turn_left);
  }
  else if (event.key.code == sf::Keyboard::A)
  {
    m_game.do_action(0, action_type::turn_right);
  }
  else if (event.key.code == sf::Keyboard::W)
  {
    m_game.do_action(0, action_type::accelerate);
  }
  else if (event.key.code == sf::Keyboard::S)
  {
    m_game.do_action(0, action_type::brake);
  }
  else if (event.key.code == sf::Keyboard::Q)
  {
    m_game.do_action(0, action_type::shoot);
  }
}

void game_view::pl_2_input(sf::Event event) noexcept
{
  // buttons for  player2
  if (event.key.code == sf::Keyboard::L)
  {
    m_game.do_action(1, action_type::turn_left);
  }
  else if (event.key.code == sf::Keyboard::J)
  {
    m_game.do_action(1, action_type::turn_right);
  }
  else if (event.key.code == sf::Keyboard::I)
  {
    m_game.do_action(1, action_type::accelerate);
  }
  else if (event.key.code == sf::Keyboard::K)
  {
    m_game.do_action(1, action_type::brake);
  }
  else if (event.key.code == sf::Keyboard::U)
  {
    m_game.do_action(1, action_type::shoot);
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
    play_sound();
  }
}

void game_view::draw_players() noexcept //!OCLINT too long indeed, please
                                        //! shorten
{
  for (const auto &player : m_game.get_v_player())
  {
    // Create the player sprite
    sf::RectangleShape rect(sf::Vector2f(player.get_size(), player.get_size()));
    rect.setFillColor(sf::Color(static_cast<sf::Uint8>(get_redness(player)),
                                static_cast<sf::Uint8>(get_greenness(player)),
                                static_cast<sf::Uint8>(get_blueness(player))));
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setPosition(static_cast<float>(player.get_x()),
                     static_cast<float>(player.get_y()));
    rect.setRotation(static_cast<float>((player.get_direction()) * 180 / M_PI));
    rect.setTexture(&m_game_resources.get_franjo());

    // Draw the player
    m_window.draw(rect);
  }
}

void game_view::draw_projectiles() noexcept
{
  for (const auto &projectile : m_game.get_projectiles())
  {
      //Every 7 projectile the projectile becames a cat
      if (m_game.get_projectiles().size() % 7 == 0){
      // Create the projectile sprite
      sf::RectangleShape rect(sf::Vector2f(220.0, 120.0));

      rect.setRotation(static_cast<float>(0));
      rect.setPosition(projectile.get_x(), projectile.get_y());
      rect.setTexture(&m_game_resources.get_cat());
      rect.rotate(projectile.get_direction() * 180 / M_PI);

      // Draw the cat
      m_window.draw(rect);
      }
      else {
          // Create the projectile sprite
          sf::RectangleShape rect(sf::Vector2f(100.0, 100.0));

          rect.setRotation(static_cast<float>(90));
          rect.setPosition(projectile.get_x(), projectile.get_y());
          rect.setTexture(&m_game_resources.get_rocket());
          rect.rotate(projectile.get_direction() * 180 / M_PI);

          // Draw the rocket
          m_window.draw(rect);
        }


  }
}


void game_view::draw_shelters() noexcept
{
  for (const auto &shelter : m_game.get_shelters())
  {
    sf::CircleShape circle(shelter.get_radius());
    circle.setPosition(shelter.get_x(), shelter.get_y());
    circle.setFillColor(sf::Color(get_redness(shelter), get_greenness(shelter),
                                  get_blueness(shelter),
                                  get_opaqueness(shelter)));
    m_window.draw(circle);
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

  draw_projectiles();

  draw_shelters();

  // Display all shapes
  m_window.display();
}

void game_view::play_sound()
{
  if(m_game.get_collision_flag()) {
      m_game_resources.get_sound(sound_type::bump).play();
    }
}
