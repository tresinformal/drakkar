#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "coordinate.h"
#include "game.h"

// Game functions are free functions that return some info about the game but do not change it
// Formally, if a function
// 1. Isn't inside a class
// 2. Takes argument game
// 3. Is passed a const ref to  game (const game&)
// Then it should be declared here. Otherwise not.

// About game itself
double get_max_x(const game &g);
double get_min_x(const game &g);
double get_max_y(const game &g);
double get_min_y(const game &g);

// About players
int count_alive_players(const game& g) noexcept;
double get_nth_player_size(const game& g, const int i);
const color get_nth_player_color(const game& g, const int i);
player_state get_nth_player_state(const game& g, const int i);
double get_nth_player_direction(const game &g, const int player_ind);
int get_winning_player_index(const game& g, const int i1, const int i2);
int get_losing_player_index(const game& g, const int i1, const int i2);
std::vector<int> get_collision_members(const game &g) noexcept;
bool has_any_interplayer_collision(const game &g) noexcept;
bool has_any_player_food_collision(const game& g);
bool has_any_player_food_collision(const game& g);
bool has_any_player_wall_collision(const game& g);
coordinate predict_players_movement(const player& p);

// About food
bool has_uneaten_food(const game &g);
int count_food_items(const game &g);
coordinate get_nth_food_position(const game& g, const int& food_id);
double get_nth_food_x(const game &g, const int n);
double get_nth_food_y(const game &g, const int n);
color get_nth_food_color(const game &g, const int n);
int get_nth_food_regeneration_time(const game &g, const int &n);
int get_nth_food_timer(const game &g, const int &n);
bool is_nth_food_eaten(const game &g, const int &n);

#endif // GAME_FUNCTIONS_H
