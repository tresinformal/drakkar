#include "game.h"
#include <cassert>
#include<iostream>
#include<cmath>

game::game(const int n_ticks, environment_type environment_type)
 : m_n_ticks{n_ticks},
   m_v_player{2, player()},
   m_environment_type{environment_type},
   m_food{1}
{
  m_v_player[0] = player(300.0,400.0, player_shape::rocket);
}

double game::get_player_direction( unsigned int player_ind)
{return get_player(player_ind).get_direction();}


double get_player_direction(game g, unsigned int player_ind)
{return g.get_player(player_ind).get_direction();}

void test_game() //!OCLINT tests may be many
{
  // The game has done zero ticks upon startup
  {
    const game g;
    // n_ticks is the number of times the game is displayed on screen
    assert(g.get_n_ticks() == 0);
  }
  // A game has a vector of players
  {
    const game g;
    // The value 1234.5 is irrelevant: just get this to compile
    for(unsigned int i = 0; i < g.get_v_player().size(); ++i)
    {
    assert(g.get_player(i).get_x() > -1234.5);
    }
  }
  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty());
  }
  // A game by default  has an empty environment
  {
    const game g;
    assert(g.get_environment_type()==environment_type::empty );
  }
  // a game initialized with an environment has that environment
  {
    const game g{0, environment_type::random};
    assert(g.get_environment_type()==environment_type::random);
    assert(static_cast<int>(g.get_environment_type())!=9);
  }
  // A game responds to actions: player can turn left
  {
    game g;
    for (unsigned int i = 0; i< g.get_v_player().size();++i)
    {
    const double before{g.get_player(i).get_direction()};
    g.get_player(i).do_action(action_type::turn_left);
    const double after{g.get_player(i).get_direction()};
    assert( std::abs(before-after) > 0.01); //Should be different
    }
  }
  // A game responds to actions: player can turn right
  {
    game g;
    for (unsigned int i = 0; i< g.get_v_player().size();++i)
    {
    const double before{g.get_player(i).get_direction()};
    g.get_player(i).do_action(action_type::turn_right);
    const double after{g.get_player(i).get_direction()};
    assert( std::abs(before-after) > 0.01); //Should be different
    }
  }
  // A game responds to actions: player can accelerate
  {
    game g;
    for (unsigned int i = 0; i< g.get_v_player().size();++i)
    {
    const double before{g.get_player(i).get_speed()};
    g.get_player(i).do_action(action_type::accelerate);
    const double after{g.get_player(i).get_speed()};
    assert( before-after < 0.01); //After should be > than before
    }
  }
  // A game responds to actions: player can break
  {
    game g;
    for (unsigned int i = 0; i< g.get_v_player().size();++i)
    {
    g.get_player(i).do_action(action_type::accelerate);//just to give the player a speed of more than 0
    const double before{g.get_player(i).get_speed()};
    g.get_player(i).do_action(action_type::brake);
    const double after{g.get_player(i).get_speed()};
    assert( before-after > 0.0000000000000001); //After should be < than before
    }
  }
  //Can get a player's direction by using a free function
  {
    const game g;
    for (unsigned int i = 0; i< g.get_v_player().size();++i)
    {
    const double a{g.get_player(i).get_direction()};
    const double b{get_player_direction(g,i)};
    assert(std::abs(b - a) < 0.0001);
    }
  }
  //game by default has a mix and max evironment size
  {
    game g;
    assert(g.get_environment().get_max_x() > -56465214.0);
  }
  #ifdef FIX_ISSUE_94
  // A game has enemies
  {
    const game g;
    assert(!g.get_enemies().empty());
  }
  #endif //FIX_ISSUE_89
}
