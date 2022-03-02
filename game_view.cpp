#include "game_view.h"

#ifndef LOGIC_ONLY // so this is NOT compiled on GitHub Actions

#include "food.h"
#include "food_type.h"
#include "game.h"
#include "game_resources.h"
#include "game_functions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <string>
#include <sstream>

game_view::game_view(game_options options) :
    m_window(sf::VideoMode(1280, 720), "tresinformal game"),
    m_v_views(
        m_game.get_v_player().size(),
        sf::View(
            sf::Vector2f(0,0),
            sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2)
            )
        ),
    m_options(options)
{

    //Hardcoded positions of the three sf::views of the three players
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

player player_input(player p, sf::Event event)
{
    auto m = get_player_kam(p);
    add_action(p, m.to_action(event.key.code));
    return p;
}

player player_stop_input(player p, sf::Event event) noexcept
{
    const auto m = get_player_kam(p);
    remove_action(p, m.to_action(event.key.code));
    return p;
}

void game_view::pl_1_stop_input(sf::Event event) noexcept
{
    const key_action_map m = get_player_1_kam();
    remove_action(m_game.get_player(0), m.to_action(event.key.code));
}

void game_view::pl_2_stop_input(sf::Event event) noexcept
{
    const key_action_map m = get_player_2_kam();
    remove_action(m_game.get_player(0), m.to_action(event.key.code));
}

void game_view::pl_3_stop_input(sf::Event event) noexcept
{
    const key_action_map m = get_player_3_kam();
    remove_action(m_game.get_player(0), m.to_action(event.key.code));
}

int count_n_projectiles(const game_view &g) noexcept
{
  return count_n_projectiles(g.get_game());
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
            sf::Keyboard::Key key_pressed = event.key.code;
            if (key_pressed == sf::Keyboard::Key::Escape)
              {
                m_next_view = view_mode::menu;
                return true;
              }
            else {
                for(auto& player : m_game.get_v_player())
                  {
                    player = player_input(player,event);
                  }
              }
          }
        else if (event.type == sf::Event::KeyReleased)
        {
            for(auto& player : m_game.get_v_player())
            {
                player = player_stop_input(player,event);
            }
        }

    }
    m_game.tick();
    return false; // if no events proceed with tick
}

void game_view::exec() noexcept
{
  while (m_window.isOpen())
  {
    const bool must_quit{process_events()}; // This is where stun is processed
    if (must_quit) return;
    m_game.tick();
    show();
  }
}

void game_view::draw_background() noexcept
{
    // Draw the background
    sf::Sprite background_sprite;
    background_sprite.setPosition(10.0, 10.0);
    sf::Texture background_texture = m_game_resources.get_coastal_world();
    background_sprite.setTexture(background_texture);
    // Scale background so it fits the entire environment
    double scaling_factor_x = get_max_x(m_game.get_env()) / background_texture.getSize().x;
    double scaling_factor_y = get_max_y(m_game.get_env()) / background_texture.getSize().y;
    background_sprite.setScale(scaling_factor_x, scaling_factor_y);
    m_window.draw(background_sprite);
}

void game_view::draw_food() noexcept
{
    // Create food sprite
    sf::CircleShape foodsprite(25.0);
    // Get position of food
    std::vector<food> foods = m_game.get_food();
    // Position in landscape
    food f = foods[0];
    foodsprite.setPosition(static_cast<float>(get_x(f)),
            static_cast<float>(get_y(f)));
    foodsprite.setFillColor(sf::Color(0, 0, 0));
    if (!f.is_eaten()) {
        m_window.draw(foodsprite);
      }
}

void game_view::press_key(const sf::Keyboard::Key& k)
{
    if(k == sf::Keyboard::E) {
      /// stunning not shooting a rocket
      this->m_game.do_action(0, action_type::shoot_stun_rocket);
    }
}


