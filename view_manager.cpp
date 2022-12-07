#include "view_manager.h"
#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"
#include <cassert>
#include <typeinfo>

view_manager::view_manager(const view_mode& starting_view,
                           const game_options& options) :
  m_next_view{starting_view},
  m_game_view(options)
{

}

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

  // Declare view_manager only once for all tests
  // to reduce the number of windows created during build

  // (584) A view manager can read its first view as input
  {
    view_mode first_view = view_mode::menu;
    view_manager vw{first_view};
    assert(vw.get_next_view() == first_view);
  }

  // (583) A view_manager can read options as input
  {
    game_options options(2022, false, get_random_kam());
    view_manager vw{view_mode::game, options};
    assert(vw.get_game_view().get_options() == options);
  }

  // (553) View manager has all view types
  {
      view_manager vw;
      vw.get_game_view();
      vw.get_menu_view();
      vw.get_options_view();
  }

  /// (578) A view manager can swap views
  {
      view_manager vw{view_mode::menu};
      view_mode next_view = view_mode::game;
      assert(vw.get_next_view() != next_view);
      vw.set_next_view(next_view);
      assert(vw.get_next_view() == next_view);
  }

  /// (582) A view manager can run and exit
  {
     view_manager vw{view_mode::quit};
     vw.exec();
  }
  /// (664) The options can be changed, by modifying options
  {
    view_manager vw;
    assert(vw.get_game_view().get_options().is_playing_music());
    auto options = vw.get_game_view().get_options();
    options.stop_music();
    vw.get_game_view().set_options(options);
    assert(!vw.get_game_view().get_options().is_playing_music());
  }

#endif // NDEBUG
}

