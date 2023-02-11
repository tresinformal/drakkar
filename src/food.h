#ifndef FOOD_H
#define FOOD_H

#include "coordinate.h"
#include "color.h"
#include "food_state.h"
#include <vector>
#include <random>
class food
{
public:
  food(const coordinate c = coordinate(2000.0, 1000.0), const color &col = color(), const int regeneration_time = 100, food_state food_state = food_state::uneaten, const double radius = 25.0);

  const color &get_color() const noexcept { return m_color; }
  double get_x() const noexcept;
  double get_y() const noexcept;
  coordinate get_position() const noexcept { return m_c; }
  // int get_food_timer() const noexcept
  int get_regeneration_time() const noexcept { return m_regeneration_time;}
  bool is_eaten() const noexcept;
  /// Get the food state
  food_state get_food_state() const noexcept { return m_food_state;}
  void set_food_state(const food_state &newState) noexcept { m_food_state = newState; }
  void place_randomly(std::mt19937 &rng, const coordinate& top_left, const coordinate& bottom_right);
  double get_radius() const noexcept;
  int get_timer() const noexcept { return m_timer; }
  void increment_timer();
  void reset_timer();

private:
  coordinate m_c;
  color m_color;
  int m_regeneration_time;
  int m_timer = 0;
  /// the food state
  food_state m_food_state;
  double m_radius;
};
///Compares two food objects for equality
bool operator==(const food& lhs, const food& rhs) noexcept;

void test_food();
///get the position of an inputted food object
const coordinate get_position(const food& in_food);
/// Get the blueness (from the color) of the food
int get_blueness(const food &f) noexcept;

/// Get the greenness (from the color) of the food
int get_greenness(const food &f) noexcept;

/// Get the redness (from the color) of the food
int get_redness(const food &f) noexcept;

/// Implement stream operator
std::ostream& operator << (std::ostream &out, const food food);

///equality operator to check if foods have the same colour and position
bool operator==(const food& lhs, const food& rhs) noexcept;

///inequality operator -||-
bool operator!=(const food& lhs, const food& rhs) noexcept;

#endif // FOOD_H
