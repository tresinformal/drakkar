#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <coordinate.h>
#include <game.h>

// Free functions that take a game as first argument

// Shelter
coordinate get_nth_shelter_position(const game &g, const int &n);

// Food
coordinate get_nth_food_position(const game& g, const int& food_id);
int get_nth_food_timer(const game &g, const int &n);

#endif // GAME_FUNCTIONS_H
