#ifndef COLOR_H
#define COLOR_H

class color
{
public:
  /// Construct a color, which is white by default
  /// @param r redness, value from [0, 255]
  /// @param g greenness, value from [0, 255]
  /// @param b blueness, value from [0, 255]
  color(const int r = 255, const int g = 255, const int b = 255);

  int get_red() const noexcept { return m_r; }
  int get_green() const noexcept { return m_g; }
  int get_blue() const noexcept { return m_b; }

private:
  /// Redness, value from [0, 255]
  int m_r;
  /// Greenness, value from [0, 255]
  int m_g;
  /// Blueness, value from [0, 255]
  int m_b;
};

/// Test the color class
void test_color();

#endif // COLOR_H
