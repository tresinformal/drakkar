#include "color.h"

#include <cassert>


color::color(const int r, const int g, const int b)
    : m_r{r}, m_g{g}, m_b{b}
{
  // Stub, need exceptions later
  assert(m_r >= 0);
  assert(m_r <= 255);
  assert(m_g >= 0);
  assert(m_g <= 255);
  assert(m_b >= 0);
  assert(m_b <= 255);
}

void test_color()
{
  //Color is white by default
  {
    const color c;
    assert(c.get_red() == 255);
    assert(c.get_green() == 255);
    assert(c.get_blue() == 255);
  }
}
