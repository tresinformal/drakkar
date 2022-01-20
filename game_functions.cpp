#include <game_functions.h>
#include <coordinate.h>
#include <game.h>


// Shelters
coordinate get_nth_shelter_position(const game &g, const int &n)
{
  assert(n >= 0);
  return g.get_shelters()[n].get_position();
}

int get_nth_food_regeneration_time(const game &g, const int &n)
{
  return g.get_food()[n].get_regeneration_time();
}

// Food
coordinate get_nth_food_position(const game& g, const int& food_id)
{
  return g.get_food()[food_id].get_position();
}
