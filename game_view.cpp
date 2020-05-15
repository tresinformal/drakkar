#include "game_view.h"
#include "food.h"
#include "game.h"
#include "game_resources.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "key_action_map.h"

game_view::game_view(game_options options) :
  m_window(sf::VideoMode(1280, 720), "tresinformal game"),
  m_v_views(
    m_game.get_v_player().size(),
    sf::View(
      sf::Vector2f(0,0),
      sf::Vector2f(m_window.getSize().x/2,m_window.getSize().y/2)
      )
    ),
  m_options(options)
{

  //Hardcoded postions of the three sf::views of the three players
  m_v_views[0].setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
  m_v_views[1].setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
  m_v_views[2].setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  if(m_options.is_playing_music())
    {
      m_game_resources.get_wonderland().setLoop(true);
      m_game_resources.get_wonderland().play();
    }
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

void game_view::pl_1_input(sf::Event event) noexcept
{
  const key_action_map m = get_player_1_kam();
  m_game.do_action(0, m.to_action(event.key.code));
}

void game_view::pl_2_input(sf::Event event) noexcept
{
  const key_action_map m = get_player_2_kam();
  m_game.do_action(1, m.to_action(event.key.code));
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

void game_view::draw_background() noexcept
{
  // Draw the background
  sf::Sprite background_sprite;
  background_sprite.setPosition(10.0, 10.0);
  //background_sprite.setTexture(m_game_resources.get_grass_landscape());
  background_sprite.setTexture(m_game_resources.get_heterogenous_landscape());
  background_sprite.setScale(16.0f, 16.0f);
  m_window.draw(background_sprite);
}

void game_view::draw_food() noexcept
{
  // Create food sprite
  sf::CircleShape foodsprite(25.0);
  // Get position of food
  std::vector<food> foods = m_game.get_food();
  // Position in landscape
  foodsprite.setPosition(static_cast<float>(foods[0].get_x()),
      static_cast<float>(foods[0].get_y()));
  foodsprite.setFillColor(sf::Color(0, 0, 0));
  m_window.draw(foodsprite);
}


void game_view::draw_players() noexcept //!OCLINT too long indeed, please
//! shorten
{
  for (const auto &player : m_game.get_v_player())
    {
      // Type conversions that simplify notation
      const float r{static_cast<float>(player.get_diameter()) / 2.0f};
      const float x{static_cast<float>(player.get_x())};
      const float y{static_cast<float>(player.get_y())};
      const float angle{static_cast<float>(player.get_direction())};
      const sf::Uint8 red{static_cast<sf::Uint8>(get_redness(player))};
      const sf::Uint8 green{static_cast<sf::Uint8>(get_greenness(player))};
      const sf::Uint8 blue{static_cast<sf::Uint8>(get_blueness(player))};

      // Create the player sprite
      sf::CircleShape circle;
      circle.setRadius(r);
      circle.setFillColor(sf::Color(red, green, blue));
      circle.setOutlineColor(sf::Color(red / 2, green / 2, blue / 2));
      circle.setOutlineThickness(2.0f);
      circle.setOrigin(r, r);
      circle.setPosition(x, y);
      circle.setRotation(angle  * 180.0f / M_PI);

      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(r, 2.0f));
      rect.setPosition(x, y);
      rect.setFillColor(sf::Color(red / 2, green / 2, blue / 2));
      rect.setRotation(angle  * 180.0f / M_PI);

      // Draw the player
      m_window.draw(circle);
      m_window.draw(rect);
    }
}

void game_view::draw_projectiles() noexcept
{
  for (const auto &projectile : m_game.get_projectiles())
    {
      if (projectile.get_type() == projectile_type::cat){
          // Create the projectile sprite
          sf::RectangleShape rect(sf::Vector2f(100.0, 100.0));
          rect.setRotation(static_cast<float>(90));
          rect.setPosition(projectile.get_x(), projectile.get_y());
          rect.setTexture(&m_game_resources.get_cat());
          rect.rotate(projectile.get_direction() * 180 / M_PI);
          m_window.draw(rect);
        }

      if (projectile.get_type() == projectile_type::rocket){
          // Create the projectile sprite
          sf::RectangleShape rect(sf::Vector2f(100.0, 100.0));
          rect.setRotation(static_cast<float>(90));
          rect.setPosition(projectile.get_x(), projectile.get_y());
          rect.setTexture(&m_game_resources.get_rocket());
          rect.rotate(projectile.get_direction() * 180 / M_PI);
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

  for(int i = 0; i != static_cast<int>(m_v_views.size()); i++){

      m_v_views[static_cast<unsigned int>(i)].setCenter(
            static_cast<float>(m_game.get_player(i).get_x()),
            static_cast<float>(m_game.get_player(i).get_y()));
      m_window.setView(m_v_views[static_cast<unsigned int>(i)]);

      draw_background();

      draw_players();

      draw_food();

      draw_projectiles();

      draw_shelters();
    }


  // Display all shapes
  m_window.display();
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

  //A game view is initialized with a number of views/cameras
  //Equal to the number of players
  {
    game_view v;
    assert(static_cast<int>(v.get_v_views().size()) -
           static_cast<int>(v.get_game().get_v_player().size()) == 0);
  }

  //Each view will show a rectangle half the height and half the side of the renderWindow

  {
    game_view v;
    for(const auto& view : v.get_v_views())
      {
        assert(view.getSize().x - v.get_window().getSize().x/2 < 0.00001f
               && view.getSize().x - v.get_window().getSize().x/2 > -0.00001f);
        assert(view.getSize().y - v.get_window().getSize().y/2 < 0.00001f
               && view.getSize().y - v.get_window().getSize().y/2 > -0.00001f);
      }
  }

  //Each view port will also be half the dimaensions of the render window
  //View will be initialized for the three default player like this
  //     Screen.begin                                  Screen.end
  //-------|------------xxxxxxxxxxxxxxxxxxxx-------------|---------
  //-------|------------xxxxxxxxxxxxxxxxxxxx-------------|---------
  //-------|------------xxxxxxxxxxxxxxxxxxxx-------------|---------
  //-------|------------xxxxxxxxxxxxxxxxxxxx-------------|---------
  //-------|---------------------------------------------|---------
  //-------|xxxxxxxxxxxxxxxxxxxx-----xxxxxxxxxxxxxxxxxxxx|---------
  //-------|xxxxxxxxxxxxxxxxxxxx-----xxxxxxxxxxxxxxxxxxxx|---------
  //-------|xxxxxxxxxxxxxxxxxxxx-----xxxxxxxxxxxxxxxxxxxx|---------
  //-------|xxxxxxxxxxxxxxxxxxxx-----xxxxxxxxxxxxxxxxxxxx|---------
  //!!!!this test looks tauthological to me. Do not knwo how to make it better @swom
  {
    game_view v;

    assert(v.get_v_views()[0].getViewport() == sf::FloatRect(0.f, 0.f, 0.5f, 0.5f) );
    assert(v.get_v_views()[1].getViewport() == sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f) );
    assert(v.get_v_views()[2].getViewport() == sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f) );
  }

  //It is possible to access the game options
  //the command .is_playing_music() is irrelevant
  //is just to see if get_options() correctlu returns the game options
  {
    game_view v;
    assert(v.get_options().is_playing_music());
  }
}


