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

// Set winner
void scoring_board::set_winner(short winner)
{
    if (winner >= -1 & winner <= 2)
    {
        m_winner = winner;
    }
}

// Update scores of the players according to the events happend on the players at this tick
void scoring_board::update_scores()
{

}

// Update time past since the start of the game
void scoring_board::update_timer()
{

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

