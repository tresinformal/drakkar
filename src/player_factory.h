#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H
#include "player.h"

class player_factory
{
  std::string m_ID;

public:

  player_factory();
  void set_id(const std::string& ID){m_ID = ID;}

  player create() {return create_player_with_id(m_ID);}
};

void test_player_factory();

#endif // PLAYER_FACTORY_H
