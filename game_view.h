#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>

/// The game's main window
/// Displays the game class
class game_view
{
public:
    game_view();

    void show() noexcept;
    void exec() noexcept;

private:
    //The game_view has a window

    sf::RenderWindow m_window;


};


void test_game_view();

#endif // GAME_VIEW_H
