#include "key_action_map.h"
#include <cassert>

key_action_map::key_action_map()
{

}

action_type key_action_map::to_action(sf::Keyboard::Key key) const noexcept
{
  switch (key) {
    case sf::Keyboard::A :
      return action_type::turn_left;
    case sf::Keyboard::D :
      return action_type::turn_right;
    case sf::Keyboard::W :
      return action_type::accelerate;
    case sf::Keyboard::S :
      return action_type::brake;
    case sf::Keyboard::Q :
      return action_type::shoot;
    default:
      assert( 1 == 2);
      return action_type::brake;
    }
}

void test_key_action_map()
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

}
