#include "color.h"

#include <cassert>
#include <cstdlib>
#include <sstream>

color::color(const int r, const int g, const int b, const int a)
    : m_r{r}, m_g{g}, m_b{b}, m_a{a}
{
  // Stub, need exceptions later
  assert(m_r >= 0);
  assert(m_r <= 255);
  assert(m_g >= 0);
  assert(m_g <= 255);
  assert(m_b >= 0);
  assert(m_b <= 255);
  assert(m_a >= 0);
  assert(m_a <= 255);
}

color get_adjacent_color(color c)
{
  while (1)
  {
    // Stub: should use a proper RNG
    switch (std::rand() % 6)
    {
    case 0: // Increase red
      if (c.get_red() == 255)
        continue;
      return color(c.get_red() + 1, c.get_green(), c.get_blue());
    case 1: // Decrease red
      if (c.get_red() == 0)
        continue;
      return color(c.get_red() - 1, c.get_green(), c.get_blue());
    case 2: // Increase green
      if (c.get_green() == 255)
        continue;
      return color(c.get_red(), c.get_green() + 1, c.get_blue());
    case 3: // Decrease green
      if (c.get_green() == 0)
        continue;
      return color(c.get_red(), c.get_green() - 1, c.get_blue());
    case 4: // Increase blue
      if (c.get_blue() == 255)
        continue;
      return color(c.get_red(), c.get_green(), c.get_blue() + 1);
    case 5: // Decrease blue
      if (c.get_blue() == 0)
        continue;
      return color(c.get_red(), c.get_green(), c.get_blue() - 1);
    }
  }
}

int get_blueness(const color &c) noexcept { return c.get_blue(); }

int get_greenness(const color &c) noexcept { return c.get_green(); }

int get_opaqueness(const color &c) noexcept { return c.get_opaqueness(); }

int get_redness(const color &c) noexcept { return c.get_red(); }

void test_color()
{
  // Color is white by default
  {
    const color c;
    assert(c.get_red() == 255);
    assert(c.get_green() == 255);
    assert(c.get_blue() == 255);
  }
  {
    const color white;
    const color other = get_adjacent_color(white);
    assert(other.get_red() != 255 || other.get_green() != 255 ||
           other.get_blue() != 255);
  }
  #ifdef FIX_ISSUE_156
  {
    std::stringstream s;
    const color c;
    s << c;
  }
  #endif //FIX_ISSUE_156
}

bool operator==(const color& lhs, const color& rhs) noexcept
{
  return lhs.get_red() == rhs.get_red()
    && lhs.get_green() == rhs.get_green()
    && lhs.get_blue() == rhs.get_blue()
    && lhs.get_opaqueness() == rhs.get_opaqueness()
  ;
}
