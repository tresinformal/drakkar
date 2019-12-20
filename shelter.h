#ifndef SHELTER_H
#define SHELTER_H


#include "color.h"

class shelter
{
public:
  shelter(const double x = 0.0, const double y = 0.0, const color& c = color());

  const color& get_color() const noexcept { return m_color; }
  double get_x() const noexcept { return f_x; }
  double get_y() const noexcept { return f_y; }

private:
  double f_x;
  double f_y;
  color m_color;
};

void test_shelter();

/// Get the blueness (from the color) of the shelter
int get_blueness(const shelter &f) noexcept;

/// Get the greenness (from the color) of the shelter
int get_greenness(const shelter &f) noexcept;

/// Get the redness (from the color) of the shelter
int get_redness(const shelter &f) noexcept;


#endif // SHELTER_H