void game_view::draw_players() noexcept //!OCLINT too long indeed, please
//! shorten
{
    for (const auto &player : m_game.get_v_player())
    {
        if(is_dead(player))
          {
            continue;
          }
        // Type conversions that simplify notation
        const float r{static_cast<float>(player.get_diameter()) / 2.0f};
        const float x{static_cast<float>(get_x(player))};
        const float y{static_cast<float>(get_y(player))};
        const float angle{static_cast<float>(player.get_direction())};
        const sf::Uint8 red{static_cast<sf::Uint8>(get_redness(player))};
        const sf::Uint8 green{static_cast<sf::Uint8>(get_greenness(player))};
        const sf::Uint8 blue{static_cast<sf::Uint8>(get_blueness(player))};

        // Create the player sprite
        sf::CircleShape circle;
        circle.setRadius(r);
        circle.setFillColor(sf::Color(red, green, blue));
        circle.setTexture(&m_game_resources.get_dragon());
        circle.setOrigin(r, r);
        circle.setPosition(x, y);
        circle.setRotation((angle  * 180.0f / M_PI) - 90);

//        sf::RectangleShape rect;
//        rect.setSize(sf::Vector2f(r, 2.0f));
//        rect.setPosition(x, y);
//        rect.setFillColor(sf::Color(red / 2, green / 2, blue / 2));
//        rect.setRotation(angle  * 180.0f / M_PI);

        // Draw the player
        m_window.draw(circle);
//        m_window.draw(rect);
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
            rect.setPosition(get_x(projectile), get_y(projectile));
            rect.setTexture(&m_game_resources.get_cat());
            rect.rotate(projectile.get_direction() * 180 / M_PI);
            m_window.draw(rect);
        }

        if (projectile.get_type() == projectile_type::rocket){
            // Create the projectile sprite
            sf::RectangleShape rect(sf::Vector2f(100.0, 100.0));
            rect.setRotation(static_cast<float>(90));
            rect.setPosition(get_x(projectile), get_y(projectile));
            rect.setTexture(&m_game_resources.get_rocket());
            rect.rotate(projectile.get_direction() * 180 / M_PI);
            m_window.draw(rect);
        }

        if (projectile.get_type() == projectile_type::stun_rocket){
            // Create the projectile sprite
            sf::RectangleShape rect(sf::Vector2f(381.0, 83.0));
            rect.setRotation(static_cast<float>(0));
            rect.setPosition(get_x(projectile), get_y(projectile));
            rect.setTexture(&m_game_resources.get_stun_rocket());
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
        circle.setPosition(get_x(shelter), get_y(shelter));
        circle.setFillColor(sf::Color(get_redness(shelter), get_greenness(shelter),
                                      get_blueness(shelter),
                                      get_opaqueness(shelter)));
        m_window.draw(circle);
    }
}

void game_view::set_player_coords_view() noexcept
{
    sf::View player_coords_view(
                sf::Vector2f(m_window.getSize().x / 4.5, m_window.getSize().y / 4.5),
                sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2)
                );
    player_coords_view.setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 0.5f));
    m_window.setView(player_coords_view);
}

void game_view::draw_player_coords() noexcept
{
    sf::Text text;
    text.setFont(m_game_resources.get_font());

    // Concatenate player coordinates string
    std::vector<player> v_player = m_game.get_v_player();
    std::string str_player_coords;
    for(int i = 0; i != static_cast<int>(v_player.size()); i++) {
        player p = v_player[static_cast<unsigned int>(i)];
        str_player_coords += "Player " + p.get_ID() + " x = " + std::to_string(trunc(get_x(p)));
        str_player_coords += "\nPlayer " + p.get_ID() + " y = " + std::to_string(trunc(get_y(p)));
        str_player_coords += "\n\n";
    }
    food f = m_game.get_food()[0];
    str_player_coords += "Food x = " + std::to_string(trunc(get_x(f)));
    str_player_coords += "y = " + std::to_string(trunc(get_y(f)));
    str_player_coords += "\n\n";

    text.setString(str_player_coords);

    m_window.draw(text);
}

void game_view::show() noexcept
{
    // Start drawing the new frame, by clearing the screen
    m_window.clear();

    for(int i = 0; i != static_cast<int>(m_v_views.size()); i++){

        m_v_views[static_cast<unsigned int>(i)].setCenter(
                    static_cast<float>(get_x(m_game.get_player(i))),
                    static_cast<float>(get_y(m_game.get_player(i))));
        m_window.setView(m_v_views[static_cast<unsigned int>(i)]);

        draw_background();

        draw_players();

        draw_food();

        draw_projectiles();

        draw_shelters();
    }

    // Set fourth view for players coordinates
    #ifndef NDEBUG  // coordinates should not be visible in release
    set_player_coords_view();
    // Display player coordinates on the fourth view
    draw_player_coords();
    #endif

    // Display all shapes
    m_window.display();
}

key_action_map get_player_kam(const player& p)
{
    if(p.get_ID() == "0")
    {
        return get_player_1_kam();
    }
    else if(p.get_ID() == "1")
    {
        return  get_player_2_kam();
    }
    else if(p.get_ID() == "2")
    {
        return  get_player_3_kam();
    }
    else
    {
        //for now return a weird action map
        return
                key_action_map
        {sf::Keyboard::P,
                    sf::Keyboard::P,
                    sf::Keyboard::P,
                    sf::Keyboard::P,
                    sf::Keyboard::P};
    }
}

