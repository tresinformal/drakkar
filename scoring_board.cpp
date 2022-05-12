#include "scoring_board.h"
#include <cassert>
#include <cmath>
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

void scoring_board::set_score_player1(unsigned int score)
{
    if (score >= 0) m_score_player1 = score;
}

void scoring_board::set_score_player2(unsigned int score)
{
    if (score >= 0) m_score_player2 = score;
}

void scoring_board::set_score_player3(unsigned int score)
{
    if (score >= 0) m_score_player3 = score;
}

void scoring_board::set_timer(unsigned int time)
{
    if (time >= 0) m_timer = time;
}

void scoring_board::set_winner(short winner)
{
    if (winner >= -1 & winner <= 2)
    {
        m_winner = winner;
    }
}

void test_scoring_board()
{
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
}

