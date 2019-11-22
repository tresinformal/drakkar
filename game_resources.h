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

  /// Get the texture of a heterogenous landscape
  sf::Texture& get_grass_landscape() noexcept { return m_grass_landscape; }

  #ifndef IS_ON_TRAVIS
  //Playing sound on Travis gives thousands of error lines, which causes the build to fail
  sf::Music& get_ninja_gods() noexcept { return m_ninja_gods; }
  #endif // IS_ON_TRAVIS

private:


  /// A grass landscape
  sf::Texture m_grass_landscape;

  /// A heterogenous landscape
  sf::Texture m_heterogenous_landscape;

  #ifndef IS_ON_TRAVIS
  //Playing sound on Travis gives thousands of error lines, which causes the build to fail
  /// 'Ninja Gods' from Urho3D
  sf::Music m_ninja_gods;
  #endif // IS_ON_TRAVIS
};

/// Test the game resources
void test_game_resources();

#endif // GAME_RESOURCES_H
