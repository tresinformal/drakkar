#include "game_functions.h"
#include "coordinate.h"
#include "game.h"

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


const color get_nth_player_color(const game& g, const int i)
{
  return g.get_player(i).get_color();
}

player_state get_nth_player_state(const game& g, const int i)
{
  return g.get_player(i).get_state();
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
              if(is_alive(rhs_pl)
                      && !is_passive(lhs_pl)
                      && !is_passive(rhs_pl) )
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

coordinate predict_players_movement(const player& p)
{
  double next_x = p.get_x() + cos(p.get_direction()) * p.get_speed();
  double next_y = p.get_y() + sin(p.get_direction()) * p.get_speed();
  coordinate c(next_x, next_y);
  return c;
}
