#ifndef FOOD_H
#define FOOD_H

#include "color.h"

class food
{
public:
  food(const double x = 0.0, const double y = 0.0, const color &c = color());

  const color &get_color() const noexcept { return m_color; }
  double get_x() const noexcept { return f_x; }
  double get_y() const noexcept { return f_y; }

private:
  double f_x;
  double f_y;
  color m_color;
};

void test_food();

/// Get the blueness (from the color) of the food
int get_blueness(const food &f) noexcept;

/// Get the greenness (from the color) of the food
int get_greenness(const food &f) noexcept;

/// Get the redness (from the color) of the food
int get_redness(const food &f) noexcept;

#endif // FOOD_H
