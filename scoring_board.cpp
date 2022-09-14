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
    // Scoring board has a correct initial state
    {
        scoring_board sb;
        assert(sb.get_score_player1() == 0);
        assert(sb.get_score_player2() == 0);
        assert(sb.get_score_player3() == 0);
        assert(sb.get_timer() == 0);
        assert(sb.get_winner() == -1);
    }

    // Can set players' score, cannot set to negative value
    {
        scoring_board sb;
        sb.set_score_player1(500);
        assert(sb.get_score_player1() == 500);
        sb.set_score_player2(500);
        assert(sb.get_score_player2() == 500);
        sb.set_score_player3(500);
        assert(sb.get_score_player3() == 500);

        sb.set_score_player1(-500);
        assert(sb.get_score_player1() == 500);
        sb.set_score_player2(-500);
        assert(sb.get_score_player2() == 500);
        sb.set_score_player3(-500);
        assert(sb.get_score_player3() == 500);
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

