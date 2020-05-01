#include "key_action_map.h"
#include <cassert>

key_action_map::key_action_map(
  const sf::Keyboard::Key& key_to_go_left,
  const sf::Keyboard::Key& key_to_go_right,
  const sf::Keyboard::Key& key_to_accelerate,
  const sf::Keyboard::Key& key_to_brake,
  const sf::Keyboard::Key& key_to_shoot
) : m_key_to_go_left{key_to_go_left},
    m_key_to_go_right{key_to_go_right},
    m_key_to_accelerate{key_to_accelerate},
    m_key_to_brake{key_to_brake},
    m_key_to_shoot{key_to_shoot}
{

}

action_type key_action_map::to_action(sf::Keyboard::Key key) const noexcept
{
  if (key == m_key_to_go_left)
  {
    return action_type::turn_left;
  }
  if (key == m_key_to_go_right)
  {
    return action_type::turn_right;
  }
  if (key == m_key_to_accelerate)
  {
    return action_type::accelerate;
  }
  if (key == m_key_to_brake)
  {
    return action_type::brake;
  }
  if (key == m_key_to_shoot)
  {
    return action_type::shoot;
  }
  assert(!"Should never get there");
  return action_type::brake;
}

key_action_map get_player_1_kam()
{
  return key_action_map();
}

key_action_map get_player_2_kam()
{
  return key_action_map(
    sf::Keyboard::L,
    sf::Keyboard::J,
    sf::Keyboard::I,
    sf::Keyboard::K,
    //sf::Keyboard::Comma,
    sf::Keyboard::U
  );
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
    assert(m.to_action(sf::Keyboard::L) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::J) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::I) == action_type::accelerate);
    assert(m.to_action(sf::Keyboard::K) == action_type::brake);
    //assert(m.to_action(sf::Keyboard::Comma) == action_type::acc_backward);
    assert(m.to_action(sf::Keyboard::U) == action_type::shoot);
  }
  #ifdef FIX_ISSUE_174
  {
    const key_action_map m = get_player_1_kam();
    assert( m.has_key(sf::Keyboard::A));
    assert(!m.has_key(sf::Keyboard::L));
  }
  #endif // FIX_ISSUE_174
}