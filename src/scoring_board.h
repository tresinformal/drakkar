#ifndef SCORING_BOARD_H
#define SCORING_BOARD_H

#include <string>
#include <iosfwd>

class scoring_board
{
public:
    scoring_board(int score_player1 = 0,
                  int score_player2 = 0,
                  int score_player3 = 0,
                  int timer = 0,
                  int winner = -1);
    void set_score(int player, int score);

    void set_score_player1(int score) {m_score_player1 = score;};

    void set_score_player2(int score) {m_score_player2 = score;};

    void set_score_player3(int score) {m_score_player3 = score;};

    void set_timer(int time) {m_timer = time;};

    void set_winner(int winner);

    int get_score(int player) const noexcept;

    int get_score_player1() const noexcept {return m_score_player1;};

    int get_score_player2() const noexcept {return m_score_player2;};

    int get_score_player3() const noexcept {return m_score_player3;};

    void modify_score(int player, int amount);

    void modify_score_player1(int amount) {m_score_player1 += amount;}

    void modify_score_player2(int amount) {m_score_player2 += amount;}

    void modify_score_player3(int amount) {m_score_player3 += amount;}

    int get_timer() const noexcept {return m_timer;};

    int get_winner() const noexcept {return m_winner;};

private:
    int m_score_player1{0};

    int m_score_player2{0};

    int m_score_player3{0};

    int m_timer{0};

    int m_winner{0};
};

void test_scoring_board();

#endif // SCORING_BOARD_H
