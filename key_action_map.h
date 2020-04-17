#ifndef KEY_TO_ACTION_MAP_H
#define KEY_TO_ACTION_MAP_H
#include "action_type.h"
#include "SFML/Graphics.hpp"

class key_action_map
{
public:
  key_action_map();
  action_type to_action(sf::Keyboard::Key key) const noexcept;
};

void test_key_action_map();

#endif // KEY_TO_ACTION_MAP_H
