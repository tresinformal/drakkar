#include "scoring_board.h"
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>

scoring_board::scoring_board(int score_player1,
                             int score_player2 ,
                             int score_player3,
                             int timer,
                             int winner)
    : m_score_player1{score_player1},
      m_score_player2{score_player2},
      m_score_player3{score_player3},
      m_timer{timer},
      m_winner{winner}
{

}

int scoring_board::get_score(int player) const noexcept
{
  switch (player)
  {
  case 0:
    return m_score_player1;
  case 1:
    return m_score_player2;
  case 2:
    return m_score_player3;
  default:
    return 0;
  }
}

void scoring_board::set_score(int player, int score)
{
  switch (player)
  {
  case 0:
    m_score_player1 = score;
    break;
  case 1:
    m_score_player2 = score;
    break;
  case 2:
    m_score_player3 = score;
    break;
  default:
    break;
  }
}

void scoring_board::modify_score(int player, int amount)
{
  switch (player)
  {
  case 0:
    m_score_player1 += amount;
    break;
  case 1:
    m_score_player2 += amount;
    break;
  case 2:
    m_score_player3 += amount;
    break;
  default:
    break;
  }
}

void scoring_board::set_winner(int winner)
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
        // Can get a specific player's score
        assert(sb.get_score(1) == 0);

        assert(sb.get_score_player1() == 0);
        assert(sb.get_score_player2() == 0);
        assert(sb.get_score_player3() == 0);
        assert(sb.get_timer() == 0);
        assert(sb.get_winner() == -1);
    }

    // Can set players' score
    {
        scoring_board sb;

        // Can get a specific player's score
        sb.set_score(1, 500);
        assert(sb.get_score(1) == 500);

        sb.set_score_player1(500);
        assert(sb.get_score_player1() == 500);
        sb.set_score_player2(500);
        assert(sb.get_score_player2() == 500);
        sb.set_score_player3(500);
        assert(sb.get_score_player3() == 500);
    }

    // Can set players' score
    {
        scoring_board sb;

        // Can get a specific player's score
        sb.set_score(1, 500);
        assert(sb.get_score(1) == 500);

        sb.set_score_player1(500);
        assert(sb.get_score_player1() == 500);
        sb.set_score_player2(500);
        assert(sb.get_score_player2() == 500);
        sb.set_score_player3(500);
        assert(sb.get_score_player3() == 500);
    }

    // Can modify players' score
    {
        scoring_board sb;

        // Can get a specific player's score
        sb.set_score(1, 500);
        sb.modify_score(1, 500);
        assert(sb.get_score(1) == 1000);

        sb.set_score(0, 500);
        sb.modify_score_player1(500);
        assert(sb.get_score_player1() == 1000);
        sb.set_score(1, 500);
        sb.modify_score_player2(500);
        assert(sb.get_score_player2() == 1000);
        sb.set_score(2, 500);
        sb.modify_score_player3(500);
        assert(sb.get_score_player3() == 1000);
    }

    // Can set timer
    {
        scoring_board sb;
        sb.set_timer(200);
        assert(sb.get_timer() == 200);
    }

    // Can set winner, cannot set to value other than 0, 1, 2
    {
        scoring_board sb;
        assert(sb.get_winner() == 0);
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

