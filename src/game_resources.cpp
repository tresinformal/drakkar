#include "game_resources.h"

#include <QResource>
#include <QFile>
#include <cassert>

game_resources::game_resources()
{
  {
    QResource artWork1 { ":/276813041_drakkar__dragon__realistic__flying__paper__rock__scissors__RGB__3.png" };
    m_artwork_1.loadFromMemory(artWork1.data(), artWork1.size());
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
    const QString filename{"marjon_the_dragon.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_dragon.loadFromFile(filename.toStdString()))
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
    /*
    const QString filename{"heterogenous_landscape.jpg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_heterogenous_landscape.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find image file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
    */
    sf::Image image;
    const int width{256};
    const int height{256};
    image.create(width, height);
    for (int x{0}; x!=width; ++x)
    {
      for (int y{0}; y!=height; ++y)
      {
        const sf::Uint8 r{static_cast<sf::Uint8>((x * 16) % 256)};
        const sf::Uint8 g{static_cast<sf::Uint8>((y * 16)  % 256)};
        const sf::Uint8 b{static_cast<sf::Uint8>((((x + y) * 16) % 256))};
        image.setPixel(
          static_cast<unsigned int>(x),
          static_cast<unsigned int>(y),
          sf::Color(r, g, b)
        );
      }
    }
    m_heterogenous_landscape.loadFromImage(image);
  }
  {
    const QString filename{"coastal_world.png"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_coastal_world.loadFromFile(filename.toStdString()))
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
  /// Load font file
  {
    const QString filename{"arial.ttf"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_font.loadFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find font file '" + filename + "'"};
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
#ifndef IS_ON_TRAVIS
  // Playing sound on Travis gives thousands of error lines, which causes the
  // build to fail
  {
    const QString filename{"grow.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_grow.openFromFile(filename.toStdString()))
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
    const QString filename{"shrink.ogg"};
    QFile f(":/" + filename);
    f.copy(filename);
    if (!m_shrink.openFromFile(filename.toStdString()))
    {
      QString msg{"Cannot find sound file '" + filename + "'"};
      throw std::runtime_error(msg.toStdString());
    }
  }
#endif // IS_ON_TRAVIS
}

void test_game_resources()
{
  #ifndef NDEBUG // no tests in release

  game_resources g;
  assert(g.get_coastal_world().getSize().x > 0.0);
  assert(g.get_artwork_1().getSize().x > 0.0);

#ifdef FIX_ISSUE_724
 // (724) Button sprites are loaded and ready to use
  {
    game_resources gr;
    gr.get_blue_button();
    gr.get_green_button();
    gr.get_red_button();
    gr.get_yellow_button();
    gr.get_grey_button();
  }
#endif // FIX_ISSUE_724

  #endif // NDEBUG
}
