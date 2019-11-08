#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class game_resources
{
public:
  game_resources();

  /// Get the texture of a heterogenous landscape
  sf::Texture& get_heterogenous_landscape() noexcept { return m_heterogenous_landscape; }

  sf::Music& get_ninja_gods() noexcept { return m_ninja_gods; }

private:


  /// A heterogenous landscape
  sf::Texture m_heterogenous_landscape;

  /// 'Ninja Gods' from Urho3D
  sf::Music m_ninja_gods;
};

/// Test the game resources
void test_game_resources();

#endif // GAME_RESOURCES_H
