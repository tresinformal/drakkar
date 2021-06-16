#ifndef FOOD_H
#define FOOD_H

#include "color.h"
#include "food_state.h"
#include <vector>
class food
{
public:
  food(const double x = 0.0, const double y = 0.0, const color &c = color(), const double timer=0.0, food_state food_state = food_state::uneaten);

  const color &get_color() const noexcept { return m_color; }
  double get_x() const noexcept;
  double get_y() const noexcept;
  double get_regeneration_time() const noexcept { return m_regeneration_time;}
  bool is_eaten() const noexcept;
  bool is_uneaten() const noexcept;
  /// Get the food state
  food_state get_food_state() const noexcept { return m_food_state;}
private:
  double m_x;
  double m_y;
  color m_color;
  double m_regeneration_time;
  /// the food state
  food_state m_food_state;
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
