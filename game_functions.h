#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <coordinate.h>
#include <game.h>

// Free functions that take a game as first argument

// Game itself
double get_max_x(const game &g);
double get_min_x(const game &g);
double get_max_y(const game &g);
double get_min_y(const game &g);

// Shelter
std::vector<coordinate> get_all_shelter_positions(const game& g);
coordinate get_nth_shelter_position(const game &g, const int &n);

// Food
coordinate get_nth_food_position(const game& g, const int& food_id);
double get_nth_food_x(const game &g, const int n);
double get_nth_food_y(const game &g, const int n);
int get_nth_food_regeneration_time(const game &g, const int &n);
int get_nth_food_timer(const game &g, const int &n);
bool is_nth_food_eaten(const game &g, const int &n);

#endif // GAME_FUNCTIONS_H
