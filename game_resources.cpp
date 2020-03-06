#include "game_resources.h"

#include <QFile>
#include <cassert>

game_resources::game_resources()
{
  {
    const QString filename{"rocket_sprite.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_rocket.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
  {
    const QString filename{"franjo.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_franjo.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
  {
    const QString filename{"cat.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_cat.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
  {
    const QString filename{"heterogenous_landscape.jpg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_heterogenous_landscape.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
  {
    const QString filename{"grass_landscape.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_grass_landscape.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
  {
    const QString filename{"player_sprite.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_player_sprite.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  {
    const QString filename{"ninja_gods.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_ninja_gods.openFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find sound file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#endif // IS_ON_TRAVIS
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  // load menu music "wonderland"
  {
    const QString filename{"wonderland.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_wonderland.openFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find sound file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#endif // IS_ON_TRAVIS
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  // load sound for shooting
  {
    const QString filename{"shoot.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_shoot.openFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find sound file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#endif // IS_ON_TRAVIS
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  // load sound for bumping into something/someone
  {
    const QString filename{"bump.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_bump.openFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find sound file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#endif // IS_ON_TRAVIS

}

#ifndef IS_ON_TRAVIS
  /// Get sound and specify which sound to get
sf::Music& game_resources::get_sound(sound_type sound)
{
  switch (sound) {
    case sound_type::bump :
      return m_bump;
    case sound_type::shoot :
      return m_shoot;
    default:
      return m_shoot;
    }
}
#endif // IS_ON_TRAVIS

void test_game_resources()
{
  game_resources g;
  assert(g.get_heterogenous_landscape().getSize().x > 0.0);


  assert(g.get_sound(sound_type::shoot).getDuration().asMicroseconds() > 0.0);

}
