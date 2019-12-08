#include "game_resources.h"

#include <QFile>
#include <cassert>

game_resources::game_resources()
{
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
}

void test_game_resources()
{
  game_resources g;
  assert(g.get_heterogenous_landscape().getSize().x > 0.0);
}
