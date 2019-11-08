#include "game.h"
#include <cassert>

game::game(const int n_ticks, environment_type environment)
 : m_n_ticks{n_ticks},
   m_player{0.0, 0.0, player_shape::rocket},
   m_environment{environment}
{
}

void test_game()
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
  #ifdef FIX_ISSUE_39
  // A game has food items
  {
    const game g;
    assert(!g.get_food().empty);
  }
  #endif

  #define FIX_ISSUE_54
  #ifdef FIX_ISSUE_54
    // A game by default  has an empty environment
      {
        const game g;
        assert(g.get_environment()==environment_type::empty );
      }
    // a game initialized with an environment has that environment
      {
        const game g{0, environment_type::random};
        assert(g.get_environment()==environment_type::random);
        assert(static_cast<int>(g.get_environment())!=9);
      }
  #endif

  #ifdef FIX_ISSUE_68
  // A game responds to actions: player can turn left
  {
    game g;
    const double before{g.get_player().get_direction()};
    g.do_action(action_type::turn_left);
    const double after{g.get_player().get_direction()};
    assert(std::abs(before - after) > 0.01); //Should be different
  }
  #endif // FIX_ISSUE_68
  #ifdef FIX_ISSUE_71
  {
    const game g;
    const double a{g.get_player().get_direction()};
    const double b{get_player_direction(g)};
    assert(std::abs(before - after) < 0.0001);
  }
  #endif
}
