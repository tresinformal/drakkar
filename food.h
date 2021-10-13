#ifndef FOOD_H
#define FOOD_H

#include "color.h"
#include "food_state.h"
#include <vector>
class food
{
public:
  food(const double x = 2000.0, const double y = 1000.0, const color &c = color(), const int regeneration_time = 100, food_state food_state = food_state::uneaten, const double radius = 25.0);

  const color &get_color() const noexcept { return m_color; }
  double get_x() const noexcept;
  double get_y() const noexcept;
  // int get_food_timer() const noexcept
  int get_regeneration_time() const noexcept { return m_regeneration_time;}
  bool is_eaten() const noexcept;
  /// Get the food state
  food_state get_food_state() const noexcept { return m_food_state;}
  void set_food_state(const food_state &newState) noexcept { m_food_state = newState; }
  double get_radius() const noexcept;
  int get_timer() const noexcept { return m_timer; }
  void increment_timer();
  void reset_timer();

private:
  double m_x;
  double m_y;
  color m_color;
  int m_regeneration_time;
  int m_timer = 0;
  /// the food state
  food_state m_food_state;
  double m_radius;
};

void test_food();
///get the position of an inputted food object
const std::vector<double> get_position(const food& in_food);
/// Get the blueness (from the color) of the food
int get_blueness(const food &f) noexcept;

/// Get the greenness (from the color) of the food
int get_greenness(const food &f) noexcept;

/// Get the redness (from the color) of the food
int get_redness(const food &f) noexcept;

/// Implement stream operator
std::ostream& operator << (std::ostream &out, const food food);
#endif // FOOD_H
