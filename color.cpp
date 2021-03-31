#include "color.h"

#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>

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
        assert(c.get_opaqueness() == 255);
    }
    // Test get functions
    {
        const color c1{0,21,255,10};
        assert(get_redness(c1)==0);
        assert(get_greenness(c1)==21);
        assert(get_blueness(c1)==255);
        assert(get_opaqueness(c1)==10);
    }
    // operator==
    {
        const color c;
        const color c1;
        assert(c == c1);
    }

//     operator!=
    {
      const color red{255, 0, 0};
      const color green{0, 255, 0};
      assert(red != green);
    }
    // operator<<
    {
        std::stringstream s;
        const color c;
        s << c;
    }
    //#define FIX_ISSUE_211
    #ifdef FIX_ISSUE_211
    {
        const color c;
        std::cout << c;
    }
    #endif // FIX_ISSUE_211
}

bool operator==(const color& lhs, const color& rhs) noexcept
{
    return lhs.get_red() == rhs.get_red()
            && lhs.get_green() == rhs.get_green()
            && lhs.get_blue() == rhs.get_blue()
            && lhs.get_opaqueness() == rhs.get_opaqueness()
            ;
}

bool operator!=(const color& lhs, const color& rhs) noexcept
{
  return !(lhs == rhs);
}

std::stringstream& operator << (std::stringstream &out, const color &color)
{
    out << "Color(" << std::to_string(color.get_red()) <<
           ", " << std::to_string(color.get_green()) <<
           ", " << std::to_string(color.get_blue()) <<
           ")";

    return out;
}
