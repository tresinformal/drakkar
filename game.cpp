#include "game.h"
#include <cassert>
#include<iostream>
#include<cmath>

game::game(const int n_ticks, environment_type environment_type, unsigned int num_players)
 : m_n_ticks{n_ticks},
   m_v_player(num_players, player()),
   m_environment_type{environment_type},
   m_food{1}
{
  for (unsigned int i = 0; i < m_v_player.size(); ++i){
  m_v_player[i] = player(300.0 + m_dist_x_pls * i,400.0, player_shape::rocket);
  }
}

double game::get_player_direction( unsigned int player_ind)
{return get_player(player_ind).get_direction();}


double get_player_direction(game g, unsigned int player_ind)
{return g.get_player(player_ind).get_direction();}

void game::apply_inertia(){
for(unsigned int i = 0; i < get_v_player().size(); ++i){
    if(get_player(i).get_speed()>0){
        //And should this function take some value from environment?
        get_player(i).do_action(action_type::brake);
    }
}
}

void game::tick(){
    //for now only applies inertia
    apply_inertia();
    ++get_n_ticks();
}

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
    // give the player a speed of more than 0
    g.get_player(i).do_action(action_type::accelerate);
    const double before{g.get_player(i).get_speed()};
    g.get_player(i).do_action(action_type::brake);
    const double after{g.get_player(i).get_speed()};
    assert( before-after > 0.0000000000000001);
    //After should be < than before
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
    //calling tick updates the counter and
    
    //callling tick() increases m_n_tick by one
    {
        game g;
        const int before =g.get_n_ticks();
        g.tick();
        assert( g.get_n_ticks() - before == 1);

    }
    // inertia  slows down players
    {
        game g;
        std::vector<double> before_v;
        std::vector<double> after_v;
        for (unsigned int i = 0; i< g.get_v_player().size();++i)
        {
        // give the player a speed of more than 0
        g.get_player(i).do_action(action_type::accelerate);
        before_v.push_back(g.get_player(i).get_speed());
        }
        g.apply_inertia();
        for (unsigned int i = 0; i< g.get_v_player().size();++i)
        {
        after_v.push_back(g.get_player(i).get_speed());
        }
        for (unsigned int i = 0; i< g.get_v_player().size();++i)
        {
        assert( before_v[i] - after_v[i] > 0.0000000000000001);
        //After should be < than before
        }
    }

    //players are placed at dist of 100 points
    //along the x axis at initialization
    {
        game g;
        for(unsigned int i = 0; i < (g.get_v_player().size() - 1); ++i){
        assert(g.get_player(i).get_x() - g.get_player(i+1).get_x() + g.get_dist_x_pls() < 0.000001
               &&
               g.get_player(i).get_x() - g.get_player(i+1).get_x() + g.get_dist_x_pls() > -0.000001);
        }
    }

}
