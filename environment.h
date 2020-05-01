#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "environment_type.h"

class environment
{
public:
  environment(double wall_short_side = 720, environment_type environment_type = environment_type::empty);
  constexpr double get_min_x() const noexcept { return m_min_x; }
  constexpr double get_min_y() const noexcept { return m_min_y; }
  constexpr double get_max_x() const noexcept { return m_max_x; }
  constexpr double get_max_y() const noexcept { return m_max_y; }
  constexpr double get_wall_s_side() const noexcept { return m_wall_short_side;}
  constexpr double get_wall_l_side() const noexcept { return m_wall_long_side;}
  /// Get environment type of the game
  constexpr environment_type get_type() const { return m_environment_type; }

private:
  double m_wall_short_side;
  double m_wall_long_side;
  double m_max_x;
  double m_min_x;
  double m_max_y;
  double m_min_y;


  /// the environment
  environment_type m_environment_type;
};

void test_environment();
#endif // ENVIRONMENT_H
