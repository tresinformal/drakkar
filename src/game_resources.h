#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class game_resources
{
public:
  game_resources();

  /// Get the texture of a heterogenous landscape
  sf::Texture &get_heterogenous_landscape() noexcept { return m_heterogenous_landscape; }

  /// Get the texture of a heterogenous landscape
  sf::Texture &get_coastal_world() noexcept { return m_coastal_world; }

  /// Get the texture of a heterogenous landscape
  sf::Texture &get_grass_landscape() noexcept { return m_grass_landscape; }

  /// Get the texture of a the player
  sf::Texture &get_player_sprite() noexcept { return m_player_sprite; }

  /// Get a picture of a Marjon the dragon
  sf::Texture &get_dragon() noexcept { return m_dragon; }

  /// Get a picture of Franjo
  sf::Texture &get_franjo() noexcept { return m_franjo; }

  /// Get a picture of Rocket
  sf::Texture &get_rocket() noexcept { return m_rocket; }

  /// Get a picture of stun rocket
  sf::Texture &get_stun_rocket() noexcept { return m_stun_rocket; }

  /// Get a picture of a Cat
  sf::Texture &get_cat() noexcept { return m_cat; }

  /// Get a font
  sf::Font &get_font() noexcept {return m_font; }

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  sf::Music &get_ninja_gods() noexcept { return m_ninja_gods; }
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// Get music file
  sf::Music &get_wonderland() noexcept { return m_wonderland; }
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// Get 'shoot' sound
  sf::Music &get_shoot() noexcept { return m_shoot; }
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// Get 'bump' sound
  sf::Music &get_bump() noexcept { return m_bump; }
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// Get 'grow' sound
  sf::Music &get_grow() noexcept { return m_grow; }
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// Get 'shrink' sound
  sf::Music &get_shrink() noexcept { return m_shrink; }
#endif // IS_ON_TRAVIS

private:
  /// Franjo
  sf::Texture m_franjo;

  /// Dragon
  sf::Texture m_dragon;

  /// Rocket
  sf::Texture m_rocket;

  /// Stun rocket
  sf::Texture m_stun_rocket;

  /// A grass landscape
  sf::Texture m_grass_landscape;

  /// Player sprite
  sf::Texture m_player_sprite;

  /// A heterogenous landscape
  sf::Texture m_heterogenous_landscape;

  /// A coastal world
  sf::Texture m_coastal_world;

  /// Font
  sf::Font m_font;

  /// Rocket
  sf::Texture m_cat;
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// 'Ninja Gods' from Urho3D
  sf::Music m_ninja_gods;
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// 'wonderland' from Sebastian
  sf::Music m_wonderland;
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// 'shoot' sound from Sebastian
  sf::Music m_shoot;
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  /// 'bump' sound from Sebastian
  sf::Music m_bump;
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  sf::Music m_grow;
#endif // IS_ON_TRAVIS

#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  sf::Music m_shrink;
#endif // IS_ON_TRAVIS
};

/// Test the game resources
void test_game_resources();

#endif // GAME_RESOURCES_H
