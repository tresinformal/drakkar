#include "view_manager.h"
#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"
#include <cassert>

view_manager::view_manager(game_view& gv,
                           menu_view& mv,
                           options_view& ov)
{
    m_game_view = &gv;
    m_menu_view = &mv;
    m_options_view = &ov;
}

void test_view_manager()
{
#ifndef NDEBUG
    
    ///View manager exists
    {
        view_manager{};
    }

    // (553) View manager has all view types
    {
        game_view gv;
        menu_view mv;
        options_view ov;
        view_manager vw(gv, mv, ov);
        assert(vw.get_game_view() == gv);
        assert(vw.get_menu_view() == mv);
        assert(vw.get_options_view() == ov);
    }


#endif
}
