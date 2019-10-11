#ifndef GAMELOGIC_H
#define GAMELOGIC_H


class game
{
public:
    game(const int n_ticks=0);

    /// return the number of ticks
    int get_n_ticks() const noexcept {return m_n_ticks;}

private:

    ///the number of ticks
    int m_n_ticks;
};

void test_game();
#endif // GAMELOGIC_H
