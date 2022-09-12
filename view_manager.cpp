#include "view_manager.h"
#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"
#include <cassert>
#include <typeinfo>

void view_manager::set_next_view(view_mode next_view)
{
    m_next_view = next_view;
}

void view_manager::exec()
{
  bool must_quit{false};

  // Execute and switch between views
  while (!must_quit)
    {
      switch (m_next_view)
        {
        case view_mode::menu:
          {
            m_menu_view.exec();
            set_next_view(m_menu_view.get_next_view());
            break;
          }
        case view_mode::game:
          {
            m_game_view.exec();
            set_next_view(m_game_view.get_next_view());
            break;
          }
        case view_mode::options:
          {
            m_options_view.exec();
            set_next_view(m_options_view.get_next_view());
            break;
          }
          // other views ...
        case view_mode::quit:
          // Game exits successfully
          must_quit = true;
          break;
        default:
          throw std::logic_error("Unknown view mode.");
        }
    }
}

void test_view_manager()
{
#ifndef NDEBUG
    
    // (553) View manager has all view types
    {
        view_manager vw;
        vw.get_game_view();
        vw.get_menu_view();
        vw.get_options_view();
    }

    /// (578) A view manager shows by default a game view
    {
        const view_manager v;
        assert(v.get_next_view() == view_mode::game);
    }

    /// (578) A view manager can swap views
    {
        view_manager v;
        view_mode next_view = view_mode::menu;
        assert(v.get_next_view() != next_view);
        v.set_next_view(next_view);
        assert(v.get_next_view() == next_view);
    }

  /// A view manager can run and exit
  {
      view_manager v;
      v.set_next_view(view_mode::quit);
      v.exec();
  }


#endif
}

