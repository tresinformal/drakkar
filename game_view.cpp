#include "game_view.h"
#include "game.h"
#include "game_resources.h"
#include "food.h"
#include <SFML/Graphics.hpp>
#include <cmath>


game_view::game_view():
    m_window(sf::VideoMode(1280, 720), "tresinformal game")
{
#ifndef IS_ON_TRAVIS
    //Playing sound on Travis gives thousands of error lines, which causes the build to fail
    m_game_resources.get_ninja_gods().setLoop(true);
    m_game_resources.get_ninja_gods().play();
#endif
}

game_view::~game_view()
{
#ifndef IS_ON_TRAVIS
    //Playing sound on Travis gives thousands of error lines, which causes the build to fail
    m_game_resources.get_ninja_gods().stop();
#endif // IS_ON_TRAVIS
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


            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    m_game.do_action(action_type::turn_left);
                }
                else if (event.key.code == sf::Keyboard::A){
                    m_game.do_action(action_type::turn_right);
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    m_game.do_action(action_type::accelerate);
                }
                else if (event.key.code == sf::Keyboard::S){
                    m_game.do_action(action_type::brake);
                }
                else{
                    break;
                }
            }

        }
        // apply inertia  and attrition
        if(m_game.get_player(0).get_speed()>0){
          //momentarly using brake action, do not know to what assign this
          //function. To game or to player?
          //Both will need this functions for this to happen.
          //And should this function take some value from environment?
          m_game.do_action(action_type::brake);
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
    background_sprite.setPosition(10.0,10.0);
    background_sprite.setTexture(m_game_resources.get_heterogenous_landscape());
    m_window.draw(background_sprite);

    //Create the player sprite
    sf::RectangleShape rect(sf::Vector2f(200.0, 100.0));
    //Set the center of rotation as the center of the shape
    rect.setOrigin(rect.getSize().x/2,rect.getSize().y/2);
    rect.setPosition(
               static_cast<float>(m_game.get_player(0).get_x()),
               static_cast<float>(m_game.get_player(0).get_y())
                );
    rect.setRotation(static_cast<float>((m_game.get_player(0).get_direction())*180/M_PI));
    //Draw the player
    m_window.draw(rect);

    // Create food sprite
    sf::CircleShape foodsprite(25.0);
    // Get position of food
    std::vector foods = m_game.get_food();
    // Position in landscape
    foodsprite.setPosition(
                static_cast<float>(foods[0].get_x()),
                static_cast<float>(foods[0].get_y())
                );
    foodsprite.setFillColor(sf::Color(0, 0, 0));
    m_window.draw(foodsprite);

    //Draw some semitransparent circles to see how well RGB/opsin-based vision works out
    sf::CircleShape circle(200.0);
    //Red
    circle.setPosition(600.0, 200.0);
    circle.setFillColor(sf::Color(255, 0, 0, 128));
    m_window.draw(circle);
    //Green
    circle.setPosition(600.0, 500.0);
    circle.setFillColor(sf::Color(0, 255, 0, 128));
    m_window.draw(circle);
    //Blue
    circle.setPosition(800.0, 350.0);
    circle.setFillColor(sf::Color(0, 0, 255, 128));
    m_window.draw(circle);

    //Display all shapes
    m_window.display();
}
