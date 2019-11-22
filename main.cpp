#include <SFML/Graphics.hpp>
#include <cassert>
#include "player_shape.h"
#include "player.h"
#include "game.h"
#include "game_options.h"
#include "game_view.h"
#include "game_resources.h"
#include "enemy.h"
#include "environment_type.h"
#include "environment.h"
#include "food.h"

/// All tests are called from here, only in debug mode
void test() {
  test_player_shape();
  test_player();
  test_game();
  test_game_options();
  test_game_view();
  test_game_resources();
  test_enemy();
  test_environment();
  test_environment_type();
  test_food();
}

int main(int argc, char ** argv) //!OCLINT tests may be long
{
#ifndef NDEBUG
  test();
#else
  // In release mode, all asserts are removed from the code
  assert(1 == 2);
#endif
  const std::vector<std::string> args(argv, argv + argc);

  //We've already tested, so the program is done
  if (args.size() > 1 && args[1] == "--test") return 0;

  #ifdef FIX_ISSUE_74
  //Show the menu, quits after (for now)
  if (args.size() > 1 && args[1] == "--menu")
  {
    menu_view v;
    v.exec();
    return 0;
  }
  #endif

  game_view v;
  v.exec();
  return 0;
}
