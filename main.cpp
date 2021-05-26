#include "enemy.h"
#include "environment.h"
#include "environment_type.h"
#include "enemy_behavior_type.h"
#include "food.h"
#include "food_type.h"
#include "food_state.h"
#include "game.h"
#include "game_options.h"
#include "game_resources.h"
#include "game_view.h"
#include "key_action_map.h"
#include "menu_button.h"
#include "menu.h"
#include "menu_view.h"
#include "player.h"
#include "player_factory.h"
#include "player_shape.h"
#include "program_state.h"
#include "player_state.h"
#include "projectile.h"
#include "sound_type.h"
#include "optional.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <chrono>
#include <iostream>

/// All tests are called from here, only in debug mode
void test()
{
#ifndef NDEBUG
    test_optional();
    test_action_type();
    test_player_shape();
    test_player();
    test_game();
    test_game_options();
    test_enemy();
    test_enemy_behavior_type();
    test_environment();
    test_individual_type();
    test_food();
    test_food_type();
    test_food_state();
    test_key_action_map();
    test_menu();
    test_menu_button();
    test_shelter();
    test_color();
    test_projectile_type();
    test_projectile();
    test_program_state();
    test_player_state();
    test_player_factory();

#ifndef LOGIC_ONLY
    test_game_view();
    test_game_resources();
    test_sound_type();
#endif // LOGIC_ONLY
#endif
}

#include <algorithm>
#include <numeric>

int main(int argc, char **argv) //!OCLINT tests may be long
{
#ifndef NDEBUG
    assert(0.1 > 0.0); //!OCLINT indeed a constant conditional
    test();
#else
    // In release mode, all asserts are removed from the code
    assert(1 == 2);
#endif
#ifdef LOGIC_ONLY
    std::cout << "Compiled with LOGIC_ONLY\n";
#endif

    const std::vector<std::string> args(argv, argv + argc);

    // We've already tested, so the program is done
    if (args.size() > 1 && args[1] == "--test")
        return 0;

    else  if (args.size() > 1 && args[1] == "--profile")
    {
#ifndef NDEBUG
        perror("Do not profile in debug mode");
        abort();
#else
#ifndef LOGIC_ONLY // that is, not compiled on GitHub Actions
        using namespace std::chrono;
        game_view v;
        double max_duration = 10;
        auto start = high_resolution_clock::now();
        duration<double> time = high_resolution_clock::now() - start;
        while( time.count() < max_duration)
        {
            v.process_events();
            v.get_game().tick();
            v.show();
            time =  high_resolution_clock::now() - start;
        }
        std::cout << time.count() << '\n';
#endif // LOGIC_ONLY // that is, not compiled on GitHub Actions
#endif
    }
#ifndef LOGIC_ONLY


    // Show the menu, quits after (for now)
    if (args.size() > 1 && args[1] == "--menu")
    {
        menu_view v;
        v.exec();
        return 0;
    }

    game_options options;
    if (args.size() > 1 && args[1] == "--no-sound")
    {
        music_off(options);
    }
    game_view v(options);
    assert(options == v.get_options());
    v.exec();
#endif // LOGIC_ONLY
}
