#include <game_functions.h>
#include <coordinate.h>
#include <game.h>

// Game functions are free functions that return some info about the game but do not change it
// Formally, if a function
// 1. Isn't inside a class
// 2. Takes argument game
// 3. Is passed a const ref to  game (const game&)
// Then it should be defined here. Otherwise not.

// About game itself
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

// About players

int count_alive_players(const game& g) noexcept
{
  return std::count_if(
        g.get_v_player().begin(),
        g.get_v_player().end(),
        [](const player& p)
  {return p.get_state() != player_state::dead;});
}

double get_nth_player_size(const game& g, const int i)
{
  return g.get_player(i).get_diameter();
}

double get_nth_player_direction(const game &g, const int player_ind)
{
  return g.get_player(player_ind).get_direction();
}

int get_winning_player_index(const game& g, const int i1, const int i2)
{
    if (is_first_player_winner(g.get_player(i1), g.get_player(i2))) {
        return i1;
    }
    else {
        return i2;
    }
}

int get_losing_player_index(const game& g, const int i1, const int i2)
{
    if (is_first_player_winner(g.get_player(i1), g.get_player(i2))) {
        return i2;
    }
    else {
        return i1;
    }
}

std::vector<int> get_collision_members(const game &g) noexcept
{
  std::vector<int> v_collisions;
  const auto n_players = static_cast<int>(g.get_v_player().size());
  for (int i = 0; i < n_players; ++i)
    {
      for (int j = i + 1; j < n_players; ++j)
        {
          if (are_colliding(g.get_player(i), g.get_player(j)))
            {
              v_collisions.push_back(i);
              v_collisions.push_back(j);
            }
        }
    }
  return v_collisions;
}

bool has_any_interplayer_collision(const game &g) noexcept
{
  const auto n_players = static_cast<int>(g.get_v_player().size()) ;
  for (int i = 0; i < n_players; ++i)
    {
      auto& lhs_pl = g.get_player(i);

      if(is_alive(lhs_pl))
        {
          for (int j = i + 1; j < n_players; ++j)
            {
              auto& rhs_pl = g.get_player(j);
              if(is_alive(rhs_pl))
                {
                  if (are_colliding(lhs_pl, rhs_pl))
                    {
                      return true;
                    }
                }
            }
        }

    }
  return false;
}

bool has_any_player_food_collision(const game& g)
{
  for (auto& p : g.get_v_player())
    {
      for(auto& f : g.get_food())
        {
          if (are_colliding(p, f))
            {
              return true;
            }
        }
    }
  return false;
}

bool has_any_player_projectile_collision(const game & g) noexcept
{
  const auto& projectiles = g.get_projectiles();
  const auto& players = g.get_v_player();

  for (const auto& p : projectiles)
    {
      for (const auto& pl : players)
        {
          if (are_colliding(pl, p)) return true;
        }
    }
  return false;
}

bool has_any_player_wall_collision(const game& g)
{
  for(const auto& player : g.get_v_player())
    {
      if(hits_wall(player, g.get_env()))
        {
          return true;
        }
    }
  return false;
}

// About shelters
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

// About food
bool has_uneaten_food(const game &g)
{
  std::vector<food> v_food{g.get_food()};
  for (unsigned int i = 0; i < v_food.size(); i++) {
      if (!v_food[i].is_eaten())
        {
          return true;
        }
    }
  return false ;
}

int count_food_items(const game &g)
{
  return static_cast<int>(g.get_food().size());
}

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

// About projectiles
int count_n_projectiles(const game &g) noexcept
{
  return static_cast<int>(g.get_projectiles().size());
}
