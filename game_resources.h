#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#include <SFML/Graphics.hpp>

class game_resources
{
public:
  game_resources();

  /// Get the texture of a heterogenous landscape
  const sf::Texture& get_heterogenous_landscape() const noexcept { return m_heterogenous_landscape; }

private:

  /// A heterogenous landscape
  sf::Texture m_heterogenous_landscape;
};

/// Test the game resources
void test_game_resources();

#endif // GAME_RESOURCES_H