bool is_nth_player_stunned(const game_view& g, const int& p) noexcept
{
    game g1 = g.get_game();
    player p1 = g1.get_player(p);
    return is_stunned(p1);
}

void test_game_view() //!OCLINT tests may be many
{
    #ifndef NDEBUG // no tests in release
    {
        // Show the game for one frame
        // (there will be a member function 'exec' for running the game)
        game_view v;
        v.show();
    }

    {
    const game_view v;
    // game has a member function called `get_n_ticks`, which returns zero upon construction
    assert(v.get_game().get_n_ticks() == 0);
    }

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

    //Each view port will also be half the dimensions of the render window
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
    //!!!!this test looks tauthological to me. Do not know how to make it better @swom
    {
        game_view v;

        assert(v.get_v_views()[0].getViewport() == sf::FloatRect(0.f, 0.f, 0.5f, 0.5f) );
        assert(v.get_v_views()[1].getViewport() == sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f) );
        assert(v.get_v_views()[2].getViewport() == sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f) );
    }

    //It is possible to access the game options
    //the command .is_playing_music() is irrelevant
    //is just to see if get_options() correctly returns the game options
    {
        game_view v;
        assert(v.get_options().is_playing_music());
    }

#define FIX_ISSUE_167
#ifdef FIX_ISSUE_167
    ///given a player get_player_kam provides the correct player kam
    {
        player p;
        assert(p.get_ID() == "0");
        assert(get_player_kam(p).get_raw_map() == get_player_1_kam().get_raw_map());
        assert(get_player_kam(p).get_raw_map() != get_player_2_kam().get_raw_map());

        p =  create_player_with_id("1");
        assert(get_player_kam(p).get_raw_map() == get_player_2_kam().get_raw_map());
        p =  create_player_with_id("2");
        assert(get_player_kam(p).get_raw_map() == get_player_3_kam().get_raw_map());
    }
#endif

#define FIX_ISSUE_183
#ifdef FIX_ISSUE_183
    ///given a player get_player_kam provides the correct player kam
    {
        player p;
        assert(p.get_ID() == "0");
        assert(get_player_kam(p).get_raw_map() == get_player_1_kam().get_raw_map());
        assert(get_player_kam(p).get_raw_map() != get_player_2_kam().get_raw_map());

        p =  create_player_with_id("1");
        assert(get_player_kam(p).get_raw_map() == get_player_2_kam().get_raw_map());
        p =  create_player_with_id("2");
        assert(get_player_kam(p).get_raw_map() == get_player_3_kam().get_raw_map());

    }
#endif

    ///Given a player and an event
    ///player_input sees if any action has to be applied to the player
    {
        player p0;
        player p1;

        p0 = create_player_with_id("0");
        p1 = create_player_with_id("1");

        sf::Event move_forward_pl_1;
        move_forward_pl_1.key.code = sf::Keyboard::W;

        p0 = player_input(p0,move_forward_pl_1);
        p1 = player_input(p1,move_forward_pl_1);

        assert(p0.get_action_set() == std::set<action_type>{action_type::accelerate} );
        assert(p1.get_action_set() == std::set<action_type>{action_type::none} );

    }

    ///Given a player and an event
    ///player_stop_input() sees if any action has to be removed from the player
    {
        player p0;
        player p1;

        p0 = create_player_with_id("0");
        add_action(p0,action_type::accelerate);

        p1 = create_player_with_id("1");
        add_action(p1,action_type::accelerate);

        sf::Event stop_move_forward_pl_1;
        stop_move_forward_pl_1.key.code = sf::Keyboard::W;

        p0 = player_stop_input(p0,stop_move_forward_pl_1);
        p1 = player_stop_input(p1,stop_move_forward_pl_1);

        assert(p0.get_action_set().empty());
        assert(p1.get_action_set() == std::set<action_type>{action_type::accelerate} );

    }

  // Pressing 1 stuns player 1
  {
    game_view g;
    assert(count_n_projectiles(g) == 0);
    g.press_key(sf::Keyboard::E);
    g.process_events(); // Needed to process the event
    //  #ifdef FIX_ISSUE_239
    assert(count_n_projectiles(g) == 1);
  }

  #ifdef FIX_ISSUE_494
  // (494) There should be a member of type view_mode
  {
    game_view gv;
    view_mode expected_next_view = view_mode::quit;
    assert(gv.what_next() == expected_next_view);
  }
  #endif

  #endif
}

#endif // LOGIC_ONLY
