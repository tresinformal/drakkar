#ifndef MENU_VIEW_H
#define MENU_VIEW_H
#include"SFML/Graphics.hpp"
#include"menu_logic.h"


class menu_view
{
public:
    menu_view();

    ///Creates the menu and draws it
    void exec();


private:
    menu_logic m_menu_logic;
    sf::RenderWindow m_window;

    ///
    bool process_events();

    ///Draws the buttons
    void draw_buttons() noexcept;

    /// Shows the menu
    void show();

};

#endif // MENU_VIEW_H
