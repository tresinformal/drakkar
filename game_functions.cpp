#include <game_functions.h>
#include <coordinate.h>
#include <game.h>

// Game
double get_max_x(const game &g) {
    return get_max_x(g.get_env());
}
double get_min_x(const game &g){
    return get_min_x(g.get_env());
}
double get_max_y(const game &g){
    return get_max_y(g.get_env());
}
double get_min_y(const game &g){
    return get_min_y(g.get_env());
}

// Shelters
std::vector<coordinate> get_all_shelter_positions(const game& g)
{
  int n_shelters = g.get_shelters().size();
  std::vector<coordinate> all_shelter_positions;
  for (int i = 0; i < n_shelters; ++i)
    {
      all_shelter_positions.push_back(get_nth_shelter_position(g, i));
    }
  return all_shelter_positions;
}
coordinate get_nth_shelter_position(const game &g, const int &n)
{
  assert(n >= 0);
  return g.get_shelters()[n].get_position();
}

// Food
coordinate get_nth_food_position(const game& g, const int& food_id)
{
  return g.get_food()[food_id].get_position();
}
double get_nth_food_x(const game &g, const int n)
{
  return g.get_food()[n].get_x();
}
double get_nth_food_y(const game &g, const int n)
{
  return g.get_food()[n].get_y();
}
bool is_nth_food_eaten(const game& g, const int &n)
{
  return g.get_food()[n].is_eaten();
}
int get_nth_food_regeneration_time(const game &g, const int &n)
{
  return g.get_food()[n].get_regeneration_time();
}
int get_nth_food_timer(const game &g, const int &n)
{
  return g.get_food()[n].get_timer();
}
