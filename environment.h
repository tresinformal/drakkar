#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "coordinate.h"
#include "environment_type.h"

class environment
{
public:
  environment(double wall_short_side = 1600, environment_type environment_type = environment_type::empty);
  double get_wall_s_side() const noexcept { return m_wall_short_side;}
  double get_wall_l_side() const noexcept { return m_wall_long_side;}
  coordinate get_top_left() const noexcept { return m_top_left_position; }
  coordinate get_bottom_right() const noexcept { return m_bottom_right_position; }

  /// Get environment type of the game
  environment_type get_type() const { return m_environment_type; }

private:
  double m_wall_short_side;
  double m_wall_long_side;
  coordinate m_top_left_position;
  coordinate m_bottom_right_position;
  /// the environment
  environment_type m_environment_type;
};

double get_max_x(const environment& e)
{
  return e.get_bottom_right().get_x();
}

double get_max_y(const environment& e)
{
  return e.get_bottom_right().get_y();
}

double get_min_x(const environment& e)
{
  return e.get_top_left().get_x();
}

double get_min_y(const environment& e)
{
  return e.get_top_left().get_y();
}

void test_environment();


#endif // ENVIRONMENT_H
