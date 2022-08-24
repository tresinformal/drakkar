#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"

class view_manager
{
public:
    view_manager(game_view &gv,
        menu_view &mv,
        options_view &ov
        );
    game_view get_game_view() const noexcept { return m_game_view;} ;
    menu_view get_menu_view() const noexcept { return m_menu_view;} ;
    options_view get_options_view() const noexcept { return m_options_view;} ;

private:
    game_view* m_game_view;
    menu_view* m_menu_view;
    options_view* m_options_view;
};

void test_view_manager();

#endif // VIEW_MANAGER_H
