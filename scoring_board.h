#ifndef SCORING_BOARD_H
#define SCORING_BOARD_H

#include <string>
#include <iosfwd>

class scoring_board
{
public:
    scoring_board(unsigned int score_player1 = 0,
                  unsigned int score_player2 = 0,
                  unsigned int score_player3 = 0,
                  unsigned int timer = 0,
                  short winner = -1);
    void set_score_player1(unsigned int score) {m_score_player1 = score;};

    void set_score_player2(unsigned int score) {m_score_player2 = score;};

    void set_score_player3(unsigned int score) {m_score_player3 = score;};

    void set_timer(unsigned int time) {m_timer = time;};

    void set_winner(short winner);

    unsigned int get_score_player1() {return m_score_player1;};

    unsigned int get_score_player2() {return m_score_player2;};

    unsigned int get_score_player3() {return m_score_player3;};

    unsigned int get_timer() {return m_timer;};

    short get_winner() {return m_winner;};

private:
    unsigned int m_score_player1{0};

    unsigned int m_score_player2{0};

    unsigned int m_score_player3{0};

    unsigned int m_timer{0};

    // -1 indicates no winner
    short m_winner{-1};
};

void test_scoring_board();

#endif // SCORING_BOARD_H
