#include "key_action_map.h"
#include <cassert>

key_action_map::key_action_map(
        const sf::Keyboard::Key& key_to_go_left,
        const sf::Keyboard::Key& key_to_go_right,
        const sf::Keyboard::Key& key_to_accelerate,
        const sf::Keyboard::Key& key_to_brake,
        const sf::Keyboard::Key& key_to_shoot
        ) : m_map {
{key_to_go_left, action_type::turn_left},
{key_to_go_right, action_type::turn_right},
{key_to_accelerate, action_type::accelerate},
{key_to_brake, action_type::brake},
{key_to_shoot, action_type::shoot}
                }
{
}

action_type key_action_map::to_action(sf::Keyboard::Key key) const noexcept
{
    if (has_key(key))
    {
        return m_map.find(key)->second;
    }
    return action_type::none;
}

key_action_map get_player_1_kam()
{
    return key_action_map();
}

key_action_map get_player_2_kam()
{
    return key_action_map(
                sf::Keyboard::J,
                sf::Keyboard::L,
                sf::Keyboard::I,
                sf::Keyboard::K,
                //sf::Keyboard::Comma,
                sf::Keyboard::U
                );
}

bool key_action_map::has_key(sf::Keyboard::Key key) const noexcept
{
    if (m_map.find(key) != m_map.end())
    {
        return true;
    }

    return false;

}

void test_key_action_map()//!OCLINT tests can be many
{
    //It is possible to return an action type from a key being pressed
    //The keys are for now the ones pressed by player1 (position 0 in the player index)
    {
        const key_action_map m; //Use player 1 as default for now
        assert(m.to_action(sf::Keyboard::A) == action_type::turn_left);
        assert(m.to_action(sf::Keyboard::D) == action_type::turn_right);
        assert(m.to_action(sf::Keyboard::W) == action_type::accelerate);
        assert(m.to_action(sf::Keyboard::S) == action_type::brake);
        assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
    }
    {
        const key_action_map m = get_player_1_kam();
        assert(m.to_action(sf::Keyboard::A) == action_type::turn_left);
        assert(m.to_action(sf::Keyboard::D) == action_type::turn_right);
        assert(m.to_action(sf::Keyboard::W) == action_type::accelerate);
        assert(m.to_action(sf::Keyboard::S) == action_type::brake);
        assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
    }
    {
        const sf::Keyboard::Key key_to_go_left = sf::Keyboard::C;
        const sf::Keyboard::Key key_to_go_right = sf::Keyboard::B;
        const sf::Keyboard::Key key_to_accelerate = sf::Keyboard::A;
        const sf::Keyboard::Key key_to_brake = sf::Keyboard::Z;
        const sf::Keyboard::Key key_to_shoot = sf::Keyboard::E;
        const key_action_map m(
                    key_to_go_left,
                    key_to_go_right,
                    key_to_accelerate,
                    key_to_brake,
                    key_to_shoot
                    );
        assert(m.to_action(key_to_go_left) == action_type::turn_left);
        assert(m.to_action(key_to_go_right) == action_type::turn_right);
        assert(m.to_action(key_to_accelerate) == action_type::accelerate);
        assert(m.to_action(key_to_brake) == action_type::brake);
        assert(m.to_action(key_to_shoot) == action_type::shoot);
    }
    {
        const key_action_map m = get_player_2_kam();
        assert(m.to_action(sf::Keyboard::J) == action_type::turn_left);
        assert(m.to_action(sf::Keyboard::L) == action_type::turn_right);
        assert(m.to_action(sf::Keyboard::I) == action_type::accelerate);
        assert(m.to_action(sf::Keyboard::K) == action_type::brake);
        //assert(m.to_action(sf::Keyboard::Comma) == action_type::acc_backward);
        assert(m.to_action(sf::Keyboard::U) == action_type::shoot);
    }
    {
        const key_action_map m = get_player_1_kam();
        assert( m.has_key(sf::Keyboard::A));
        assert( m.has_key(sf::Keyboard::D));
        assert( m.has_key(sf::Keyboard::W));
        assert( m.has_key(sf::Keyboard::S));
        assert( m.has_key(sf::Keyboard::Q));
        assert(!m.has_key(sf::Keyboard::L));
    }

    //Giving a key that is not in the map returns a action_type::none action
    //but does not crash the program
    {
        const key_action_map m = get_player_1_kam();
        assert(!m.has_key(sf::Keyboard::L));
        assert(action_type::none == m.to_action(sf::Keyboard::L));

    }

}
