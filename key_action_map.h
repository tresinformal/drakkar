#ifndef KEY_TO_ACTION_MAP_H
#define KEY_TO_ACTION_MAP_H
#include "action_type.h"
#include "SFML/Graphics.hpp"

/// Convert a key to an action
class key_action_map
{
public:

  ///Constructor
  key_action_map(
    const sf::Keyboard::Key& key_to_go_left = sf::Keyboard::A,
    const sf::Keyboard::Key& key_to_go_right = sf::Keyboard::D,
    const sf::Keyboard::Key& key_to_accelerate = sf::Keyboard::W,
    const sf::Keyboard::Key& key_to_brake = sf::Keyboard::S,
    const sf::Keyboard::Key& key_to_shoot = sf::Keyboard::Q
  );

  ///Find out which action is triggered by that key
  action_type to_action(sf::Keyboard::Key key) const noexcept;

  ///Find out if the key is mapped
  bool has_key(sf::Keyboard::Key key) const noexcept;

private:
  sf::Keyboard::Key m_key_to_go_left;
  sf::Keyboard::Key m_key_to_go_right;
  sf::Keyboard::Key m_key_to_accelerate;
  sf::Keyboard::Key m_key_to_brake;
  sf::Keyboard::Key m_key_to_shoot;
};

/// Get the default key to action map for player 1
key_action_map get_player_1_kam();

/// Get the default key to action map for player 2
key_action_map get_player_2_kam();

/// Get the default key to action map for player 3
//key_action_map get_player_3_kam();

/// Check if key has action

void test_key_action_map();

#endif // KEY_TO_ACTION_MAP_H
