#include "game.h"
#include <cassert>
#include<iostream>
#include<cmath>

game::game(const int n_ticks, environment_type environment_type)
 : m_n_ticks{n_ticks},
   m_player{0.0, 0.0, player_shape::rocket},
   m_environment_type{environment_type},
   m_food{1}
{
}

double get_player_direction(game g) {return g.get_player().get_direction();}

///For now only turn_left command actually does something, to be decided how the it and the
/// rest will really work later after voting

void game::do_action(action_type action){

    switch (action) {
    case action_type::turn_left :{
        get_ref_player().turn_left();
        break;
    }
    case action_type::turn_right :{
        break;
    }
    case action_type::accelerate :{
        break;
    }
    case action_type::brake   :{
        break;
    }
    }
}

void test_game() //!OCLINT tests may be many
{
  // The game has done zero ticks upon startup
  {
    const game g;
    // n_ticks is the number of times the game is displayed on screen
    assert(g.get_n_ticks() == 0);
  }
  // A game has a player
  {
    const game g;
    // The value 1234.5 is irrelevant: just get this to compile
    assert(g.get_player().get_x() > -1234.5);
  }

  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty());
  }

  #define FIX_ISSUE_54
  #ifdef FIX_ISSUE_54
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
  #endif

#define FIX_ISSUE_68
  #ifdef FIX_ISSUE_68
  // A game responds to actions: player can turn left
  {
    game g;
    const double before{g.get_player().get_direction()};
    g.do_action(action_type::turn_left);
    const double after{g.get_player().get_direction()};
    assert( std::abs(before-after) > 0.01); //Should be different
  }
  #endif // FIX_ISSUE_68

   {
    const game g;
    const double a{g.get_player().get_direction()};
    const double b{get_player_direction(g)};

    assert(std::abs(b - a) < 0.0001);
  }

  //game by default has a mix and max evironment size
  {
    game g;
    assert(g.get_environment().get_max_x() > -56465214.0);
  }

}
