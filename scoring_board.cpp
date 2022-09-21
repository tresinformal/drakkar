#include "scoring_board.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>

scoring_board::scoring_board(unsigned int score_player1,
                             unsigned int score_player2 ,
                             unsigned int score_player3,
                             unsigned int timer,
                             short winner)
    : m_score_player1{score_player1},
      m_score_player2{score_player2},
      m_score_player3{score_player3},
      m_timer{timer},
      m_winner{winner}
{

}

void scoring_board::set_winner(short winner)
{
  if ((winner < 0) | (winner > 2))
    {
      throw std::logic_error("winner should only be 0, 1 or 2");
    } else {
      m_winner = winner;
    }
}

void test_scoring_board()
{
#ifndef NDEBUG // no tests in release
    #define FIX_ISSUE_542
    #ifdef FIX_ISSUE_542
// When a scoring board is initialized players have 0 score and the time has not started yet
    {
      scoring_board sb;
      assert(sb.get_score_player1() == 0);
      assert(sb.get_score_player2() == 0);
      assert(sb.get_score_player3() == 0);
      assert(sb.get_timer() == 0);
      assert(sb.get_winner() == -1);
    }

    // Can get player 1 score
    {
      const scoring_board sb;
      assert(sb.get_score_player1() != 12345678 );
    }
    // Can get player 2 score
    {
      const scoring_board sb;
      assert(sb.get_score_player2() != 12345678);
    }
    // Can get player 3 score
    {
      const scoring_board sb;
      assert(sb.get_score_player3() != 12345678);
    }
    // Get/set for player 1 must be symmetric
    {
      scoring_board sb;
      sb.set_score_player1(500);
      assert(sb.get_score_player1() == 500);
    }
    // Get/set for player 2 must be symmetric
    {
      scoring_board sb;
      sb.set_score_player2(500);
      assert(sb.get_score_player2() == 500);
    }
    // Get/set for player 3 must be symmetric
    {
      scoring_board sb;
      sb.set_score_player3(500);
      assert(sb.get_score_player3() == 500);
    }
    // Cannot set negative values for player 1
    {
      scoring_board sb;
      // (591) Score cannot set to negative value
      try
      {
         sb.set_score_player1(-500);
      }
      catch (const std::invalid_argument& e)
      {
        const std::string expected_msg{
          "When setting a player score, "
          "a player score cannot be negative."
        };
        assert(e.what() == expected_msg);
      }
    }
    // Cannot set negative values for player 2
    {
       scoring_board sb;
       try {
         sb.set_score_player2(-500);
       }  catch (const std::invalid_argument& e) {
        const std::string expected_msg{
          "When setting a player score, "
          "a player score cannot be negative."
        };
         assert(e.what() == expected_msg);
       }
    }
    // Cannot set negative values for player 3
    {
       scoring_board sb;
       try {
         sb.set_score_player3(-500);
       }  catch (const std::invalid_argument& e) {
        const std::string expected_msg{
          "When setting a player score, "
          "a player score cannot be negative."
        };
         assert(e.what() == expected_msg);
       }
    }
    // Can set timer, cannot set timer to negative value
    {
        scoring_board sb;
        sb.set_timer(200);
        assert(sb.get_timer() == 200);
        sb.set_timer(-200);
        assert(sb.get_timer() == 200);
    }

    // Can set winner, cannot set to value other than -1, 0, 1, 2
    {
        scoring_board sb;
        assert(sb.get_winner() == -1);
        sb.set_winner(0);
        assert(sb.get_winner() == 0);
        sb.set_winner(1);
        assert(sb.get_winner() == 1);
        sb.set_winner(2);
        assert(sb.get_winner() == 2);
        // set to no winner
        sb.set_winner(-1);
        assert(sb.get_winner() == -1);
        // cannot set to non-legit value
        sb.set_winner(5);
        assert(sb.get_winner() == -1);
    }
    #endif
#endif
}

