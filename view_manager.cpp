#include "view_manager.h"
#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"
#include <cassert>
#include <typeinfo>

void test_view_manager()
{
#ifndef NDEBUG
    
    ///View manager exists
    {
        view_manager{};
    }

    // (553) View manager has all view types
    {
        view_manager vw;
        vw.get_game_view();
        vw.get_menu_view();
        vw.get_options_view();
    }

    ///A view manager can run
    {
        view_manager v;
        v.run();
    }

    ///A view manager shows by default an option view
    {
        const view_manager v;
        assert(v.is_showing() == view_mode::options);
    }

    ///A view manager can swap views
    {
        view_manager v;
        view_mode next_view = view_mode::game;
        assert(v.is_showing() != next_view);
        v.swap(next_view);
        assert(v.is_showing() == next_view);
    }

#endif
}

