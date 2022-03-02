#ifndef SHELTER_H
#define SHELTER_H

#include "color.h"
#include "coordinate.h"
#include <cmath>
#include "string.h"
class shelter
{
public:
  shelter(const coordinate c = coordinate(0.0, 0.0),
          const double radius = 100.0,
          const color &col = color(),
          const double speed = 0.1,
          const double direction = 1.0);

  const color &get_color() const noexcept;
  double get_radius() const noexcept;
  coordinate get_position() const noexcept;
  double get_x() const noexcept;
  double get_y() const noexcept;
  double get_speed() const noexcept;
  double get_direction() const noexcept;
  // Make shelter drift in a random direction
  void make_shelter_drift();

private:
  color m_color;
  double m_radius;
  coordinate m_c;
  double m_speed;
  double m_direction;
};

std::string to_str(const shelter& in_shelter) noexcept;

void test_shelter();

/// Get the blueness (from the color) of the shelter
int get_blueness(const shelter &f) noexcept;

/// Get the greenness (from the color) of the shelter
int get_greenness(const shelter &f) noexcept;

/// Get the opaqueness(from the color) of the shelter (0 = transparat, 255 =
/// opaque)
int get_opaqueness(const shelter &f) noexcept;

/// Get the redness (from the color) of the shelter
int get_redness(const shelter &f) noexcept;
std::string to_str(const shelter& in_shelter) noexcept;

#endif // SHELTER_H
