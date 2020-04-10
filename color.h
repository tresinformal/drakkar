#ifndef COLOR_H
#define COLOR_H

#include <string>

class color
{
public:
  /// Construct a color, which is white by default
  /// @param r redness, value from [0, 255]
  /// @param g greenness, value from [0, 255]
  /// @param b blueness, value from [0, 255]
  /// @param a alpha value or opaqueness (0 = transparant, 255 = opaque)
  color(const int r = 255, const int g = 255, const int b = 255,
        const int a = 255);

  int get_red() const noexcept { return m_r; }
  int get_green() const noexcept { return m_g; }
  int get_blue() const noexcept { return m_b; }

  /// Get the opaqueness(from the color) of the shelter (0 = transparant, 255 =
  /// opaque)
  int get_opaqueness() const noexcept { return m_a; }

private:
  /// Redness, value from [0, 255]
  int m_r;
  /// Greenness, value from [0, 255]
  int m_g;
  /// Blueness, value from [0, 255]
  int m_b;
  /// Alpha or opaqueness (0 = transparant, 255 = opaque)
  int m_a;

};

/// Implement stream operator
std::stringstream& operator << (std::stringstream &out, const color &color);

/// Get a color that differs one hue in its red, green or blue value
color get_adjacent_color(color c);

/// Get the blueness
int get_blueness(const color &c) noexcept;

/// Get the greenness
int get_greenness(const color &c) noexcept;

/// Get the opaqueness
int get_opaqueness(const color &c) noexcept;

/// Get the redness
int get_redness(const color &c) noexcept;


/// Test the color class
void test_color();

bool operator==(const color& lhs, const color& rhs) noexcept;


#endif // COLOR_H
