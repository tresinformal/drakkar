#include "game_resources.h"

#include <cassert>
#include <QFile>

game_resources::game_resources()
{
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
}

void test_game_resources()
{
  game_resources g;
  assert(g.get_heterogenous_landscape().getSize().x > 0.0);
}
