#include "view_manager.h"
#include "game_view.h"
#include "options_view.h"
#include "menu_view.h"
#include <cassert>

view_manager::view_manager()
{

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
      // #define FIX_ISSUE_533
      #ifdef FIX_ISSUE_533
      game_view gv;
      menu_view mv;
      options_view ov;
      view_manager vw(gv, mv, ov);
      assert(vw.get_game_view() == gv);
      assert(vw.get_menu_view() == mv);
      assert(vw.get_options_view() == ov);
      #endif // FIX_ISSUE_533
    }


  #endif
}
